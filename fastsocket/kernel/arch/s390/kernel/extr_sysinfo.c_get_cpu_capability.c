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
struct sysinfo_1_2_2 {unsigned int capability; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int stsi (struct sysinfo_1_2_2*,int,int,int) ; 

int get_cpu_capability(unsigned int *capability)
{
	struct sysinfo_1_2_2 *info;
	int rc;

	info = (void *) get_zeroed_page(GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	rc = stsi(info, 1, 2, 2);
	if (rc == -ENOSYS)
		goto out;
	rc = 0;
	*capability = info->capability;
out:
	free_page((unsigned long) info);
	return rc;
}