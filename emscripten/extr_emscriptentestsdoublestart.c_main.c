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
 int /*<<< orphan*/  emscripten_async_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  later ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  times ; 

int main(void) {
  emscripten_async_call(later, NULL, 2000);
  times++;
  printf("This should only appear once.\n");
  emscripten_set_main_loop(main_loop, 10, 0);
  return 0;
}