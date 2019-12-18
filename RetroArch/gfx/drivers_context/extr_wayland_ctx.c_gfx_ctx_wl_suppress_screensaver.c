#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zwp_idle_inhibit_manager_v1 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * idle_inhibitor; int /*<<< orphan*/  surface; struct zwp_idle_inhibit_manager_v1* idle_inhibit_manager; } ;
typedef  TYPE_1__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/ * zwp_idle_inhibit_manager_v1_create_inhibitor (struct zwp_idle_inhibit_manager_v1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_idle_inhibitor_v1_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gfx_ctx_wl_suppress_screensaver(void *data, bool state)
{
	(void)data;

	gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

    if (!wl->idle_inhibit_manager)
        return false;
    if (state == (!!wl->idle_inhibitor))
        return true;
    if (state)
    {
        RARCH_LOG("[Wayland]: Enabling idle inhibitor\n");
        struct zwp_idle_inhibit_manager_v1 *mgr = wl->idle_inhibit_manager;
        wl->idle_inhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(mgr, wl->surface);
    }
    else
    {
        RARCH_LOG("[Wayland]: Disabling the idle inhibitor\n");
        zwp_idle_inhibitor_v1_destroy(wl->idle_inhibitor);
        wl->idle_inhibitor = NULL;
    }
    return true;
}