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
struct fc_rport {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int fc_rport_set_dev_loss_tmo (struct fc_rport*,unsigned long) ; 
 int fc_str_to_dev_loss (char const*,unsigned long*) ; 
 struct fc_rport* transport_class_to_rport (struct device*) ; 

__attribute__((used)) static ssize_t
store_fc_rport_dev_loss_tmo(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct fc_rport *rport = transport_class_to_rport(dev);
	unsigned long val;
	int rc;

	rc = fc_str_to_dev_loss(buf, &val);
	if (rc)
		return rc;

	rc = fc_rport_set_dev_loss_tmo(rport, val);
	if (rc)
		return rc;
	return count;
}