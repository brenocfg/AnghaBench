#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Method {char* member_0; char* member_1; char* member_2; } ;

/* Variables and functions */

__attribute__((used)) static struct Method* Start_Methods(void) {
  
  static struct Method methods[] = {
    {
      "with", 
      "#define with(...)",
      "Perform operations in between `start` and `stop`."
    }, {
      "start", 
      "void start(var self);",
      "Start the object `self`."
    }, {
      "stop", 
      "void stop(var self);",
      "Stop the object `self`."
    }, {
      "join", 
      "void join(var self);",
      "Block and wait for the object `self` to stop."
    }, {
      "running", 
      "bool running(var self);",
      "Check if the object `self` is running."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}