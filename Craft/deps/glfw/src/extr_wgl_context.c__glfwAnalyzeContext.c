#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ARB_pixel_format; scalar_t__ EXT_framebuffer_sRGB; scalar_t__ ARB_framebuffer_sRGB; scalar_t__ ARB_multisample; scalar_t__ ARB_create_context; int /*<<< orphan*/  EXT_create_context_es2_profile; int /*<<< orphan*/  ARB_create_context_profile; scalar_t__ ARB_context_flush_control; } ;
struct TYPE_9__ {TYPE_1__ wgl; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_10__ {scalar_t__ samples; scalar_t__ sRGB; } ;
typedef  TYPE_3__ _GLFWfbconfig ;
struct TYPE_11__ {scalar_t__ api; int major; scalar_t__ minor; scalar_t__ debug; scalar_t__ release; scalar_t__ profile; scalar_t__ forward; } ;
typedef  TYPE_4__ _GLFWctxconfig ;
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 scalar_t__ GLFW_OPENGL_API ; 
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 scalar_t__ GL_FALSE ; 
 scalar_t__ GL_TRUE ; 
 int _GLFW_RECREATION_IMPOSSIBLE ; 
 int _GLFW_RECREATION_NOT_NEEDED ; 
 int _GLFW_RECREATION_REQUIRED ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

int _glfwAnalyzeContext(const _GLFWwindow* window,
                        const _GLFWctxconfig* ctxconfig,
                        const _GLFWfbconfig* fbconfig)
{
    GLboolean required = GL_FALSE;

    if (ctxconfig->api == GLFW_OPENGL_API)
    {
        if (ctxconfig->forward)
        {
            if (!window->wgl.ARB_create_context)
            {
                _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                                "WGL: A forward compatible OpenGL context requested but WGL_ARB_create_context is unavailable");
                return _GLFW_RECREATION_IMPOSSIBLE;
            }

            required = GL_TRUE;
        }

        if (ctxconfig->profile)
        {
            if (!window->wgl.ARB_create_context_profile)
            {
                _glfwInputError(GLFW_VERSION_UNAVAILABLE,
                                "WGL: OpenGL profile requested but WGL_ARB_create_context_profile is unavailable");
                return _GLFW_RECREATION_IMPOSSIBLE;
            }

            required = GL_TRUE;
        }

        if (ctxconfig->release)
        {
            if (window->wgl.ARB_context_flush_control)
                required = GL_TRUE;
        }
    }
    else
    {
        if (!window->wgl.ARB_create_context ||
            !window->wgl.ARB_create_context_profile ||
            !window->wgl.EXT_create_context_es2_profile)
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "WGL: OpenGL ES requested but WGL_ARB_create_context_es2_profile is unavailable");
            return _GLFW_RECREATION_IMPOSSIBLE;
        }

        required = GL_TRUE;
    }

    if (ctxconfig->major != 1 || ctxconfig->minor != 0)
    {
        if (window->wgl.ARB_create_context)
            required = GL_TRUE;
    }

    if (ctxconfig->debug)
    {
        if (window->wgl.ARB_create_context)
            required = GL_TRUE;
    }

    if (fbconfig->samples > 0)
    {
        // MSAA is not a hard constraint, so do nothing if it's not supported
        if (window->wgl.ARB_multisample && window->wgl.ARB_pixel_format)
            required = GL_TRUE;
    }

    if (fbconfig->sRGB)
    {
        // sRGB is not a hard constraint, so do nothing if it's not supported
        if ((window->wgl.ARB_framebuffer_sRGB ||
             window->wgl.EXT_framebuffer_sRGB) &&
            window->wgl.ARB_pixel_format)
        {
            required = GL_TRUE;
        }
    }

    if (required)
        return _GLFW_RECREATION_REQUIRED;

    return _GLFW_RECREATION_NOT_NEEDED;
}