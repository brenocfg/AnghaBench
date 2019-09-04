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
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  first () ; 
 int /*<<< orphan*/ * fp ; 
 int /*<<< orphan*/  printf (char*,int volatile) ; 
 int /*<<< orphan*/ * second ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
  fp = argc == 200 ? NULL : second;

  volatile int x = 0;
  if (!setjmp(buf)) {
    x++;
    first();                  // when executed, setjmp returns 0
  } else {                    // when longjmp jumps back, setjmp returns 1
    printf("main: %d\n", x);  // prints
  }

  return 0;
}