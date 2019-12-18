#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ api; int major; int minor; int /*<<< orphan*/  release; void* robustness; void* profile; void* debug; void* forward; int /*<<< orphan*/  revision; } ;
struct TYPE_7__ {TYPE_1__ context; int /*<<< orphan*/  (* GetIntegerv ) (int /*<<< orphan*/ ,int*) ;scalar_t__ GetStringi; scalar_t__ Clear; scalar_t__ GetString; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_8__ {scalar_t__ debug; } ;
typedef  TYPE_3__ _GLFWctxconfig ;
typedef  scalar_t__ PFNGLGETSTRINGPROC ;
typedef  scalar_t__ PFNGLGETSTRINGIPROC ;
typedef  int /*<<< orphan*/  (* PFNGLGETINTEGERVPROC ) (int /*<<< orphan*/ ,int*) ;
typedef  scalar_t__ PFNGLCLEARPROC ;
typedef  int GLint ;
typedef  void* GLboolean ;

/* Variables and functions */
 void* GLFW_LOSE_CONTEXT_ON_RESET ; 
 void* GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_API ; 
 void* GLFW_OPENGL_COMPAT_PROFILE ; 
 void* GLFW_OPENGL_CORE_PROFILE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 int /*<<< orphan*/  GLFW_RELEASE_BEHAVIOR_NONE ; 
 int GL_CONTEXT_COMPATIBILITY_PROFILE_BIT ; 
 int GL_CONTEXT_CORE_PROFILE_BIT ; 
 int /*<<< orphan*/  GL_CONTEXT_FLAGS ; 
 int GL_CONTEXT_FLAG_DEBUG_BIT ; 
 int GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT ; 
 int /*<<< orphan*/  GL_CONTEXT_PROFILE_MASK ; 
 int /*<<< orphan*/  GL_CONTEXT_RELEASE_BEHAVIOR ; 
 int GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH ; 
 void* GL_FALSE ; 
 int GL_LOSE_CONTEXT_ON_RESET_ARB ; 
 int GL_NONE ; 
 int GL_NO_RESET_NOTIFICATION_ARB ; 
 int /*<<< orphan*/  GL_RESET_NOTIFICATION_STRATEGY_ARB ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* _glfwPlatformGetCurrentContext () ; 
 scalar_t__ glfwExtensionSupported (char*) ; 
 scalar_t__ glfwGetProcAddress (char*) ; 
 int /*<<< orphan*/  parseVersionString (scalar_t__*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int*) ; 

GLboolean _glfwRefreshContextAttribs(const _GLFWctxconfig* ctxconfig)
{
    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    window->GetIntegerv = (PFNGLGETINTEGERVPROC) glfwGetProcAddress("glGetIntegerv");
    window->GetString = (PFNGLGETSTRINGPROC) glfwGetProcAddress("glGetString");
    window->Clear = (PFNGLCLEARPROC) glfwGetProcAddress("glClear");

    if (!parseVersionString(&window->context.api,
                            &window->context.major,
                            &window->context.minor,
                            &window->context.revision))
    {
        return GL_FALSE;
    }

#if defined(_GLFW_USE_OPENGL)
    if (window->context.major > 2)
    {
        // OpenGL 3.0+ uses a different function for extension string retrieval
        // We cache it here instead of in glfwExtensionSupported mostly to alert
        // users as early as possible that their build may be broken

        window->GetStringi = (PFNGLGETSTRINGIPROC) glfwGetProcAddress("glGetStringi");
        if (!window->GetStringi)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Entry point retrieval is broken");
            return GL_FALSE;
        }
    }

    if (window->context.api == GLFW_OPENGL_API)
    {
        // Read back context flags (OpenGL 3.0 and above)
        if (window->context.major >= 3)
        {
            GLint flags;
            window->GetIntegerv(GL_CONTEXT_FLAGS, &flags);

            if (flags & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT)
                window->context.forward = GL_TRUE;

            if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
                window->context.debug = GL_TRUE;
            else if (glfwExtensionSupported("GL_ARB_debug_output") &&
                     ctxconfig->debug)
            {
                // HACK: This is a workaround for older drivers (pre KHR_debug)
                //       not setting the debug bit in the context flags for
                //       debug contexts
                window->context.debug = GL_TRUE;
            }
        }

        // Read back OpenGL context profile (OpenGL 3.2 and above)
        if (window->context.major > 3 ||
            (window->context.major == 3 && window->context.minor >= 2))
        {
            GLint mask;
            window->GetIntegerv(GL_CONTEXT_PROFILE_MASK, &mask);

            if (mask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
                window->context.profile = GLFW_OPENGL_COMPAT_PROFILE;
            else if (mask & GL_CONTEXT_CORE_PROFILE_BIT)
                window->context.profile = GLFW_OPENGL_CORE_PROFILE;
            else if (glfwExtensionSupported("GL_ARB_compatibility"))
            {
                // HACK: This is a workaround for the compatibility profile bit
                //       not being set in the context flags if an OpenGL 3.2+
                //       context was created without having requested a specific
                //       version
                window->context.profile = GLFW_OPENGL_COMPAT_PROFILE;
            }
        }

        // Read back robustness strategy
        if (glfwExtensionSupported("GL_ARB_robustness"))
        {
            // NOTE: We avoid using the context flags for detection, as they are
            //       only present from 3.0 while the extension applies from 1.1

            GLint strategy;
            window->GetIntegerv(GL_RESET_NOTIFICATION_STRATEGY_ARB, &strategy);

            if (strategy == GL_LOSE_CONTEXT_ON_RESET_ARB)
                window->context.robustness = GLFW_LOSE_CONTEXT_ON_RESET;
            else if (strategy == GL_NO_RESET_NOTIFICATION_ARB)
                window->context.robustness = GLFW_NO_RESET_NOTIFICATION;
        }
    }
    else
    {
        // Read back robustness strategy
        if (glfwExtensionSupported("GL_EXT_robustness"))
        {
            // NOTE: The values of these constants match those of the OpenGL ARB
            //       one, so we can reuse them here

            GLint strategy;
            window->GetIntegerv(GL_RESET_NOTIFICATION_STRATEGY_ARB, &strategy);

            if (strategy == GL_LOSE_CONTEXT_ON_RESET_ARB)
                window->context.robustness = GLFW_LOSE_CONTEXT_ON_RESET;
            else if (strategy == GL_NO_RESET_NOTIFICATION_ARB)
                window->context.robustness = GLFW_NO_RESET_NOTIFICATION;
        }
    }

    if (glfwExtensionSupported("GL_KHR_context_flush_control"))
    {
        GLint behavior;
        window->GetIntegerv(GL_CONTEXT_RELEASE_BEHAVIOR, &behavior);

        if (behavior == GL_NONE)
            window->context.release = GLFW_RELEASE_BEHAVIOR_NONE;
        else if (behavior == GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH)
            window->context.release = GLFW_RELEASE_BEHAVIOR_FLUSH;
    }
#endif // _GLFW_USE_OPENGL

    return GL_TRUE;
}