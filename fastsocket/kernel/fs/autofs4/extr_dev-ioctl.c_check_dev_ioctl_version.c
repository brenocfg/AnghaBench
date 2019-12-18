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
struct autofs_dev_ioctl {scalar_t__ ver_major; scalar_t__ ver_minor; } ;

/* Variables and functions */
 scalar_t__ AUTOFS_DEV_IOCTL_VERSION_MAJOR ; 
 scalar_t__ AUTOFS_DEV_IOCTL_VERSION_MINOR ; 
 int /*<<< orphan*/  AUTOFS_WARN (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int EINVAL ; 

__attribute__((used)) static int check_dev_ioctl_version(int cmd, struct autofs_dev_ioctl *param)
{
	int err = 0;

	if ((AUTOFS_DEV_IOCTL_VERSION_MAJOR != param->ver_major) ||
	    (AUTOFS_DEV_IOCTL_VERSION_MINOR < param->ver_minor)) {
		AUTOFS_WARN("ioctl control interface version mismatch: "
		     "kernel(%u.%u), user(%u.%u), cmd(%d)",
		     AUTOFS_DEV_IOCTL_VERSION_MAJOR,
		     AUTOFS_DEV_IOCTL_VERSION_MINOR,
		     param->ver_major, param->ver_minor, cmd);
		err = -EINVAL;
	}

	/* Fill in the kernel version. */
	param->ver_major = AUTOFS_DEV_IOCTL_VERSION_MAJOR;
	param->ver_minor = AUTOFS_DEV_IOCTL_VERSION_MINOR;

	return err;
}