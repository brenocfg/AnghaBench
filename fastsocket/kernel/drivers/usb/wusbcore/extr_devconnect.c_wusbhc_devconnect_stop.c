#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wusbhc {int ports_max; TYPE_1__* wuie_host_info; int /*<<< orphan*/  keep_alive_timer; int /*<<< orphan*/  mutex; TYPE_2__* port; } ;
struct TYPE_4__ {scalar_t__ wusb_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wusbhc_dev_disconnect (struct wusbhc*,TYPE_2__*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusbhc_mmcie_rm (struct wusbhc*,int /*<<< orphan*/ *) ; 

void wusbhc_devconnect_stop(struct wusbhc *wusbhc)
{
	int i;

	mutex_lock(&wusbhc->mutex);
	for (i = 0; i < wusbhc->ports_max; i++) {
		if (wusbhc->port[i].wusb_dev)
			__wusbhc_dev_disconnect(wusbhc, &wusbhc->port[i]);
	}
	mutex_unlock(&wusbhc->mutex);

	cancel_delayed_work_sync(&wusbhc->keep_alive_timer);
	wusbhc_mmcie_rm(wusbhc, &wusbhc->wuie_host_info->hdr);
	kfree(wusbhc->wuie_host_info);
	wusbhc->wuie_host_info = NULL;
}