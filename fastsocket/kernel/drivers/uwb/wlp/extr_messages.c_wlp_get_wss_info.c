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
struct wlp_wss_tmp_info {int dummy; } ;
struct wlp_uuid {int dummy; } ;
struct wlp_attr_wss_info {int dummy; } ;
struct wlp_attr_hdr {int dummy; } ;
struct wlp {TYPE_2__* rc; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 size_t wlp_check_wss_info_attr_hdr (struct wlp*,struct wlp_attr_hdr*,size_t) ; 
 size_t wlp_get_wss_info_attrs (struct wlp*,void*,struct wlp_wss_tmp_info*,size_t) ; 
 size_t wlp_get_wssid (struct wlp*,void*,struct wlp_uuid*,size_t) ; 

__attribute__((used)) static ssize_t wlp_get_wss_info(struct wlp *wlp, struct wlp_attr_wss_info *attr,
				size_t buflen, struct wlp_uuid *wssid,
				struct wlp_wss_tmp_info *wss_info)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	ssize_t result;
	size_t len;
	size_t used = 0;
	void *ptr;

	result = wlp_check_wss_info_attr_hdr(wlp, (struct wlp_attr_hdr *)attr,
					     buflen);
	if (result < 0)
		goto out;
	len = result;
	used = sizeof(*attr);
	ptr = attr;

	result = wlp_get_wssid(wlp, ptr + used, wssid, buflen - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain WSSID from WSS info.\n");
		goto out;
	}
	used += result;
	result = wlp_get_wss_info_attrs(wlp, ptr + used, wss_info,
					buflen - used);
	if (result < 0) {
		dev_err(dev, "WLP: unable to obtain WSS information "
			"from WSS information attributes. \n");
		goto out;
	}
	used += result;
	if (len + sizeof(*attr) != used) {
		dev_err(dev, "WLP: Amount of data parsed does not "
			"match length field. Parsed %zu, length "
			"field %zu. \n", used, len);
		result = -EINVAL;
		goto out;
	}
	result = used;
out:
	return result;
}