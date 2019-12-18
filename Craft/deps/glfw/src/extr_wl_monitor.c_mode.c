#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_output {int dummy; } ;
struct TYPE_9__ {int modesCount; int modesSize; TYPE_4__* modes; } ;
struct _GLFWmonitor {TYPE_3__ wl; } ;
typedef  void* int32_t ;
struct TYPE_8__ {void* refreshRate; void* height; void* width; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; TYPE_2__ base; TYPE_1__ member_0; } ;
typedef  TYPE_4__ _GLFWvidmodeWayland ;

/* Variables and functions */
 TYPE_4__* realloc (TYPE_4__*,int) ; 

__attribute__((used)) static void mode(void* data,
                 struct wl_output* output,
                 uint32_t flags,
                 int32_t width,
                 int32_t height,
                 int32_t refresh)
{
    struct _GLFWmonitor *monitor = data;
    _GLFWvidmodeWayland mode = { { 0 }, };

    mode.base.width = width;
    mode.base.height = height;
    mode.base.refreshRate = refresh;
    mode.flags = flags;

    if (monitor->wl.modesCount + 1 >= monitor->wl.modesSize)
    {
        int size = monitor->wl.modesSize * 2;
        _GLFWvidmodeWayland* modes =
            realloc(monitor->wl.modes,
                    size * sizeof(_GLFWvidmodeWayland));
        monitor->wl.modes = modes;
        monitor->wl.modesSize = size;
    }

    monitor->wl.modes[monitor->wl.modesCount++] = mode;
}