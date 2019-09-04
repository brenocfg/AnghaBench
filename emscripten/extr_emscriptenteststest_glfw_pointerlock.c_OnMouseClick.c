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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int actions ; 
 int /*<<< orphan*/  emscripten_cancel_main_loop () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  result ; 

void OnMouseClick(GLFWwindow *window, int button, int action, int mods) {
  actions++;
  printf("mouse actions: %d / 4\n", actions);
  if (actions >= 4) {
    printf("done.\n");
    REPORT_RESULT(result);
    emscripten_cancel_main_loop();
  }
}