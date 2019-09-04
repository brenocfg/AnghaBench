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
 int /*<<< orphan*/  printf (char*,unsigned long) ; 

int main(int argc, char **argv) {
  unsigned long d1 = 0x847c9b5d;
  unsigned long q = 0x549530e1;
  if (argc > 1000) {
    q += argc;
    d1 -= argc;
  }  // confuse optimizer
  printf("%lu\n", d1 * q);
  return 0;
}