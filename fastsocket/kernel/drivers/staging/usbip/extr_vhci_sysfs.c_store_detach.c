#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ VHCI_NPORTS ; 
 int /*<<< orphan*/  sscanf (char const*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_sysfs (char*) ; 
 int /*<<< orphan*/  usbip_uerr (char*,scalar_t__) ; 
 int vhci_port_disconnect (scalar_t__) ; 

__attribute__((used)) static ssize_t store_detach(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	int err;
	__u32 rhport = 0;

	sscanf(buf, "%u", &rhport);

	/* check rhport */
	if (rhport >= VHCI_NPORTS) {
		usbip_uerr("invalid port %u\n", rhport);
		return -EINVAL;
	}

	err = vhci_port_disconnect(rhport);
	if (err < 0)
		return -EINVAL;

	usbip_dbg_vhci_sysfs("Leave\n");
	return count;
}