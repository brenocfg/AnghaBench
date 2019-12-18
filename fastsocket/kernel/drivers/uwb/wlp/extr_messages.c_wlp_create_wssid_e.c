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
struct wlp_wssid_e {int /*<<< orphan*/  node; int /*<<< orphan*/ * info; } ;
struct wlp_wss_tmp_info {int dummy; } ;
struct wlp_neighbor_e {int /*<<< orphan*/  wssid; } ;
struct wlp {TYPE_2__* rc; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct wlp_wssid_e*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct wlp_wssid_e *wlp_create_wssid_e(struct wlp *wlp,
					      struct wlp_neighbor_e *neighbor)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	struct wlp_wssid_e *wssid_e;

	wssid_e = kzalloc(sizeof(*wssid_e), GFP_KERNEL);
	if (wssid_e == NULL) {
		dev_err(dev, "WLP: unable to allocate memory "
			"for WSS information.\n");
		goto error_alloc;
	}
	wssid_e->info = kzalloc(sizeof(struct wlp_wss_tmp_info), GFP_KERNEL);
	if (wssid_e->info == NULL) {
		dev_err(dev, "WLP: unable to allocate memory "
			"for temporary WSS information.\n");
		kfree(wssid_e);
		wssid_e = NULL;
		goto error_alloc;
	}
	list_add(&wssid_e->node, &neighbor->wssid);
error_alloc:
	return wssid_e;
}