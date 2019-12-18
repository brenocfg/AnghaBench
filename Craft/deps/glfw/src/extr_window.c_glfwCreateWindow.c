#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int width; int height; char const* title; void* focused; void* visible; int /*<<< orphan*/ * monitor; int /*<<< orphan*/  floating; int /*<<< orphan*/  autoIconify; int /*<<< orphan*/  decorated; void* resizable; } ;
typedef  TYPE_3__ _GLFWwndconfig ;
struct TYPE_23__ {int width; int height; int /*<<< orphan*/  refreshRate; int /*<<< orphan*/  blueBits; int /*<<< orphan*/  greenBits; int /*<<< orphan*/  redBits; } ;
struct TYPE_27__ {int cursorPosX; int cursorPosY; int /*<<< orphan*/  (* Clear ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  cursorMode; int /*<<< orphan*/  floating; int /*<<< orphan*/  autoIconify; int /*<<< orphan*/  decorated; void* resizable; int /*<<< orphan*/ * monitor; TYPE_1__ videoMode; struct TYPE_27__* next; } ;
typedef  TYPE_4__ _GLFWwindow ;
typedef  int /*<<< orphan*/  _GLFWmonitor ;
struct TYPE_28__ {int /*<<< orphan*/  blueBits; int /*<<< orphan*/  greenBits; int /*<<< orphan*/  redBits; } ;
typedef  TYPE_5__ _GLFWfbconfig ;
struct TYPE_29__ {TYPE_4__* share; } ;
typedef  TYPE_6__ _GLFWctxconfig ;
struct TYPE_25__ {int /*<<< orphan*/  refreshRate; TYPE_3__ window; TYPE_6__ context; TYPE_5__ framebuffer; } ;
struct TYPE_24__ {TYPE_2__ hints; TYPE_4__* windowListHead; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CURSOR_NORMAL ; 
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 void* GL_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 TYPE_22__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwIsValidContext (TYPE_6__*) ; 
 int /*<<< orphan*/  _glfwIsValidContextConfig (TYPE_6__*) ; 
 int /*<<< orphan*/  _glfwPlatformCreateWindow (TYPE_4__*,TYPE_3__*,TYPE_6__*,TYPE_5__*) ; 
 TYPE_4__* _glfwPlatformGetCurrentContext () ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (TYPE_4__*,int*,int*) ; 
 int /*<<< orphan*/  _glfwPlatformMakeContextCurrent (TYPE_4__*) ; 
 int /*<<< orphan*/  _glfwPlatformSetCursorPos (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  _glfwPlatformShowWindow (TYPE_4__*) ; 
 int /*<<< orphan*/  _glfwPlatformSwapBuffers (TYPE_4__*) ; 
 int /*<<< orphan*/  _glfwPlatformUnhideWindow (TYPE_4__*) ; 
 int /*<<< orphan*/  _glfwRefreshContextAttribs (TYPE_6__*) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  glfwDestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

GLFWwindow* glfwCreateWindow(int width, int height,
                                     const char* title,
                                     GLFWmonitor* monitor,
                                     GLFWwindow* share)
{
    _GLFWfbconfig fbconfig;
    _GLFWctxconfig ctxconfig;
    _GLFWwndconfig wndconfig;
    _GLFWwindow* window;
    _GLFWwindow* previous;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (width <= 0 || height <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid window size");
        return NULL;
    }

    fbconfig  = _glfw.hints.framebuffer;
    ctxconfig = _glfw.hints.context;
    wndconfig = _glfw.hints.window;

    wndconfig.width   = width;
    wndconfig.height  = height;
    wndconfig.title   = title;
    wndconfig.monitor = (_GLFWmonitor*) monitor;
    ctxconfig.share   = (_GLFWwindow*) share;

    if (wndconfig.monitor)
    {
        wndconfig.resizable = GL_TRUE;
        wndconfig.visible   = GL_TRUE;
        wndconfig.focused   = GL_TRUE;
    }

    // Check the OpenGL bits of the window config
    if (!_glfwIsValidContextConfig(&ctxconfig))
        return NULL;

    window = calloc(1, sizeof(_GLFWwindow));
    window->next = _glfw.windowListHead;
    _glfw.windowListHead = window;

    window->videoMode.width       = width;
    window->videoMode.height      = height;
    window->videoMode.redBits     = fbconfig.redBits;
    window->videoMode.greenBits   = fbconfig.greenBits;
    window->videoMode.blueBits    = fbconfig.blueBits;
    window->videoMode.refreshRate = _glfw.hints.refreshRate;

    window->monitor     = wndconfig.monitor;
    window->resizable   = wndconfig.resizable;
    window->decorated   = wndconfig.decorated;
    window->autoIconify = wndconfig.autoIconify;
    window->floating    = wndconfig.floating;
    window->cursorMode  = GLFW_CURSOR_NORMAL;

    // Save the currently current context so it can be restored later
    previous = _glfwPlatformGetCurrentContext();

    // Open the actual window and create its context
    if (!_glfwPlatformCreateWindow(window, &wndconfig, &ctxconfig, &fbconfig))
    {
        glfwDestroyWindow((GLFWwindow*) window);
        _glfwPlatformMakeContextCurrent(previous);
        return NULL;
    }

    _glfwPlatformMakeContextCurrent(window);

    // Retrieve the actual (as opposed to requested) context attributes
    if (!_glfwRefreshContextAttribs(&ctxconfig))
    {
        glfwDestroyWindow((GLFWwindow*) window);
        _glfwPlatformMakeContextCurrent(previous);
        return NULL;
    }

    // Verify the context against the requested parameters
    if (!_glfwIsValidContext(&ctxconfig))
    {
        glfwDestroyWindow((GLFWwindow*) window);
        _glfwPlatformMakeContextCurrent(previous);
        return NULL;
    }

    // Clearing the front buffer to black to avoid garbage pixels left over
    // from previous uses of our bit of VRAM
    window->Clear(GL_COLOR_BUFFER_BIT);
    _glfwPlatformSwapBuffers(window);

    // Restore the previously current context (or NULL)
    _glfwPlatformMakeContextCurrent(previous);

    if (wndconfig.monitor)
    {
        int width, height;
        _glfwPlatformGetWindowSize(window, &width, &height);

        window->cursorPosX = width / 2;
        window->cursorPosY = height / 2;

        _glfwPlatformSetCursorPos(window, window->cursorPosX, window->cursorPosY);
    }
    else
    {
        if (wndconfig.visible)
        {
            if (wndconfig.focused)
                _glfwPlatformShowWindow(window);
            else
                _glfwPlatformUnhideWindow(window);
        }
    }

    return (GLFWwindow*) window;
}