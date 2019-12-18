#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct TYPE_4__ {int devno; } ;
struct TYPE_5__ {TYPE_1__ fcp; } ;
struct ipl_parameter_block {TYPE_2__ ipl_info; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int type; } ;

/* Variables and functions */
 struct ipl_parameter_block* IPL_PARMBLOCK_START ; 
#define  IPL_TYPE_CCW 130 
#define  IPL_TYPE_FCP 129 
#define  IPL_TYPE_FCP_DUMP 128 
 int ipl_devno ; 
 TYPE_3__ ipl_info ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t sys_ipl_device_show(struct kobject *kobj,
				   struct kobj_attribute *attr, char *page)
{
	struct ipl_parameter_block *ipl = IPL_PARMBLOCK_START;

	switch (ipl_info.type) {
	case IPL_TYPE_CCW:
		return sprintf(page, "0.0.%04x\n", ipl_devno);
	case IPL_TYPE_FCP:
	case IPL_TYPE_FCP_DUMP:
		return sprintf(page, "0.0.%04x\n", ipl->ipl_info.fcp.devno);
	default:
		return 0;
	}
}