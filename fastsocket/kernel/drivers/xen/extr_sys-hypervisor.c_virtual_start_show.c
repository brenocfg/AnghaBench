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
struct xen_platform_parameters {int /*<<< orphan*/  virt_start; } ;
struct hyp_sysfs_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_xen_version (int /*<<< orphan*/ ,struct xen_platform_parameters*) ; 
 int /*<<< orphan*/  XENVER_platform_parameters ; 
 int /*<<< orphan*/  kfree (struct xen_platform_parameters*) ; 
 struct xen_platform_parameters* kmalloc (int,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t virtual_start_show(struct hyp_sysfs_attr *attr, char *buffer)
{
	int ret = -ENOMEM;
	struct xen_platform_parameters *parms;

	parms = kmalloc(sizeof(struct xen_platform_parameters), GFP_KERNEL);
	if (parms) {
		ret = HYPERVISOR_xen_version(XENVER_platform_parameters,
					     parms);
		if (!ret)
			ret = sprintf(buffer, "%lx\n", parms->virt_start);
		kfree(parms);
	}

	return ret;
}