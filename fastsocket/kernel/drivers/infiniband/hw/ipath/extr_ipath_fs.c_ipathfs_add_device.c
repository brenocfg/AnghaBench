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
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int create_device_files (int /*<<< orphan*/ *,struct ipath_devdata*) ; 
 int /*<<< orphan*/ * ipath_super ; 

int ipathfs_add_device(struct ipath_devdata *dd)
{
	int ret;

	if (ipath_super == NULL) {
		ret = 0;
		goto bail;
	}

	ret = create_device_files(ipath_super, dd);

bail:
	return ret;
}