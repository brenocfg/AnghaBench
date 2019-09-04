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
 int /*<<< orphan*/  abortframe ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

void dostuff(int a) {
  printf("pre\n");
  if (a != 42)
    emscripten_run_script(
        "waka_waka()");  // this should fail, and never reach "never"
  printf("never\n");

  if (a == 100) {
    longjmp(abortframe, -1);
  }

  if (setjmp(abortframe)) {
    printf("got 100");
  }
}