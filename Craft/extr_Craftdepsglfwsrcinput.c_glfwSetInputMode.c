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
typedef  int /*<<< orphan*/  _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  GLFW_CURSOR 130 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
#define  GLFW_STICKY_KEYS 129 
#define  GLFW_STICKY_MOUSE_BUTTONS 128 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setCursorMode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setStickyKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setStickyMouseButtons (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void glfwSetInputMode(GLFWwindow* handle, int mode, int value)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;

    _GLFW_REQUIRE_INIT();

    switch (mode)
    {
        case GLFW_CURSOR:
            setCursorMode(window, value);
            break;
        case GLFW_STICKY_KEYS:
            setStickyKeys(window, value ? GL_TRUE : GL_FALSE);
            break;
        case GLFW_STICKY_MOUSE_BUTTONS:
            setStickyMouseButtons(window, value ? GL_TRUE : GL_FALSE);
            break;
        default:
            _glfwInputError(GLFW_INVALID_ENUM, "Invalid input mode");
            break;
    }
}