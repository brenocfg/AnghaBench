#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event ;
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {TYPE_1__ x11; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_11__ {int format; int /*<<< orphan*/  message_type; int /*<<< orphan*/  window; } ;
struct TYPE_13__ {TYPE_3__ xclient; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ XEvent ;
struct TYPE_10__ {int /*<<< orphan*/  display; int /*<<< orphan*/  NULL_; } ;
struct TYPE_14__ {TYPE_2__ x11; TYPE_4__* windowListHead; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void _glfwPlatformPostEmptyEvent(void)
{
    XEvent event;
    _GLFWwindow* window = _glfw.windowListHead;

    memset(&event, 0, sizeof(event));
    event.type = ClientMessage;
    event.xclient.window = window->x11.handle;
    event.xclient.format = 32; // Data is 32-bit longs
    event.xclient.message_type = _glfw.x11.NULL_;

    XSendEvent(_glfw.x11.display, window->x11.handle, False, 0, &event);
    XFlush(_glfw.x11.display);
}