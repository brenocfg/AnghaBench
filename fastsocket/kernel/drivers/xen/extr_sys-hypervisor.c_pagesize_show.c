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
 int HYPERVISOR_xen_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XENVER_pagesize ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pagesize_show(struct hyp_sysfs_attr *attr, char *buffer)
{
	int ret;

	ret = HYPERVISOR_xen_version(XENVER_pagesize, NULL);
	if (ret > 0)
		ret = sprintf(buffer, "%x\n", ret);

	return ret;
}