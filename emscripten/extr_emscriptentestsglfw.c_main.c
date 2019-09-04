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
 int /*<<< orphan*/  Init () ; 
 int /*<<< orphan*/  Iteration ; 
 int /*<<< orphan*/  Shut_Down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwGetTime () ; 
 int /*<<< orphan*/  old_time ; 

int main(void)
{
  Init();
  old_time = glfwGetTime();
  emscripten_set_main_loop (Iteration, 0, 1);
  Shut_Down(0);
}