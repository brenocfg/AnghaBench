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
typedef  int /*<<< orphan*/  u16 ;
struct wlp_attr_hdr {int dummy; } ;
struct wlp {TYPE_2__* rc; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 scalar_t__ wlp_check_attr_hdr (struct wlp*,struct wlp_attr_hdr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ssize_t wlp_get_attribute(struct wlp *wlp, u16 type_code,
	struct wlp_attr_hdr *attr_hdr, void *value, ssize_t value_len,
	ssize_t buflen)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	ssize_t attr_len = sizeof(*attr_hdr) + value_len;
	if (buflen < 0)
		return -EINVAL;
	if (buflen < attr_len) {
		dev_err(dev, "WLP: Not enough space in buffer to parse"
			" attribute field. Need %d, received %zu\n",
			(int)attr_len, buflen);
		return -EIO;
	}
	if (wlp_check_attr_hdr(wlp, attr_hdr, type_code, value_len) < 0) {
		dev_err(dev, "WLP: Header verification failed. \n");
		return -EINVAL;
	}
	memcpy(value, (void *)attr_hdr + sizeof(*attr_hdr), value_len);
	return attr_len;
}