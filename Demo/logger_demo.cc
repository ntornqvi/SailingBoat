#include <iostream>
#include "../Core/IO/io.h"
#include "../Utilities/DataContainers/gps_position.h"
#include "../Core/Parser/parser.h"
#include <cstdlib>
#include <vector>
#include <iomanip>

int main(void) {
  std::cout << "Beginning Logger Test" << std::endl;

  IO io;
  Parser parser;

  std::vector<std::string> gps_file_data = io.ReadFile("test.txt");

  std::cout << "we have #" << gps_file_data.size() << " lines of code" << std::endl;

  for (int i = 0; i < gps_file_data.size(); i++) {
    std::cout << gps_file_data[i] << std::endl;
  }

  std::vector<std::string> cleaned = parser.RemoveComments(gps_file_data);

  std::cout << "we have #" << cleaned.size() << " Coordinates" << std::endl;
  std::vector<GPSPosition> gps_waypoints;
  for (int i = 0; i < cleaned.size(); i++) {
    std::vector<std::string> split = parser.SplitString(cleaned[i], ',');
    if (split.size() == 2) {
      GPSPosition item;
      item.latitude = std::atof(split[0].c_str());
      item.longitude = std::atof(split[1].c_str());

      gps_waypoints.push_back(item);
    }
  }

  std::cout << "We have #" << gps_waypoints.size() << " Waypoints to our destination" << std::endl;

  for (int i = gps_waypoints.size() - 1; i >= 0; i--) {
    std::cout << "WAYPOINT #" << i << std::endl;
    std::cout << std::setprecision(15) << gps_waypoints[i].latitude << std::endl;
    std::cout << std::setprecision(15) << gps_waypoints[i].longitude << std::endl;
  }

  io.WriteFile("THIS IS JUST A TEST");

  return 0;
}