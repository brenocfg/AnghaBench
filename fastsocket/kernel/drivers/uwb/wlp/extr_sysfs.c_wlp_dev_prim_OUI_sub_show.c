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
struct wlp {int /*<<< orphan*/  mutex; TYPE_2__* dev_info; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  OUIsubdiv; } ;
struct TYPE_4__ {TYPE_1__ prim_dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __wlp_setup_device_info (struct wlp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

ssize_t wlp_dev_prim_OUI_sub_show(struct wlp *wlp, char *buf)
{
	ssize_t result = 0;
	mutex_lock(&wlp->mutex);
	if (wlp->dev_info == NULL) {
		result = __wlp_setup_device_info(wlp);
		if (result < 0)
			goto out;
	}
	result = scnprintf(buf, PAGE_SIZE, "%u\n",
			   wlp->dev_info->prim_dev_type.OUIsubdiv);
out:
	mutex_unlock(&wlp->mutex);
	return result;
}