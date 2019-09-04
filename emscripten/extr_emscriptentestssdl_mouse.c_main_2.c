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
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one ; 

void main_2(void* arg) {
  emscripten_run_script("window.simulateMouseEvent(10, 20, -1)"); // move from 0,0 to 10,20
  emscripten_run_script("window.simulateMouseEvent(10, 20, 0)"); // click
  emscripten_run_script("window.simulateMouseEvent(10, 20, 0)"); // click some more, but this one should be ignored through PeepEvent
  emscripten_run_script("window.simulateMouseEvent(30, 77, -1)"); // move some more
  emscripten_run_script("window.simulateMouseEvent(30, 77, 1)"); // trigger the end

  emscripten_set_main_loop(one, 0, 0);
}