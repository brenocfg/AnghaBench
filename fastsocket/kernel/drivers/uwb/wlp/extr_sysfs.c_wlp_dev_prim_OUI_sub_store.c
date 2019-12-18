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
typedef  unsigned int u8 ;
struct wlp {int /*<<< orphan*/  mutex; TYPE_2__* dev_info; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {unsigned int OUIsubdiv; } ;
struct TYPE_4__ {TYPE_1__ prim_dev_type; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t __wlp_alloc_device_info (struct wlp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t sscanf (char const*,char*,unsigned int*) ; 

ssize_t wlp_dev_prim_OUI_sub_store(struct wlp *wlp, const char *buf,
				   size_t size)
{
	ssize_t result;
	unsigned sub;
	u8 max_sub = ~0;
	mutex_lock(&wlp->mutex);
	if (wlp->dev_info == NULL) {
		result = __wlp_alloc_device_info(wlp);
		if (result < 0)
			goto out;
	}
	result = sscanf(buf, "%u", &sub);
	if (sub <= max_sub)
		wlp->dev_info->prim_dev_type.OUIsubdiv = sub;
	else
		result = -EINVAL;
out:
	mutex_unlock(&wlp->mutex);
	return result < 0 ? result : size;
}