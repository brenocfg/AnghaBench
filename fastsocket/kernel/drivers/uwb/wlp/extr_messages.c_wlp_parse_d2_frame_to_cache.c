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
typedef  int /*<<< orphan*/  uuid_e ;
struct wlp_uuid {int dummy; } ;
struct wlp_neighbor_e {struct wlp_device_info* info; int /*<<< orphan*/  uuid; } ;
struct wlp_frame_assoc {int dummy; } ;
struct wlp_device_info {int /*<<< orphan*/  name; } ;
struct wlp {int /*<<< orphan*/  uuid; TYPE_2__* rc; } ;
struct sk_buff {size_t len; void* data; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum wlp_assc_error { ____Placeholder_wlp_assc_error } wlp_assc_error ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WLP_ASSOC_ERROR_NONE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct wlp_device_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct wlp_uuid*,int /*<<< orphan*/ *,int) ; 
 size_t wlp_get_dev_name (struct wlp*,void*,int /*<<< orphan*/ ,size_t) ; 
 size_t wlp_get_uuid_e (struct wlp*,void*,struct wlp_uuid*,size_t) ; 
 size_t wlp_get_uuid_r (struct wlp*,void*,int /*<<< orphan*/ *,size_t) ; 
 size_t wlp_get_variable_info (struct wlp*,void*,struct wlp_device_info*,size_t) ; 
 size_t wlp_get_wlp_assc_err (struct wlp*,void*,int*,size_t) ; 
 size_t wlp_get_wss_info_to_cache (struct wlp*,void*,struct wlp_neighbor_e*,size_t) ; 
 int /*<<< orphan*/  wlp_remove_neighbor_tmp_info (struct wlp_neighbor_e*) ; 

int wlp_parse_d2_frame_to_cache(struct wlp *wlp, struct sk_buff *skb,
				struct wlp_neighbor_e *neighbor)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	struct wlp_frame_assoc *d2 = (void *) skb->data;
	void *ptr = skb->data;
	size_t len = skb->len;
	size_t used;
	ssize_t result;
	struct wlp_uuid uuid_e;
	struct wlp_device_info *nb_info;
	enum wlp_assc_error assc_err;

	used = sizeof(*d2);
	result = wlp_get_uuid_e(wlp, ptr + used, &uuid_e, len - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain UUID-E attribute from D2 "
			"message.\n");
		goto error_parse;
	}
	if (memcmp(&uuid_e, &wlp->uuid, sizeof(uuid_e))) {
		dev_err(dev, "WLP: UUID-E in incoming D2 does not match "
			"local UUID sent in D1. \n");
		goto error_parse;
	}
	used += result;
	result = wlp_get_uuid_r(wlp, ptr + used, &neighbor->uuid, len - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain UUID-R attribute from D2 "
			"message.\n");
		goto error_parse;
	}
	used += result;
	result = wlp_get_wss_info_to_cache(wlp, ptr + used, neighbor,
					   len - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain WSS information "
			"from D2 message.\n");
		goto error_parse;
	}
	used += result;
	neighbor->info = kzalloc(sizeof(struct wlp_device_info), GFP_KERNEL);
	if (neighbor->info == NULL) {
		dev_err(dev, "WLP: cannot allocate memory to store device "
			"info.\n");
		result = -ENOMEM;
		goto error_parse;
	}
	nb_info = neighbor->info;
	result = wlp_get_dev_name(wlp, ptr + used, nb_info->name,
				  len - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain Device Name from D2 "
			"message.\n");
		goto error_parse;
	}
	used += result;
	result = wlp_get_variable_info(wlp, ptr + used, nb_info, len - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain Device Information from "
			"D2 message.\n");
		goto error_parse;
	}
	used += result;
	result = wlp_get_wlp_assc_err(wlp, ptr + used, &assc_err, len - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain WLP Association Error "
			"Information from D2 message.\n");
		goto error_parse;
	}
	if (assc_err != WLP_ASSOC_ERROR_NONE) {
		dev_err(dev, "WLP: neighbor device returned association "
			"error %d\n", assc_err);
		result = -EINVAL;
		goto error_parse;
	}
	result = 0;
error_parse:
	if (result < 0)
		wlp_remove_neighbor_tmp_info(neighbor);
	return result;
}