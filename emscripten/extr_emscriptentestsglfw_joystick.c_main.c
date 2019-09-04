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
 int /*<<< orphan*/  GLFW_RESIZABLE ; 
 int /*<<< orphan*/  g_window ; 
 int /*<<< orphan*/  glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetJoystickCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  joystick_callback ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  window ; 

int main() {
  if (!glfwInit())
  {
    printf("Could not create window. Test failed.\n");
#ifdef REPORT_RESULT
    REPORT_RESULT(0);
#endif
    return -1;
  }
  glfwWindowHint(GLFW_RESIZABLE , 1);
  g_window = glfwCreateWindow(600, 450, "GLFW joystick test", NULL, NULL);
  if (!g_window)
  {
    printf("Could not create window. Test failed.\n");
#ifdef REPORT_RESULT
    REPORT_RESULT(0);
#endif
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(g_window);
  glfwSetJoystickCallback(joystick_callback);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(render, 0, 1);
#else
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
#endif

  glfwTerminate();

  return 0;
}