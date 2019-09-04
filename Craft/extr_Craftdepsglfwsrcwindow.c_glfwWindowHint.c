#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int api; int major; int minor; int robustness; int profile; int release; void* debug; void* forward; } ;
struct TYPE_7__ {void* visible; void* floating; void* autoIconify; void* focused; void* decorated; void* resizable; } ;
struct TYPE_6__ {int redBits; int greenBits; int blueBits; int alphaBits; int depthBits; int stencilBits; int accumRedBits; int accumGreenBits; int accumBlueBits; int accumAlphaBits; int auxBuffers; int samples; void* sRGB; void* doublebuffer; void* stereo; } ;
struct TYPE_9__ {int refreshRate; TYPE_3__ context; TYPE_2__ window; TYPE_1__ framebuffer; } ;
struct TYPE_10__ {TYPE_4__ hints; } ;

/* Variables and functions */
#define  GLFW_ACCUM_ALPHA_BITS 157 
#define  GLFW_ACCUM_BLUE_BITS 156 
#define  GLFW_ACCUM_GREEN_BITS 155 
#define  GLFW_ACCUM_RED_BITS 154 
#define  GLFW_ALPHA_BITS 153 
#define  GLFW_AUTO_ICONIFY 152 
#define  GLFW_AUX_BUFFERS 151 
#define  GLFW_BLUE_BITS 150 
#define  GLFW_CLIENT_API 149 
#define  GLFW_CONTEXT_RELEASE_BEHAVIOR 148 
#define  GLFW_CONTEXT_ROBUSTNESS 147 
#define  GLFW_CONTEXT_VERSION_MAJOR 146 
#define  GLFW_CONTEXT_VERSION_MINOR 145 
#define  GLFW_DECORATED 144 
#define  GLFW_DEPTH_BITS 143 
#define  GLFW_DOUBLEBUFFER 142 
#define  GLFW_FLOATING 141 
#define  GLFW_FOCUSED 140 
#define  GLFW_GREEN_BITS 139 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
#define  GLFW_OPENGL_DEBUG_CONTEXT 138 
#define  GLFW_OPENGL_FORWARD_COMPAT 137 
#define  GLFW_OPENGL_PROFILE 136 
#define  GLFW_RED_BITS 135 
#define  GLFW_REFRESH_RATE 134 
#define  GLFW_RESIZABLE 133 
#define  GLFW_SAMPLES 132 
#define  GLFW_SRGB_CAPABLE 131 
#define  GLFW_STENCIL_BITS 130 
#define  GLFW_STEREO 129 
#define  GLFW_VISIBLE 128 
 void* GL_FALSE ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

void glfwWindowHint(int target, int hint)
{
    _GLFW_REQUIRE_INIT();

    switch (target)
    {
        case GLFW_RED_BITS:
            _glfw.hints.framebuffer.redBits = hint;
            break;
        case GLFW_GREEN_BITS:
            _glfw.hints.framebuffer.greenBits = hint;
            break;
        case GLFW_BLUE_BITS:
            _glfw.hints.framebuffer.blueBits = hint;
            break;
        case GLFW_ALPHA_BITS:
            _glfw.hints.framebuffer.alphaBits = hint;
            break;
        case GLFW_DEPTH_BITS:
            _glfw.hints.framebuffer.depthBits = hint;
            break;
        case GLFW_STENCIL_BITS:
            _glfw.hints.framebuffer.stencilBits = hint;
            break;
        case GLFW_ACCUM_RED_BITS:
            _glfw.hints.framebuffer.accumRedBits = hint;
            break;
        case GLFW_ACCUM_GREEN_BITS:
            _glfw.hints.framebuffer.accumGreenBits = hint;
            break;
        case GLFW_ACCUM_BLUE_BITS:
            _glfw.hints.framebuffer.accumBlueBits = hint;
            break;
        case GLFW_ACCUM_ALPHA_BITS:
            _glfw.hints.framebuffer.accumAlphaBits = hint;
            break;
        case GLFW_AUX_BUFFERS:
            _glfw.hints.framebuffer.auxBuffers = hint;
            break;
        case GLFW_STEREO:
            _glfw.hints.framebuffer.stereo = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_DOUBLEBUFFER:
            _glfw.hints.framebuffer.doublebuffer = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_SAMPLES:
            _glfw.hints.framebuffer.samples = hint;
            break;
        case GLFW_SRGB_CAPABLE:
            _glfw.hints.framebuffer.sRGB = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_RESIZABLE:
            _glfw.hints.window.resizable = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_DECORATED:
            _glfw.hints.window.decorated = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_FOCUSED:
            _glfw.hints.window.focused = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_AUTO_ICONIFY:
            _glfw.hints.window.autoIconify = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_FLOATING:
            _glfw.hints.window.floating = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_VISIBLE:
            _glfw.hints.window.visible = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_CLIENT_API:
            _glfw.hints.context.api = hint;
            break;
        case GLFW_CONTEXT_VERSION_MAJOR:
            _glfw.hints.context.major = hint;
            break;
        case GLFW_CONTEXT_VERSION_MINOR:
            _glfw.hints.context.minor = hint;
            break;
        case GLFW_CONTEXT_ROBUSTNESS:
            _glfw.hints.context.robustness = hint;
            break;
        case GLFW_OPENGL_FORWARD_COMPAT:
            _glfw.hints.context.forward = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_OPENGL_DEBUG_CONTEXT:
            _glfw.hints.context.debug = hint ? GL_TRUE : GL_FALSE;
            break;
        case GLFW_OPENGL_PROFILE:
            _glfw.hints.context.profile = hint;
            break;
        case GLFW_CONTEXT_RELEASE_BEHAVIOR:
            _glfw.hints.context.release = hint;
            break;
        case GLFW_REFRESH_RATE:
            _glfw.hints.refreshRate = hint;
            break;
        default:
            _glfwInputError(GLFW_INVALID_ENUM, "Invalid window hint");
            break;
    }
}