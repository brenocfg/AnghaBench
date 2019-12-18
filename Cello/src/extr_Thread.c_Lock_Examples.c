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
struct Example {char* member_0; char* member_1; } ;

/* Variables and functions */

__attribute__((used)) static struct Example* Lock_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "var x = new(Mutex);\n"
      "lock(x);   /* Lock Mutex */ \n"
      "print(\"Inside Mutex!\\n\");\n"
      "unlock(x); /* Unlock Mutex */"
    }, {NULL, NULL}
  };

  return examples;
  
}