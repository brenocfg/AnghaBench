#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct wl_surface {int dummy; } ;
struct wl_cursor_image {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; } ;
struct wl_buffer {int dummy; } ;
struct TYPE_10__ {TYPE_6__* currentCursor; } ;
struct TYPE_14__ {scalar_t__ cursorMode; TYPE_1__ wl; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct wl_buffer* buffer; int /*<<< orphan*/  yhot; int /*<<< orphan*/  xhot; } ;
struct TYPE_15__ {TYPE_3__ wl; } ;
typedef  TYPE_6__ _GLFWcursor ;
struct TYPE_13__ {int /*<<< orphan*/  pointerSerial; int /*<<< orphan*/  pointer; TYPE_2__* defaultCursor; TYPE_5__* pointerFocus; struct wl_surface* cursorSurface; } ;
struct TYPE_16__ {TYPE_4__ wl; } ;
struct TYPE_11__ {struct wl_cursor_image** images; } ;

/* Variables and functions */
 scalar_t__ GLFW_CURSOR_NORMAL ; 
 TYPE_9__ _glfw ; 
 struct wl_buffer* wl_cursor_image_get_buffer (struct wl_cursor_image*) ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_attach (struct wl_surface*,struct wl_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (struct wl_surface*) ; 
 int /*<<< orphan*/  wl_surface_damage (struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
    struct wl_buffer* buffer;
    struct wl_cursor_image* image;
    struct wl_surface* surface = _glfw.wl.cursorSurface;

    if (!_glfw.wl.pointer)
        return;

    window->wl.currentCursor = cursor;

    // If we're not in the correct window just save the cursor
    // the next time the pointer enters the window the cursor will change
    if (window != _glfw.wl.pointerFocus)
        return;

    if (window->cursorMode == GLFW_CURSOR_NORMAL)
    {
        if (cursor == NULL)
        {
            image = _glfw.wl.defaultCursor->images[0];
            buffer = wl_cursor_image_get_buffer(image);
            if (!buffer)
                return;
            wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.pointerSerial,
                                  surface,
                                  image->hotspot_x,
                                  image->hotspot_y);
            wl_surface_attach(surface, buffer, 0, 0);
            wl_surface_damage(surface, 0, 0,
                              image->width, image->height);
            wl_surface_commit(surface);
        }
        else
        {
            wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.pointerSerial,
                                  surface,
                                  cursor->wl.xhot,
                                  cursor->wl.yhot);
            wl_surface_attach(surface, cursor->wl.buffer, 0, 0);
            wl_surface_damage(surface, 0, 0,
                              cursor->wl.width, cursor->wl.height);
            wl_surface_commit(surface);
        }
    }
    else /* Cursor is hidden set cursor surface to NULL */
    {
        wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.pointerSerial, NULL, 0, 0);
    }
}