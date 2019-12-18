#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wl_display {int dummy; } ;
struct pollfd {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_5__ {struct wl_display* display; } ;
struct TYPE_7__ {TYPE_2__* windowListHead; TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  POLLIN ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputWindowCloseRequest (TYPE_2__*) ; 
 scalar_t__ errno ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  wl_display_cancel_read (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_dispatch_pending (struct wl_display*) ; 
 scalar_t__ wl_display_flush (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_get_fd (struct wl_display*) ; 
 scalar_t__ wl_display_prepare_read (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_read_events (struct wl_display*) ; 

__attribute__((used)) static void
handleEvents(int timeout)
{
    struct wl_display* display = _glfw.wl.display;
    struct pollfd fds[] = {
        { wl_display_get_fd(display), POLLIN },
    };

    while (wl_display_prepare_read(display) != 0)
        wl_display_dispatch_pending(display);

    // If an error different from EAGAIN happens, we have likely been
    // disconnected from the Wayland session, try to handle that the best we
    // can.
    if (wl_display_flush(display) < 0 && errno != EAGAIN)
    {
        _GLFWwindow* window = _glfw.windowListHead;
        while (window)
        {
            _glfwInputWindowCloseRequest(window);
            window = window->next;
        }
        wl_display_cancel_read(display);
        return;
    }

    if (poll(fds, 1, timeout) > 0)
    {
        wl_display_read_events(display);
        wl_display_dispatch_pending(display);
    }
    else
    {
        wl_display_cancel_read(display);
    }
}