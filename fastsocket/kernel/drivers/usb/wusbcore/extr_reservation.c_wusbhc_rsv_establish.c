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
struct wusbhc {struct uwb_rsv* rsv; scalar_t__ cluster_id; struct uwb_rc* uwb_rc; } ;
struct uwb_dev_addr {scalar_t__* data; } ;
struct TYPE_2__ {struct uwb_dev_addr devaddr; int /*<<< orphan*/  type; } ;
struct uwb_rsv {int max_mas; int min_mas; int max_interval; int is_multicast; int /*<<< orphan*/  type; TYPE_1__ target; } ;
struct uwb_rc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  UWB_DRP_TYPE_PRIVATE ; 
 int /*<<< orphan*/  UWB_RSV_TARGET_DEVADDR ; 
 struct uwb_rsv* uwb_rsv_create (struct uwb_rc*,int /*<<< orphan*/ ,struct wusbhc*) ; 
 int /*<<< orphan*/  uwb_rsv_destroy (struct uwb_rsv*) ; 
 int uwb_rsv_establish (struct uwb_rsv*) ; 
 int /*<<< orphan*/  wusbhc_rsv_complete_cb ; 

int wusbhc_rsv_establish(struct wusbhc *wusbhc)
{
	struct uwb_rc *rc = wusbhc->uwb_rc;
	struct uwb_rsv *rsv;
	struct uwb_dev_addr bcid;
	int ret;

	rsv = uwb_rsv_create(rc, wusbhc_rsv_complete_cb, wusbhc);
	if (rsv == NULL)
		return -ENOMEM;

	bcid.data[0] = wusbhc->cluster_id;
	bcid.data[1] = 0;

	rsv->target.type = UWB_RSV_TARGET_DEVADDR;
	rsv->target.devaddr = bcid;
	rsv->type = UWB_DRP_TYPE_PRIVATE;
	rsv->max_mas = 256; /* try to get as much as possible */
	rsv->min_mas = 15;  /* one MAS per zone */
	rsv->max_interval = 1; /* max latency is one zone */
	rsv->is_multicast = true;

	ret = uwb_rsv_establish(rsv);
	if (ret == 0)
		wusbhc->rsv = rsv;
	else
		uwb_rsv_destroy(rsv);
	return ret;
}