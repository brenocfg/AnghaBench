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
struct hyp_sysfs_attr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HYPERVISOR_xen_version (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XENVER_capabilities ; 
 int /*<<< orphan*/  XEN_CAPABILITIES_INFO_LEN ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t capabilities_show(struct hyp_sysfs_attr *attr, char *buffer)
{
	int ret = -ENOMEM;
	char *caps;

	caps = kmalloc(XEN_CAPABILITIES_INFO_LEN, GFP_KERNEL);
	if (caps) {
		ret = HYPERVISOR_xen_version(XENVER_capabilities, caps);
		if (!ret)
			ret = sprintf(buffer, "%s\n", caps);
		kfree(caps);
	}

	return ret;
}