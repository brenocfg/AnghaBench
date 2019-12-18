#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pfd ;
struct TYPE_15__ {scalar_t__ context; int /*<<< orphan*/  dc; scalar_t__ (* CreateContextAttribsARB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ;scalar_t__ ARB_context_flush_control; scalar_t__ ARB_create_context_robustness; scalar_t__ ARB_create_context; } ;
struct TYPE_14__ {int /*<<< orphan*/  handle; } ;
struct TYPE_16__ {TYPE_4__ wgl; TYPE_3__ win32; } ;
typedef  TYPE_5__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
struct TYPE_17__ {scalar_t__ api; scalar_t__ profile; scalar_t__ robustness; scalar_t__ release; int major; int minor; scalar_t__ debug; scalar_t__ forward; TYPE_2__* share; } ;
typedef  TYPE_6__ _GLFWctxconfig ;
struct TYPE_12__ {int /*<<< orphan*/ * context; } ;
struct TYPE_13__ {TYPE_1__ wgl; } ;
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/ * HGLRC ;

/* Variables and functions */
 int /*<<< orphan*/  DescribePixelFormat (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ GLFW_LOSE_CONTEXT_ON_RESET ; 
 scalar_t__ GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_API ; 
 scalar_t__ GLFW_OPENGL_COMPAT_PROFILE ; 
 scalar_t__ GLFW_OPENGL_CORE_PROFILE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_NONE ; 
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ; 
 int WGL_CONTEXT_CORE_PROFILE_BIT_ARB ; 
 int WGL_CONTEXT_DEBUG_BIT_ARB ; 
 int WGL_CONTEXT_ES2_PROFILE_BIT_EXT ; 
 int /*<<< orphan*/  WGL_CONTEXT_FLAGS_ARB ; 
 int WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB ; 
 int /*<<< orphan*/  WGL_CONTEXT_MAJOR_VERSION_ARB ; 
 int /*<<< orphan*/  WGL_CONTEXT_MINOR_VERSION_ARB ; 
 int /*<<< orphan*/  WGL_CONTEXT_PROFILE_MASK_ARB ; 
 int /*<<< orphan*/  WGL_CONTEXT_RELEASE_BEHAVIOR_ARB ; 
 int WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB ; 
 int WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB ; 
 int /*<<< orphan*/  WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB ; 
 int WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB ; 
 int WGL_LOSE_CONTEXT_ON_RESET_ARB ; 
 int WGL_NO_RESET_NOTIFICATION_ARB ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwPlatformMakeContextCurrent (TYPE_5__*) ; 
 scalar_t__ _glfw_wglCreateContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfw_wglShareLists (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  choosePixelFormat (TYPE_5__*,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  initWGLExtensions (TYPE_5__*) ; 
 int /*<<< orphan*/  setWGLattrib (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

int _glfwCreateContext(_GLFWwindow* window,
                       const _GLFWctxconfig* ctxconfig,
                       const _GLFWfbconfig* fbconfig)
{
    int attribs[40];
    int pixelFormat = 0;
    PIXELFORMATDESCRIPTOR pfd;
    HGLRC share = NULL;

    if (ctxconfig->share)
        share = ctxconfig->share->wgl.context;

    window->wgl.dc = GetDC(window->win32.handle);
    if (!window->wgl.dc)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "WGL: Failed to retrieve DC for window");
        return GL_FALSE;
    }

    if (!choosePixelFormat(window, fbconfig, &pixelFormat))
        return GL_FALSE;

    if (!DescribePixelFormat(window->wgl.dc, pixelFormat, sizeof(pfd), &pfd))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "WGL: Failed to retrieve PFD for selected pixel format");
        return GL_FALSE;
    }

    if (!SetPixelFormat(window->wgl.dc, pixelFormat, &pfd))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "WGL: Failed to set selected pixel format");
        return GL_FALSE;
    }

    if (window->wgl.ARB_create_context)
    {
        int index = 0, mask = 0, flags = 0;

        if (ctxconfig->api == GLFW_OPENGL_API)
        {
            if (ctxconfig->forward)
                flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

            if (ctxconfig->profile == GLFW_OPENGL_CORE_PROFILE)
                mask |= WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
            else if (ctxconfig->profile == GLFW_OPENGL_COMPAT_PROFILE)
                mask |= WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        }
        else
            mask |= WGL_CONTEXT_ES2_PROFILE_BIT_EXT;

        if (ctxconfig->debug)
            flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

        if (ctxconfig->robustness)
        {
            if (window->wgl.ARB_create_context_robustness)
            {
                if (ctxconfig->robustness == GLFW_NO_RESET_NOTIFICATION)
                {
                    setWGLattrib(WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                                 WGL_NO_RESET_NOTIFICATION_ARB);
                }
                else if (ctxconfig->robustness == GLFW_LOSE_CONTEXT_ON_RESET)
                {
                    setWGLattrib(WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                                 WGL_LOSE_CONTEXT_ON_RESET_ARB);
                }

                flags |= WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB;
            }
        }

        if (ctxconfig->release)
        {
            if (window->wgl.ARB_context_flush_control)
            {
                if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_NONE)
                {
                    setWGLattrib(WGL_CONTEXT_RELEASE_BEHAVIOR_ARB,
                                 WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB);
                }
                else if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_FLUSH)
                {
                    setWGLattrib(WGL_CONTEXT_RELEASE_BEHAVIOR_ARB,
                                 WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB);
                }
            }
        }

        // NOTE: Only request an explicitly versioned context when necessary, as
        //       explicitly requesting version 1.0 does not always return the
        //       highest version supported by the driver
        if (ctxconfig->major != 1 || ctxconfig->minor != 0)
        {
            setWGLattrib(WGL_CONTEXT_MAJOR_VERSION_ARB, ctxconfig->major);
            setWGLattrib(WGL_CONTEXT_MINOR_VERSION_ARB, ctxconfig->minor);
        }

        if (flags)
            setWGLattrib(WGL_CONTEXT_FLAGS_ARB, flags);

        if (mask)
            setWGLattrib(WGL_CONTEXT_PROFILE_MASK_ARB, mask);

        setWGLattrib(0, 0);

        window->wgl.context = window->wgl.CreateContextAttribsARB(window->wgl.dc,
                                                                  share,
                                                                  attribs);
        if (!window->wgl.context)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "WGL: Failed to create OpenGL context");
            return GL_FALSE;
        }
    }
    else
    {
        window->wgl.context = _glfw_wglCreateContext(window->wgl.dc);
        if (!window->wgl.context)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "WGL: Failed to create OpenGL context");
            return GL_FALSE;
        }

        if (share)
        {
            if (!_glfw_wglShareLists(share, window->wgl.context))
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "WGL: Failed to enable sharing with specified OpenGL context");
                return GL_FALSE;
            }
        }
    }

    _glfwPlatformMakeContextCurrent(window);
    initWGLExtensions(window);

    return GL_TRUE;
}