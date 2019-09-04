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
 int /*<<< orphan*/  GLFW_JOYSTICK_1 ; 
 int /*<<< orphan*/  GLFW_JOYSTICK_2 ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_run_script (char*) ; 
 float* glfwGetJoystickAxes (int /*<<< orphan*/ ,int*) ; 
 unsigned char* glfwGetJoystickButtons (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glfwGetJoystickName (int /*<<< orphan*/ ) ; 
 int glfwJoystickPresent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void main_2(void *arg) {
  printf("Testing adding new gamepads\n");
  emscripten_run_script("window.addNewGamepad('Pad Thai', 4, 16)");
  emscripten_run_script("window.addNewGamepad('Pad Kee Mao', 0, 4)");
  // Check that the joysticks exist properly.
  assert(glfwJoystickPresent(GLFW_JOYSTICK_1));
  assert(glfwJoystickPresent(GLFW_JOYSTICK_2));

  assert(strcmp(glfwGetJoystickName(GLFW_JOYSTICK_1), "Pad Thai") == 0);
  assert(strcmp(glfwGetJoystickName(GLFW_JOYSTICK_2), "Pad Kee Mao") == 0);

  int axes_count = 0;
  int buttons_count = 0;

  glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
  glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
  assert(axes_count == 4);
  assert(buttons_count == 16);

  glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axes_count);
  glfwGetJoystickButtons(GLFW_JOYSTICK_2, &buttons_count);
  assert(axes_count == 0);
  assert(buttons_count == 4);

  // Buttons
  printf("Testing buttons\n");
  const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
  assert(buttons_count == 16);
  assert(buttons[0] == 0);
  emscripten_run_script("window.simulateGamepadButtonDown(0, 1)");
  buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
  assert(buttons_count == 16);
  assert(buttons[1] == 1);

  emscripten_run_script("window.simulateGamepadButtonUp(0, 1)");
  buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
  assert(buttons_count == 16);
  assert(buttons[1] == 0);


  emscripten_run_script("window.simulateGamepadButtonDown(1, 0)");
  buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &buttons_count);
  assert(buttons_count == 4);
  assert(buttons[0] == 1);

  emscripten_run_script("window.simulateGamepadButtonUp(1, 0)");
  buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &buttons_count);
  assert(buttons_count == 4);
  assert(buttons[1] == 0);

  // Joystick wiggling
  printf("Testing joystick axes\n");
  emscripten_run_script("window.simulateAxisMotion(0, 0, 1)");
  const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
  assert(axes_count == 4);
  assert(axes[0] == 1);

  emscripten_run_script("window.simulateAxisMotion(0, 0, 0)");
  axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
  assert(axes_count == 4);
  assert(axes[0] == 0);

  emscripten_run_script("window.simulateAxisMotion(0, 1, -1)");
  axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
  assert(axes_count == 4);
  assert(axes[1] == -1);

  // End test.
  printf("Test passed!\n");
  REPORT_RESULT(2);
}