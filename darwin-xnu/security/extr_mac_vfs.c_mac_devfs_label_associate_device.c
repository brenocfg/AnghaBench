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
struct devnode {int /*<<< orphan*/  dn_label; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct devnode*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  devfs_label_associate_device ; 
 int /*<<< orphan*/  mac_device_enforce ; 

void
mac_devfs_label_associate_device(dev_t dev, struct devnode *de,
    const char *fullpath)
{
#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_device_enforce)
		return;
#endif

	MAC_PERFORM(devfs_label_associate_device, dev, de, de->dn_label,
	    fullpath);
}