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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char** argv) {
  int y = -133;
  int64_t x = ((int64_t)((short)(y))) * (100 + argc);
  if (x > 0)
    printf(">0\n");
  else
    printf("<=0\n");
}