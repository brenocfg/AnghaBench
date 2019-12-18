#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int api; int major; int minor; int revision; int robustness; int forward; int debug; int profile; int release; } ;
struct TYPE_7__ {int resizable; int decorated; int floating; TYPE_1__ context; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  GLFW_CLIENT_API 142 
#define  GLFW_CONTEXT_RELEASE_BEHAVIOR 141 
#define  GLFW_CONTEXT_REVISION 140 
#define  GLFW_CONTEXT_ROBUSTNESS 139 
#define  GLFW_CONTEXT_VERSION_MAJOR 138 
#define  GLFW_CONTEXT_VERSION_MINOR 137 
#define  GLFW_DECORATED 136 
#define  GLFW_FLOATING 135 
#define  GLFW_FOCUSED 134 
#define  GLFW_ICONIFIED 133 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
#define  GLFW_OPENGL_DEBUG_CONTEXT 132 
#define  GLFW_OPENGL_FORWARD_COMPAT 131 
#define  GLFW_OPENGL_PROFILE 130 
#define  GLFW_RESIZABLE 129 
#define  GLFW_VISIBLE 128 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int _glfwPlatformWindowFocused (TYPE_2__*) ; 
 int _glfwPlatformWindowIconified (TYPE_2__*) ; 
 int _glfwPlatformWindowVisible (TYPE_2__*) ; 

int glfwGetWindowAttrib(GLFWwindow* handle, int attrib)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;

    _GLFW_REQUIRE_INIT_OR_RETURN(0);

    switch (attrib)
    {
        case GLFW_FOCUSED:
            return _glfwPlatformWindowFocused(window);
        case GLFW_ICONIFIED:
            return _glfwPlatformWindowIconified(window);
        case GLFW_VISIBLE:
            return _glfwPlatformWindowVisible(window);
        case GLFW_RESIZABLE:
            return window->resizable;
        case GLFW_DECORATED:
            return window->decorated;
        case GLFW_FLOATING:
            return window->floating;
        case GLFW_CLIENT_API:
            return window->context.api;
        case GLFW_CONTEXT_VERSION_MAJOR:
            return window->context.major;
        case GLFW_CONTEXT_VERSION_MINOR:
            return window->context.minor;
        case GLFW_CONTEXT_REVISION:
            return window->context.revision;
        case GLFW_CONTEXT_ROBUSTNESS:
            return window->context.robustness;
        case GLFW_OPENGL_FORWARD_COMPAT:
            return window->context.forward;
        case GLFW_OPENGL_DEBUG_CONTEXT:
            return window->context.debug;
        case GLFW_OPENGL_PROFILE:
            return window->context.profile;
        case GLFW_CONTEXT_RELEASE_BEHAVIOR:
            return window->context.release;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window attribute");
    return 0;
}