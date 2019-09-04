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
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void OnMouseClick( int button, int action ){
  if(action == GLFW_PRESS)
    printf("Mouse button %i has been pressed\n", button);
  if(action == GLFW_RELEASE)
    printf("Mouse button %i has been released\n", button);
}