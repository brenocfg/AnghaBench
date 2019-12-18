#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  dc; } ;
struct TYPE_20__ {TYPE_2__ wgl; } ;
struct TYPE_21__ {TYPE_3__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_22__ {int redBits; int greenBits; int blueBits; int alphaBits; int depthBits; int stencilBits; int accumRedBits; int accumGreenBits; int accumBlueBits; int accumAlphaBits; int auxBuffers; int samples; int handle; void* doublebuffer; void* stereo; void* sRGB; } ;
typedef  TYPE_5__ _GLFWfbconfig ;
struct TYPE_23__ {int dwFlags; scalar_t__ iPixelType; int cRedBits; int cGreenBits; int cBlueBits; int cAlphaBits; int cDepthBits; int cStencilBits; int cAccumRedBits; int cAccumGreenBits; int cAccumBlueBits; int cAccumAlphaBits; int cAuxBuffers; } ;
struct TYPE_18__ {scalar_t__ EXT_framebuffer_sRGB; scalar_t__ ARB_framebuffer_sRGB; scalar_t__ ARB_multisample; scalar_t__ ARB_pixel_format; } ;
struct TYPE_17__ {TYPE_1__ wgl; } ;
typedef  TYPE_6__ PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int DescribePixelFormat (int /*<<< orphan*/ ,int const,int,TYPE_6__*) ; 
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 void* GLFW_TRUE ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int PFD_GENERIC_ACCELERATED ; 
 int PFD_GENERIC_FORMAT ; 
 int PFD_STEREO ; 
 int PFD_SUPPORT_OPENGL ; 
 scalar_t__ PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  WGL_ACCELERATION_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_ALPHA_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_BLUE_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_GREEN_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ACCUM_RED_BITS_ARB ; 
 int /*<<< orphan*/  WGL_ALPHA_BITS_ARB ; 
 int /*<<< orphan*/  WGL_AUX_BUFFERS_ARB ; 
 int /*<<< orphan*/  WGL_BLUE_BITS_ARB ; 
 int /*<<< orphan*/  WGL_DEPTH_BITS_ARB ; 
 int /*<<< orphan*/  WGL_DOUBLE_BUFFER_ARB ; 
 int /*<<< orphan*/  WGL_DRAW_TO_WINDOW_ARB ; 
 int /*<<< orphan*/  WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB ; 
 int /*<<< orphan*/  WGL_GREEN_BITS_ARB ; 
 int WGL_NO_ACCELERATION_ARB ; 
 int /*<<< orphan*/  WGL_NUMBER_PIXEL_FORMATS_ARB ; 
 int /*<<< orphan*/  WGL_PIXEL_TYPE_ARB ; 
 int /*<<< orphan*/  WGL_RED_BITS_ARB ; 
 int /*<<< orphan*/  WGL_SAMPLES_ARB ; 
 int /*<<< orphan*/  WGL_STENCIL_BITS_ARB ; 
 int /*<<< orphan*/  WGL_STEREO_ARB ; 
 int /*<<< orphan*/  WGL_SUPPORT_OPENGL_ARB ; 
 int WGL_TYPE_RGBA_ARB ; 
 TYPE_15__ _glfw ; 
 TYPE_5__* _glfwChooseFBConfig (TYPE_5__ const*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int getPixelFormatAttrib (TYPE_4__*,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int choosePixelFormat(_GLFWwindow* window, const _GLFWfbconfig* desired)
{
    _GLFWfbconfig* usableConfigs;
    const _GLFWfbconfig* closest;
    int i, pixelFormat, nativeCount, usableCount;

    if (_glfw.wgl.ARB_pixel_format)
    {
        nativeCount = getPixelFormatAttrib(window,
                                           1,
                                           WGL_NUMBER_PIXEL_FORMATS_ARB);
    }
    else
    {
        nativeCount = DescribePixelFormat(window->context.wgl.dc,
                                          1,
                                          sizeof(PIXELFORMATDESCRIPTOR),
                                          NULL);
    }

    usableConfigs = calloc(nativeCount, sizeof(_GLFWfbconfig));
    usableCount = 0;

    for (i = 0;  i < nativeCount;  i++)
    {
        const int n = i + 1;
        _GLFWfbconfig* u = usableConfigs + usableCount;

        if (_glfw.wgl.ARB_pixel_format)
        {
            // Get pixel format attributes through "modern" extension

            if (!getPixelFormatAttrib(window, n, WGL_SUPPORT_OPENGL_ARB) ||
                !getPixelFormatAttrib(window, n, WGL_DRAW_TO_WINDOW_ARB))
            {
                continue;
            }

            if (getPixelFormatAttrib(window, n, WGL_PIXEL_TYPE_ARB) !=
                WGL_TYPE_RGBA_ARB)
            {
                continue;
            }

            if (getPixelFormatAttrib(window, n, WGL_ACCELERATION_ARB) ==
                 WGL_NO_ACCELERATION_ARB)
            {
                continue;
            }

            u->redBits = getPixelFormatAttrib(window, n, WGL_RED_BITS_ARB);
            u->greenBits = getPixelFormatAttrib(window, n, WGL_GREEN_BITS_ARB);
            u->blueBits = getPixelFormatAttrib(window, n, WGL_BLUE_BITS_ARB);
            u->alphaBits = getPixelFormatAttrib(window, n, WGL_ALPHA_BITS_ARB);

            u->depthBits = getPixelFormatAttrib(window, n, WGL_DEPTH_BITS_ARB);
            u->stencilBits = getPixelFormatAttrib(window, n, WGL_STENCIL_BITS_ARB);

            u->accumRedBits = getPixelFormatAttrib(window, n, WGL_ACCUM_RED_BITS_ARB);
            u->accumGreenBits = getPixelFormatAttrib(window, n, WGL_ACCUM_GREEN_BITS_ARB);
            u->accumBlueBits = getPixelFormatAttrib(window, n, WGL_ACCUM_BLUE_BITS_ARB);
            u->accumAlphaBits = getPixelFormatAttrib(window, n, WGL_ACCUM_ALPHA_BITS_ARB);

            u->auxBuffers = getPixelFormatAttrib(window, n, WGL_AUX_BUFFERS_ARB);

            if (getPixelFormatAttrib(window, n, WGL_STEREO_ARB))
                u->stereo = GLFW_TRUE;
            if (getPixelFormatAttrib(window, n, WGL_DOUBLE_BUFFER_ARB))
                u->doublebuffer = GLFW_TRUE;

            if (_glfw.wgl.ARB_multisample)
                u->samples = getPixelFormatAttrib(window, n, WGL_SAMPLES_ARB);

            if (_glfw.wgl.ARB_framebuffer_sRGB ||
                _glfw.wgl.EXT_framebuffer_sRGB)
            {
                if (getPixelFormatAttrib(window, n, WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB))
                    u->sRGB = GLFW_TRUE;
            }
        }
        else
        {
            PIXELFORMATDESCRIPTOR pfd;

            // Get pixel format attributes through legacy PFDs

            if (!DescribePixelFormat(window->context.wgl.dc,
                                     n,
                                     sizeof(PIXELFORMATDESCRIPTOR),
                                     &pfd))
            {
                continue;
            }

            if (!(pfd.dwFlags & PFD_DRAW_TO_WINDOW) ||
                !(pfd.dwFlags & PFD_SUPPORT_OPENGL))
            {
                continue;
            }

            if (!(pfd.dwFlags & PFD_GENERIC_ACCELERATED) &&
                (pfd.dwFlags & PFD_GENERIC_FORMAT))
            {
                continue;
            }

            if (pfd.iPixelType != PFD_TYPE_RGBA)
                continue;

            u->redBits = pfd.cRedBits;
            u->greenBits = pfd.cGreenBits;
            u->blueBits = pfd.cBlueBits;
            u->alphaBits = pfd.cAlphaBits;

            u->depthBits = pfd.cDepthBits;
            u->stencilBits = pfd.cStencilBits;

            u->accumRedBits = pfd.cAccumRedBits;
            u->accumGreenBits = pfd.cAccumGreenBits;
            u->accumBlueBits = pfd.cAccumBlueBits;
            u->accumAlphaBits = pfd.cAccumAlphaBits;

            u->auxBuffers = pfd.cAuxBuffers;

            if (pfd.dwFlags & PFD_STEREO)
                u->stereo = GLFW_TRUE;
            if (pfd.dwFlags & PFD_DOUBLEBUFFER)
                u->doublebuffer = GLFW_TRUE;
        }

        u->handle = n;
        usableCount++;
    }

    if (!usableCount)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "WGL: The driver does not appear to support OpenGL");

        free(usableConfigs);
        return 0;
    }

    closest = _glfwChooseFBConfig(desired, usableConfigs, usableCount);
    if (!closest)
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "WGL: Failed to find a suitable pixel format");

        free(usableConfigs);
        return 0;
    }

    pixelFormat = (int) closest->handle;
    free(usableConfigs);

    return pixelFormat;
}