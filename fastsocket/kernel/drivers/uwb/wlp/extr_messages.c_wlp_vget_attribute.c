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
typedef  size_t u16 ;
struct wlp_attr_hdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct wlp {TYPE_2__* rc; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static ssize_t wlp_vget_attribute(struct wlp *wlp, u16 type_code,
	struct wlp_attr_hdr *attr_hdr, void *value, ssize_t max_value_len,
	ssize_t buflen)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	size_t len;
	if (buflen < 0)
		return -EINVAL;
	if (buflen < sizeof(*attr_hdr)) {
		dev_err(dev, "WLP: Not enough space in buffer to parse"
			" header.\n");
		return -EIO;
	}
	if (le16_to_cpu(attr_hdr->type) != type_code) {
		dev_err(dev, "WLP: Unexpected attribute type. Got %u, "
			"expected %u.\n", le16_to_cpu(attr_hdr->type),
			type_code);
		return -EINVAL;
	}
	len = le16_to_cpu(attr_hdr->length);
	if (len > max_value_len) {
		dev_err(dev, "WLP: Attribute larger than maximum "
			"allowed. Received %zu, max is %d.\n", len,
			(int)max_value_len);
		return -EFBIG;
	}
	if (buflen < sizeof(*attr_hdr) + len) {
		dev_err(dev, "WLP: Not enough space in buffer to parse "
			"variable data.\n");
		return -EIO;
	}
	memcpy(value, (void *)attr_hdr + sizeof(*attr_hdr), len);
	return sizeof(*attr_hdr) + len;
}