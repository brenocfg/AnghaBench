#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fcoe_ctlr_device {int enabled; TYPE_1__* f; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int (* set_fcoe_ctlr_enabled ) (struct fcoe_ctlr_device*) ;} ;

/* Variables and functions */
 size_t ENOTSUPP ; 
#define  FCOE_CTLR_DISABLED 130 
#define  FCOE_CTLR_ENABLED 129 
#define  FCOE_CTLR_UNUSED 128 
 struct fcoe_ctlr_device* dev_to_ctlr (struct device*) ; 
 int stub1 (struct fcoe_ctlr_device*) ; 

__attribute__((used)) static ssize_t store_ctlr_enabled(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct fcoe_ctlr_device *ctlr = dev_to_ctlr(dev);
	int rc;

	switch (ctlr->enabled) {
	case FCOE_CTLR_ENABLED:
		if (*buf == '1')
			return count;
		ctlr->enabled = FCOE_CTLR_DISABLED;
		break;
	case FCOE_CTLR_DISABLED:
		if (*buf == '0')
			return count;
		ctlr->enabled = FCOE_CTLR_ENABLED;
		break;
	case FCOE_CTLR_UNUSED:
		return -ENOTSUPP;
	};

	rc = ctlr->f->set_fcoe_ctlr_enabled(ctlr);
	if (rc)
		return rc;

	return count;
}