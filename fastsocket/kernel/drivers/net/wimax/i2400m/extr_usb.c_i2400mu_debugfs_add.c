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
struct TYPE_5__ {struct dentry* debugfs_dentry; } ;
struct TYPE_6__ {TYPE_2__ wimax_dev; } ;
struct i2400mu {struct dentry* debugfs_dentry; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  rx_size_auto_shrink; TYPE_3__ i2400m; TYPE_1__* usb_iface; } ;
struct device {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __debugfs_register (char*,int /*<<< orphan*/ ,struct dentry*) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 struct dentry* debugfs_create_size_t (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  fw ; 
 int /*<<< orphan*/  notif ; 
 int /*<<< orphan*/  rx ; 
 int /*<<< orphan*/  tx ; 
 int /*<<< orphan*/  usb ; 

__attribute__((used)) static
int i2400mu_debugfs_add(struct i2400mu *i2400mu)
{
	int result;
	struct device *dev = &i2400mu->usb_iface->dev;
	struct dentry *dentry = i2400mu->i2400m.wimax_dev.debugfs_dentry;
	struct dentry *fd;

	dentry = debugfs_create_dir("i2400m-usb", dentry);
	result = PTR_ERR(dentry);
	if (IS_ERR(dentry)) {
		if (result == -ENODEV)
			result = 0;	/* No debugfs support */
		goto error;
	}
	i2400mu->debugfs_dentry = dentry;
	__debugfs_register("dl_", usb, dentry);
	__debugfs_register("dl_", fw, dentry);
	__debugfs_register("dl_", notif, dentry);
	__debugfs_register("dl_", rx, dentry);
	__debugfs_register("dl_", tx, dentry);

	/* Don't touch these if you don't know what you are doing */
	fd = debugfs_create_u8("rx_size_auto_shrink", 0600, dentry,
			       &i2400mu->rx_size_auto_shrink);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"rx_size_auto_shrink: %d\n", result);
		goto error;
	}

	fd = debugfs_create_size_t("rx_size", 0600, dentry,
				   &i2400mu->rx_size);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"rx_size: %d\n", result);
		goto error;
	}

	return 0;

error:
	debugfs_remove_recursive(i2400mu->debugfs_dentry);
	return result;
}