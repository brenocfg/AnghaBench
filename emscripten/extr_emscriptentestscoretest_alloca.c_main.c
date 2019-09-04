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
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

int main(int argc, char **argv) {
  char *pc, *pc2;
  assert(argc == 1);
  pc = (char *)alloca(4+argc);
  assert(((int)pc) % 4 == 0);
  pc2 = (char *)alloca(4+argc);
  assert(((int)pc2) % 4 == 0);
  printf("z:%d*%d*%d*\n", (int)pc > 0, (int)pc, (int)pc2);
  return 0;
}