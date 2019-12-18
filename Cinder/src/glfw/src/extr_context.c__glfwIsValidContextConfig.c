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
struct TYPE_3__ {scalar_t__ source; scalar_t__ client; int major; int minor; int profile; int robustness; int release; scalar_t__ forward; } ;
typedef  TYPE_1__ _GLFWctxconfig ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 scalar_t__ GLFW_EGL_CONTEXT_API ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int GLFW_LOSE_CONTEXT_ON_RESET ; 
 scalar_t__ GLFW_NATIVE_CONTEXT_API ; 
 scalar_t__ GLFW_NO_API ; 
 int GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_API ; 
 int GLFW_OPENGL_COMPAT_PROFILE ; 
 int GLFW_OPENGL_CORE_PROFILE ; 
 scalar_t__ GLFW_OPENGL_ES_API ; 
 int GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 int GLFW_RELEASE_BEHAVIOR_NONE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 

GLFWbool _glfwIsValidContextConfig(const _GLFWctxconfig* ctxconfig)
{
    if (ctxconfig->source != GLFW_NATIVE_CONTEXT_API &&
        ctxconfig->source != GLFW_EGL_CONTEXT_API)
    {
        _glfwInputError(GLFW_INVALID_ENUM,
                        "Invalid context creation API %i",
                        ctxconfig->source);
        return GLFW_FALSE;
    }

    if (ctxconfig->client != GLFW_NO_API &&
        ctxconfig->client != GLFW_OPENGL_API &&
        ctxconfig->client != GLFW_OPENGL_ES_API)
    {
        _glfwInputError(GLFW_INVALID_ENUM,
                        "Invalid client API %i",
                        ctxconfig->client);
        return GLFW_FALSE;
    }

    if (ctxconfig->client == GLFW_OPENGL_API)
    {
        if ((ctxconfig->major < 1 || ctxconfig->minor < 0) ||
            (ctxconfig->major == 1 && ctxconfig->minor > 5) ||
            (ctxconfig->major == 2 && ctxconfig->minor > 1) ||
            (ctxconfig->major == 3 && ctxconfig->minor > 3))
        {
            // OpenGL 1.0 is the smallest valid version
            // OpenGL 1.x series ended with version 1.5
            // OpenGL 2.x series ended with version 2.1
            // OpenGL 3.x series ended with version 3.3
            // For now, let everything else through

            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid OpenGL version %i.%i",
                            ctxconfig->major, ctxconfig->minor);
            return GLFW_FALSE;
        }

        if (ctxconfig->profile)
        {
            if (ctxconfig->profile != GLFW_OPENGL_CORE_PROFILE &&
                ctxconfig->profile != GLFW_OPENGL_COMPAT_PROFILE)
            {
                _glfwInputError(GLFW_INVALID_ENUM,
                                "Invalid OpenGL profile %i",
                                ctxconfig->profile);
                return GLFW_FALSE;
            }

            if (ctxconfig->major <= 2 ||
                (ctxconfig->major == 3 && ctxconfig->minor < 2))
            {
                // Desktop OpenGL context profiles are only defined for version 3.2
                // and above

                _glfwInputError(GLFW_INVALID_VALUE,
                                "Context profiles are only defined for OpenGL version 3.2 and above");
                return GLFW_FALSE;
            }
        }

        if (ctxconfig->forward && ctxconfig->major <= 2)
        {
            // Forward-compatible contexts are only defined for OpenGL version 3.0 and above
            _glfwInputError(GLFW_INVALID_VALUE,
                            "Forward-compatibility is only defined for OpenGL version 3.0 and above");
            return GLFW_FALSE;
        }
    }
    else if (ctxconfig->client == GLFW_OPENGL_ES_API)
    {
        if (ctxconfig->major < 1 || ctxconfig->minor < 0 ||
            (ctxconfig->major == 1 && ctxconfig->minor > 1) ||
            (ctxconfig->major == 2 && ctxconfig->minor > 0))
        {
            // OpenGL ES 1.0 is the smallest valid version
            // OpenGL ES 1.x series ended with version 1.1
            // OpenGL ES 2.x series ended with version 2.0
            // For now, let everything else through

            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid OpenGL ES version %i.%i",
                            ctxconfig->major, ctxconfig->minor);
            return GLFW_FALSE;
        }
    }

    if (ctxconfig->robustness)
    {
        if (ctxconfig->robustness != GLFW_NO_RESET_NOTIFICATION &&
            ctxconfig->robustness != GLFW_LOSE_CONTEXT_ON_RESET)
        {
            _glfwInputError(GLFW_INVALID_ENUM,
                            "Invalid context robustness mode %i",
                            ctxconfig->robustness);
            return GLFW_FALSE;
        }
    }

    if (ctxconfig->release)
    {
        if (ctxconfig->release != GLFW_RELEASE_BEHAVIOR_NONE &&
            ctxconfig->release != GLFW_RELEASE_BEHAVIOR_FLUSH)
        {
            _glfwInputError(GLFW_INVALID_ENUM,
                            "Invalid context release behavior %i",
                            ctxconfig->release);
            return GLFW_FALSE;
        }
    }

    return GLFW_TRUE;
}