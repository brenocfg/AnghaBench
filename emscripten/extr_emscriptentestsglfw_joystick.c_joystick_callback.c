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
 int GLFW_CONNECTED ; 
 int GLFW_DISCONNECTED ; 
 char* glfwGetJoystickName (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

void joystick_callback(int joy, int event)
{
  if (event == GLFW_CONNECTED) {
    printf("Joystick %d was connected: %s\n", joy, glfwGetJoystickName(joy));
  } else if (event == GLFW_DISCONNECTED) {
    printf("Joystick %d was disconnected\n", joy);
  }
}