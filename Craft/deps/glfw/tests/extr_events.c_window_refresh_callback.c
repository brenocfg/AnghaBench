#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int number; } ;
typedef  TYPE_1__ Slot ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  counter ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 double glfwGetTime () ; 
 TYPE_1__* glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,double) ; 

__attribute__((used)) static void window_refresh_callback(GLFWwindow* window)
{
    Slot* slot = glfwGetWindowUserPointer(window);
    printf("%08x to %i at %0.3f: Window refresh\n",
           counter++, slot->number, glfwGetTime());

    glfwMakeContextCurrent(window);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}