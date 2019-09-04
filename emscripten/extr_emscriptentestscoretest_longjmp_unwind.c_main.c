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
 scalar_t__ MINOR ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  foo () ; 
 int get_stack () ; 
 int /*<<< orphan*/  jb ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 

int main()
{
  int before = get_stack();
  printf("before setjmp: %d\n", before);

  if (!setjmp(jb)) {
    foo();
    return 0;
  } else {
    int after = get_stack();
    printf("before setjmp: %d\n", after);
    assert(abs(after - before) < MINOR); // stack has been unwound (but may have minor printf changes
    printf("ok.\n");
    return 1;
  }
}