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
 int GLFW_JOYSTICK_1 ; 
 int GLFW_JOYSTICK_16 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 float* glfwGetJoystickAxes (int,int*) ; 
 unsigned char* glfwGetJoystickButtons (int,int*) ; 
 char* glfwGetJoystickName (int) ; 
 int /*<<< orphan*/  glfwJoystickPresent (int) ; 
 int /*<<< orphan*/  printf (char*,int,char const*,int,unsigned char const) ; 

void render() {
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  for (int j = GLFW_JOYSTICK_1; j < GLFW_JOYSTICK_16; ++j) {
    int joy = GLFW_JOYSTICK_1 + j;
    if (!glfwJoystickPresent(joy)) continue;

    static struct {
      int axes_count;
      float axes[16];
      int button_count;
      unsigned char buttons[16];
    } last_gamepad_state[16] = {0};

    const char *name = glfwGetJoystickName(joy);

    int axes_count = 0;
    const float *axes = glfwGetJoystickAxes(joy, &axes_count);

    int button_count = 0;
    const unsigned char *buttons = glfwGetJoystickButtons(joy, &button_count);

    last_gamepad_state[joy].axes_count = axes_count;
    for (int i = 0; i < axes_count; ++i) {
      if (last_gamepad_state[joy].axes[i] != axes[i]) {
        printf("(%d %s) axis %d = %f\n", joy, name, i, axes[i]);
      }

      last_gamepad_state[joy].axes[i] = axes[i];
    }

    last_gamepad_state[joy].button_count =  button_count;
    for (int i = 0; i < button_count; ++i) {
      if (last_gamepad_state[joy].buttons[i] != buttons[i]) {
        printf("(%d %s) button %d = %d\n", joy, name, i, buttons[i]);
      }

      last_gamepad_state[joy].buttons[i] = buttons[i];
    }
  }
}