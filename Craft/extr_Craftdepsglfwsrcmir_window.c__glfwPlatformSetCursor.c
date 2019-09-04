#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  surface; } ;
struct TYPE_12__ {TYPE_2__ mir; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_11__ {scalar_t__ custom_cursor; scalar_t__ conf; } ;
struct TYPE_13__ {TYPE_3__ mir; } ;
typedef  TYPE_5__ _GLFWcursor ;
struct TYPE_9__ {scalar_t__ default_conf; } ;
struct TYPE_14__ {TYPE_1__ mir; } ;

/* Variables and functions */
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  mir_buffer_stream_swap_buffers_sync (scalar_t__) ; 
 int /*<<< orphan*/  mir_surface_configure_cursor (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mir_wait_for (int /*<<< orphan*/ ) ; 

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
    if (cursor && cursor->mir.conf)
    {
        mir_wait_for(mir_surface_configure_cursor(window->mir.surface, cursor->mir.conf));
        if (cursor->mir.custom_cursor)
        {
            /* FIXME Bug https://bugs.launchpad.net/mir/+bug/1477285
                     Requires a triple buffer swap to get the cursor buffer on top! (since mir is tripled buffered)
            */
            mir_buffer_stream_swap_buffers_sync(cursor->mir.custom_cursor);
            mir_buffer_stream_swap_buffers_sync(cursor->mir.custom_cursor);
            mir_buffer_stream_swap_buffers_sync(cursor->mir.custom_cursor);
        }
    }
    else
    {
        mir_wait_for(mir_surface_configure_cursor(window->mir.surface, _glfw.mir.default_conf));
    }
}