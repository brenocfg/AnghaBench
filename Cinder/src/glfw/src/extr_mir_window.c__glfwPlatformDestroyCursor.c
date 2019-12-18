#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ custom_cursor; scalar_t__ conf; } ;
struct TYPE_5__ {TYPE_1__ mir; } ;
typedef  TYPE_2__ _GLFWcursor ;

/* Variables and functions */
 int /*<<< orphan*/  mir_buffer_stream_release_sync (scalar_t__) ; 
 int /*<<< orphan*/  mir_cursor_configuration_destroy (scalar_t__) ; 

void _glfwPlatformDestroyCursor(_GLFWcursor* cursor)
{
    if (cursor->mir.conf)
        mir_cursor_configuration_destroy(cursor->mir.conf);
    if (cursor->mir.custom_cursor)
        mir_buffer_stream_release_sync(cursor->mir.custom_cursor);
}