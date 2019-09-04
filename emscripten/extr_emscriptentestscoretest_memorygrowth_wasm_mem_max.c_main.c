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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ malloc (int const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main() {
  const int MB = 1024 * 1024;
  // Memory size starts at 64MB, and max is 100. allocate enough
  // to prove we can grow. 70 is enough to prove we can grow,
  // higher can prove we stop at the right point.
  for (int i = 0; 1; i++) {
    printf("%d\n", i);
    volatile int sink = (int)malloc(MB);
    if (!sink) {
      printf("failed at %d\n", i);
      assert(i > 70);
      break;
    }
    assert(i <= 100); // the wasm mem max limit, we must not get there
  }
  printf("grew memory ok.\n");
}