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
 int GLFW_MOUSE_BUTTON_LEFT ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int glfwGetMouseButton (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

void OnMouseMove( int x, int y ){
  int lState = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);

	if (lState == GLFW_PRESS)
    printf("Dragged %i to %i %i\n", GLFW_MOUSE_BUTTON_LEFT, x, y);
  if(lState == GLFW_RELEASE)
    printf("Moved %i to %i %i\n", GLFW_MOUSE_BUTTON_LEFT, x, y);
}