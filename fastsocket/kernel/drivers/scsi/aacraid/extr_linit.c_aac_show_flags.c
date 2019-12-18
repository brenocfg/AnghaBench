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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int SupportedOptions2; } ;
struct aac_dev {scalar_t__ msi; TYPE_1__ supplement_adapter_info; scalar_t__ jbod; scalar_t__ raw_io_64; scalar_t__ raw_io_interface; } ;
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int AAC_OPTION_POWER_MANAGEMENT ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_2__* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ) ; 
 scalar_t__ nblank (int /*<<< orphan*/ ) ; 
 int snprintf (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  x ; 

__attribute__((used)) static ssize_t aac_show_flags(struct device *cdev,
			      struct device_attribute *attr, char *buf)
{
	int len = 0;
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(cdev)->hostdata;

	if (nblank(dprintk(x)))
		len = snprintf(buf, PAGE_SIZE, "dprintk\n");
#ifdef AAC_DETAILED_STATUS_INFO
	len += snprintf(buf + len, PAGE_SIZE - len,
			"AAC_DETAILED_STATUS_INFO\n");
#endif
	if (dev->raw_io_interface && dev->raw_io_64)
		len += snprintf(buf + len, PAGE_SIZE - len,
				"SAI_READ_CAPACITY_16\n");
	if (dev->jbod)
		len += snprintf(buf + len, PAGE_SIZE - len, "SUPPORTED_JBOD\n");
	if (dev->supplement_adapter_info.SupportedOptions2 &
		AAC_OPTION_POWER_MANAGEMENT)
		len += snprintf(buf + len, PAGE_SIZE - len,
				"SUPPORTED_POWER_MANAGEMENT\n");
	if (dev->msi)
		len += snprintf(buf + len, PAGE_SIZE - len, "PCI_HAS_MSI\n");
	return len;
}