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

__attribute__((used)) static struct Method* Doc_Methods(void) {
  
  static struct Method methods[] = {
    {
      "name", 
      "const char* name(var type);",
      "Return the name of a given `type`."
    }, {
      "brief", 
      "const char* brief(var type);",
      "Return a brief description of a given `type`."
    }, {
      "description", 
      "const char* description(var type);",
      "Return a longer description of a given `type`."
    }, {
      "definition", 
      "const char* definition(var type);",
      "Return the C definition of a given `type`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}