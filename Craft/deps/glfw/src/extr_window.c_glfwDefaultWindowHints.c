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
struct TYPE_8__ {int redBits; int greenBits; int blueBits; int alphaBits; int depthBits; int stencilBits; void* doublebuffer; } ;
struct TYPE_7__ {void* autoIconify; void* focused; void* decorated; void* visible; void* resizable; } ;
struct TYPE_6__ {int major; scalar_t__ minor; int /*<<< orphan*/  api; } ;
struct TYPE_9__ {int /*<<< orphan*/  refreshRate; TYPE_3__ framebuffer; TYPE_2__ window; TYPE_1__ context; } ;
struct TYPE_10__ {TYPE_4__ hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_DONT_CARE ; 
 int /*<<< orphan*/  GLFW_OPENGL_API ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void glfwDefaultWindowHints(void)
{
    _GLFW_REQUIRE_INIT();

    memset(&_glfw.hints, 0, sizeof(_glfw.hints));

    // The default is OpenGL with minimum version 1.0
    _glfw.hints.context.api   = GLFW_OPENGL_API;
    _glfw.hints.context.major = 1;
    _glfw.hints.context.minor = 0;

    // The default is a focused, visible, resizable window with decorations
    _glfw.hints.window.resizable   = GL_TRUE;
    _glfw.hints.window.visible     = GL_TRUE;
    _glfw.hints.window.decorated   = GL_TRUE;
    _glfw.hints.window.focused     = GL_TRUE;
    _glfw.hints.window.autoIconify = GL_TRUE;

    // The default is 24 bits of color, 24 bits of depth and 8 bits of stencil,
    // double buffered
    _glfw.hints.framebuffer.redBits      = 8;
    _glfw.hints.framebuffer.greenBits    = 8;
    _glfw.hints.framebuffer.blueBits     = 8;
    _glfw.hints.framebuffer.alphaBits    = 8;
    _glfw.hints.framebuffer.depthBits    = 24;
    _glfw.hints.framebuffer.stencilBits  = 8;
    _glfw.hints.framebuffer.doublebuffer = GL_TRUE;

    // The default is to select the highest available refresh rate
    _glfw.hints.refreshRate = GLFW_DONT_CARE;
}