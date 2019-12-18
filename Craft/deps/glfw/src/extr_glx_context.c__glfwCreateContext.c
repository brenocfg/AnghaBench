#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {void* context; int /*<<< orphan*/  visual; } ;
struct TYPE_18__ {TYPE_5__ glx; } ;
typedef  TYPE_6__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWfbconfig ;
struct TYPE_19__ {scalar_t__ api; int forward; scalar_t__ profile; scalar_t__ robustness; scalar_t__ release; int major; int minor; scalar_t__ debug; TYPE_2__* share; } ;
typedef  TYPE_7__ _GLFWctxconfig ;
struct TYPE_16__ {scalar_t__ errorBase; void* (* CreateContextAttribsARB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ;scalar_t__ ARB_context_flush_control; scalar_t__ ARB_create_context_robustness; scalar_t__ ARB_create_context; int /*<<< orphan*/  ARB_create_context_profile; int /*<<< orphan*/  EXT_create_context_es2_profile; } ;
struct TYPE_15__ {scalar_t__ errorCode; int /*<<< orphan*/  display; } ;
struct TYPE_13__ {int /*<<< orphan*/ * context; } ;
struct TYPE_14__ {TYPE_1__ glx; } ;
struct TYPE_12__ {TYPE_4__ glx; TYPE_3__ x11; } ;
typedef  int /*<<< orphan*/ * GLXFBConfig ;
typedef  int /*<<< orphan*/ * GLXContext ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 scalar_t__ GLFW_LOSE_CONTEXT_ON_RESET ; 
 scalar_t__ GLFW_NO_RESET_NOTIFICATION ; 
 scalar_t__ GLFW_OPENGL_ANY_PROFILE ; 
 scalar_t__ GLFW_OPENGL_API ; 
 scalar_t__ GLFW_OPENGL_COMPAT_PROFILE ; 
 scalar_t__ GLFW_OPENGL_CORE_PROFILE ; 
 scalar_t__ GLFW_OPENGL_ES_API ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_FLUSH ; 
 scalar_t__ GLFW_RELEASE_BEHAVIOR_NONE ; 
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 scalar_t__ GLXBadProfileARB ; 
 int GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ; 
 int GLX_CONTEXT_CORE_PROFILE_BIT_ARB ; 
 int GLX_CONTEXT_DEBUG_BIT_ARB ; 
 int GLX_CONTEXT_ES2_PROFILE_BIT_EXT ; 
 int GLX_CONTEXT_FLAGS_ARB ; 
 int GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB ; 
 int GLX_CONTEXT_MAJOR_VERSION_ARB ; 
 int GLX_CONTEXT_MINOR_VERSION_ARB ; 
 int GLX_CONTEXT_PROFILE_MASK_ARB ; 
 int GLX_CONTEXT_RELEASE_BEHAVIOR_ARB ; 
 int GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB ; 
 int GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB ; 
 int GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB ; 
 int GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB ; 
 int GLX_LOSE_CONTEXT_ON_RESET_ARB ; 
 int GLX_NO_RESET_NOTIFICATION_ARB ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 int None ; 
 int /*<<< orphan*/  True ; 
 TYPE_11__ _glfw ; 
 int /*<<< orphan*/  _glfwGrabXErrorHandler () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwInputXError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwReleaseXErrorHandler () ; 
 int /*<<< orphan*/  _glfw_glXGetVisualFromFBConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chooseFBConfig (int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 void* createLegacyContext (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setGLXattrib (int,int) ; 
 void* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

int _glfwCreateContext(_GLFWwindow* window,
                       const _GLFWctxconfig* ctxconfig,
                       const _GLFWfbconfig* fbconfig)
{
    int attribs[40];
    GLXFBConfig native = NULL;
    GLXContext share = NULL;

    if (ctxconfig->share)
        share = ctxconfig->share->glx.context;

    if (!chooseFBConfig(fbconfig, &native))
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "GLX: Failed to find a suitable GLXFBConfig");
        return GL_FALSE;
    }

    window->glx.visual = _glfw_glXGetVisualFromFBConfig(_glfw.x11.display,
                                                        native);
    if (!window->glx.visual)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "GLX: Failed to retrieve visual for GLXFBConfig");
        return GL_FALSE;
    }

    if (ctxconfig->api == GLFW_OPENGL_ES_API)
    {
        if (!_glfw.glx.ARB_create_context ||
            !_glfw.glx.ARB_create_context_profile ||
            !_glfw.glx.EXT_create_context_es2_profile)
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "GLX: OpenGL ES requested but GLX_EXT_create_context_es2_profile is unavailable");
            return GL_FALSE;
        }
    }

    if (ctxconfig->forward)
    {
        if (!_glfw.glx.ARB_create_context)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "GLX: Forward compatibility requested but GLX_ARB_create_context_profile is unavailable");
            return GL_FALSE;
        }
    }

    if (ctxconfig->profile)
    {
        if (!_glfw.glx.ARB_create_context ||
            !_glfw.glx.ARB_create_context_profile)
        {
            _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                            "GLX: An OpenGL profile requested but GLX_ARB_create_context_profile is unavailable");
            return GL_FALSE;
        }
    }

    _glfwGrabXErrorHandler();

    if (_glfw.glx.ARB_create_context)
    {
        int index = 0, mask = 0, flags = 0;

        if (ctxconfig->api == GLFW_OPENGL_API)
        {
            if (ctxconfig->forward)
                flags |= GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;

            if (ctxconfig->profile == GLFW_OPENGL_CORE_PROFILE)
                mask |= GLX_CONTEXT_CORE_PROFILE_BIT_ARB;
            else if (ctxconfig->profile == GLFW_OPENGL_COMPAT_PROFILE)
                mask |= GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
        }
        else
            mask |= GLX_CONTEXT_ES2_PROFILE_BIT_EXT;

        if (ctxconfig->debug)
            flags |= GLX_CONTEXT_DEBUG_BIT_ARB;

        if (ctxconfig->robustness)
        {
            if (_glfw.glx.ARB_create_context_robustness)
            {
                if (ctxconfig->robustness == GLFW_NO_RESET_NOTIFICATION)
                {
                    setGLXattrib(GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                                 GLX_NO_RESET_NOTIFICATION_ARB);
                }
                else if (ctxconfig->robustness == GLFW_LOSE_CONTEXT_ON_RESET)
                {
                    setGLXattrib(GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB,
                                 GLX_LOSE_CONTEXT_ON_RESET_ARB);
                }

                flags |= GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB;
            }
        }

        if (ctxconfig->release)
        {
            if (_glfw.glx.ARB_context_flush_control)
            {
                if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_NONE)
                {
                    setGLXattrib(GLX_CONTEXT_RELEASE_BEHAVIOR_ARB,
                                 GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB);
                }
                else if (ctxconfig->release == GLFW_RELEASE_BEHAVIOR_FLUSH)
                {
                    setGLXattrib(GLX_CONTEXT_RELEASE_BEHAVIOR_ARB,
                                 GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB);
                }
            }
        }

        // NOTE: Only request an explicitly versioned context when necessary, as
        //       explicitly requesting version 1.0 does not always return the
        //       highest version supported by the driver
        if (ctxconfig->major != 1 || ctxconfig->minor != 0)
        {
            setGLXattrib(GLX_CONTEXT_MAJOR_VERSION_ARB, ctxconfig->major);
            setGLXattrib(GLX_CONTEXT_MINOR_VERSION_ARB, ctxconfig->minor);
        }

        if (mask)
            setGLXattrib(GLX_CONTEXT_PROFILE_MASK_ARB, mask);

        if (flags)
            setGLXattrib(GLX_CONTEXT_FLAGS_ARB, flags);

        setGLXattrib(None, None);

        window->glx.context =
            _glfw.glx.CreateContextAttribsARB(_glfw.x11.display,
                                              native,
                                              share,
                                              True,
                                              attribs);

        // HACK: This is a fallback for broken versions of the Mesa
        //       implementation of GLX_ARB_create_context_profile that fail
        //       default 1.0 context creation with a GLXBadProfileARB error in
        //       violation of the extension spec
        if (!window->glx.context)
        {
            if (_glfw.x11.errorCode == _glfw.glx.errorBase + GLXBadProfileARB &&
                ctxconfig->api == GLFW_OPENGL_API &&
                ctxconfig->profile == GLFW_OPENGL_ANY_PROFILE &&
                ctxconfig->forward == GL_FALSE)
            {
                window->glx.context = createLegacyContext(window, native, share);
            }
        }
    }
    else
        window->glx.context = createLegacyContext(window, native, share);

    _glfwReleaseXErrorHandler();

    if (!window->glx.context)
    {
        _glfwInputXError(GLFW_VERSION_UNAVAILABLE, "GLX: Failed to create context");
        return GL_FALSE;
    }

    return GL_TRUE;
}