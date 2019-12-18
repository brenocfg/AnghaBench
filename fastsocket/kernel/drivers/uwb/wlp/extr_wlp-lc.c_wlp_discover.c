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
struct wlp {int /*<<< orphan*/  nbmutex; TYPE_2__* rc; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wlp_neighbors_release (struct wlp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uwb_dev_for_each (TYPE_2__*,int /*<<< orphan*/ ,struct wlp*) ; 
 int /*<<< orphan*/  wlp_add_neighbor_helper ; 
 int wlp_discover_all_neighbors (struct wlp*) ; 

ssize_t wlp_discover(struct wlp *wlp)
{
	int result = 0;
	struct device *dev = &wlp->rc->uwb_dev.dev;

	mutex_lock(&wlp->nbmutex);
	/* Clear current neighborhood cache. */
	__wlp_neighbors_release(wlp);
	/* Determine which devices in neighborhood. Repopulate cache. */
	result = uwb_dev_for_each(wlp->rc, wlp_add_neighbor_helper, wlp);
	if (result < 0) {
		/* May have partial neighbor information, release all. */
		__wlp_neighbors_release(wlp);
		goto error_dev_for_each;
	}
	/* Discover the properties of devices in neighborhood. */
	result = wlp_discover_all_neighbors(wlp);
	/* In case of failure we still print our partial results. */
	if (result < 0) {
		dev_err(dev, "Unable to fully discover neighborhood. \n");
		result = 0;
	}
error_dev_for_each:
	mutex_unlock(&wlp->nbmutex);
	return result;
}