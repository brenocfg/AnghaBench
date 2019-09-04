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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,short,short) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,short*,short*) ; 

int main() {
  short int x;
  short int y;

  const char* buffer[] = {"173,16",      "    16,173",   "183,   173",
                          "  17,   287", " 98,  123,   "};

  for (int i = 0; i < 5; ++i) {
    sscanf(buffer[i], "%hd,%hd", &x, &y);
    printf("%d:%d,%d ", i, x, y);
  }

  return 0;
}