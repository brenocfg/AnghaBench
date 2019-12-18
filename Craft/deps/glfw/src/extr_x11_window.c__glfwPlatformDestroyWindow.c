#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ handle; scalar_t__ colormap; int /*<<< orphan*/ * ic; } ;
struct TYPE_11__ {TYPE_1__ x11; scalar_t__ monitor; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  scalar_t__ Window ;
struct TYPE_10__ {int /*<<< orphan*/  display; int /*<<< orphan*/  context; int /*<<< orphan*/  CLIPBOARD; } ;
struct TYPE_12__ {TYPE_2__ x11; } ;
typedef  scalar_t__ Colormap ;

/* Variables and functions */
 int /*<<< orphan*/  XDeleteContext (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyIC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeColormap (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUnmapWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwDestroyContext (TYPE_3__*) ; 
 int /*<<< orphan*/  leaveFullscreenMode (TYPE_3__*) ; 
 int /*<<< orphan*/  pushSelectionToManager (TYPE_3__*) ; 

void _glfwPlatformDestroyWindow(_GLFWwindow* window)
{
    if (window->monitor)
        leaveFullscreenMode(window);

    if (window->x11.ic)
    {
        XDestroyIC(window->x11.ic);
        window->x11.ic = NULL;
    }

    _glfwDestroyContext(window);

    if (window->x11.handle)
    {
        if (XGetSelectionOwner(_glfw.x11.display, _glfw.x11.CLIPBOARD) ==
            window->x11.handle)
        {
            pushSelectionToManager(window);
        }

        XDeleteContext(_glfw.x11.display, window->x11.handle, _glfw.x11.context);
        XUnmapWindow(_glfw.x11.display, window->x11.handle);
        XDestroyWindow(_glfw.x11.display, window->x11.handle);
        window->x11.handle = (Window) 0;
    }

    if (window->x11.colormap)
    {
        XFreeColormap(_glfw.x11.display, window->x11.colormap);
        window->x11.colormap = (Colormap) 0;
    }

    XFlush(_glfw.x11.display);
}