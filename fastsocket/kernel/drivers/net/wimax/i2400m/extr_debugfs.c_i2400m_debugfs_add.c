#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct dentry* debugfs_dentry; } ;
struct i2400m {int /*<<< orphan*/  trace_msg_from_user; int /*<<< orphan*/  state; int /*<<< orphan*/  tx_out; int /*<<< orphan*/  tx_in; struct dentry* debugfs_dentry; TYPE_1__ wimax_dev; } ;
struct device {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  __debugfs_register (char*,int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  debugfs ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct i2400m*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_i2400m_reset (char*,struct dentry*,struct i2400m*) ; 
 struct dentry* debugfs_create_i2400m_suspend (char*,struct dentry*,struct i2400m*) ; 
 struct dentry* debugfs_create_netdev_queue_stopped (char*,struct dentry*,struct i2400m*) ; 
 struct dentry* debugfs_create_size_t (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  driver ; 
 int /*<<< orphan*/  fw ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_rx_stats_fops ; 
 int /*<<< orphan*/  i2400m_tx_stats_fops ; 
 int /*<<< orphan*/  netdev ; 
 int /*<<< orphan*/  rfkill ; 
 int /*<<< orphan*/  rx ; 
 int /*<<< orphan*/  tx ; 

int i2400m_debugfs_add(struct i2400m *i2400m)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	struct dentry *dentry = i2400m->wimax_dev.debugfs_dentry;
	struct dentry *fd;

	dentry = debugfs_create_dir("i2400m", dentry);
	result = PTR_ERR(dentry);
	if (IS_ERR(dentry)) {
		if (result == -ENODEV)
			result = 0;	/* No debugfs support */
		goto error;
	}
	i2400m->debugfs_dentry = dentry;
	__debugfs_register("dl_", control, dentry);
	__debugfs_register("dl_", driver, dentry);
	__debugfs_register("dl_", debugfs, dentry);
	__debugfs_register("dl_", fw, dentry);
	__debugfs_register("dl_", netdev, dentry);
	__debugfs_register("dl_", rfkill, dentry);
	__debugfs_register("dl_", rx, dentry);
	__debugfs_register("dl_", tx, dentry);

	fd = debugfs_create_size_t("tx_in", 0400, dentry,
				   &i2400m->tx_in);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"tx_in: %d\n", result);
		goto error;
	}

	fd = debugfs_create_size_t("tx_out", 0400, dentry,
				   &i2400m->tx_out);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"tx_out: %d\n", result);
		goto error;
	}

	fd = debugfs_create_u32("state", 0600, dentry,
				&i2400m->state);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"state: %d\n", result);
		goto error;
	}

	/*
	 * Trace received messages from user space
	 *
	 * In order to tap the bidirectional message stream in the
	 * 'msg' pipe, user space can read from the 'msg' pipe;
	 * however, due to limitations in libnl, we can't know what
	 * the different applications are sending down to the kernel.
	 *
	 * So we have this hack where the driver will echo any message
	 * received on the msg pipe from user space [through a call to
	 * wimax_dev->op_msg_from_user() into
	 * i2400m_op_msg_from_user()] into the 'trace' pipe that this
	 * driver creates.
	 *
	 * So then, reading from both the 'trace' and 'msg' pipes in
	 * user space will provide a full dump of the traffic.
	 *
	 * Write 1 to activate, 0 to clear.
	 *
	 * It is not really very atomic, but it is also not too
	 * critical.
	 */
	fd = debugfs_create_u8("trace_msg_from_user", 0600, dentry,
			       &i2400m->trace_msg_from_user);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"trace_msg_from_user: %d\n", result);
		goto error;
	}

	fd = debugfs_create_netdev_queue_stopped("netdev_queue_stopped",
						 dentry, i2400m);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"netdev_queue_stopped: %d\n", result);
		goto error;
	}

	fd = debugfs_create_file("rx_stats", 0600, dentry, i2400m,
				 &i2400m_rx_stats_fops);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"rx_stats: %d\n", result);
		goto error;
	}

	fd = debugfs_create_file("tx_stats", 0600, dentry, i2400m,
				 &i2400m_tx_stats_fops);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry "
			"tx_stats: %d\n", result);
		goto error;
	}

	fd = debugfs_create_i2400m_suspend("suspend", dentry, i2400m);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry suspend: %d\n",
			result);
		goto error;
	}

	fd = debugfs_create_i2400m_reset("reset", dentry, i2400m);
	result = PTR_ERR(fd);
	if (IS_ERR(fd) && result != -ENODEV) {
		dev_err(dev, "Can't create debugfs entry reset: %d\n", result);
		goto error;
	}

	result = 0;
error:
	return result;
}