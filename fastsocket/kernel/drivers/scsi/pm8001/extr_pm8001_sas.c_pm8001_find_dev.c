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
typedef  size_t u32 ;
struct pm8001_hba_info {struct pm8001_device* devices; } ;
struct pm8001_device {size_t device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 size_t PM8001_MAX_DEVICES ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 

struct pm8001_device *pm8001_find_dev(struct pm8001_hba_info *pm8001_ha,
					u32 device_id)
{
	u32 dev;
	for (dev = 0; dev < PM8001_MAX_DEVICES; dev++) {
		if (pm8001_ha->devices[dev].device_id == device_id)
			return &pm8001_ha->devices[dev];
	}
	if (dev == PM8001_MAX_DEVICES) {
		PM8001_FAIL_DBG(pm8001_ha, pm8001_printk("NO MATCHING "
				"DEVICE FOUND !!!\n"));
	}
	return NULL;
}