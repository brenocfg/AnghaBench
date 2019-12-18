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

__attribute__((used)) static struct Method* Len_Methods(void) {
  
  static struct Method methods[] = {
    {
      "len", 
      "size_t len(var self);",
      "Returns the length of object `self`."
    }, {NULL, NULL, NULL}
  };
  
  return methods;
}