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

__attribute__((used)) static struct Example* C_Float_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "printf(\"%f\", c_float($F(5.1))); /* 5.1 */\n"
      "printf(\"%f\", c_float($F(6.2))); /* 6.2 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}