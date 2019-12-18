#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ci_name; } ;
struct o2hb_region {scalar_t__ hr_blocks; scalar_t__ hr_start_block; int hr_block_bytes; scalar_t__ hr_generation; int /*<<< orphan*/ * hr_bdev; struct task_struct* hr_task; int /*<<< orphan*/  hr_steady_iterations; TYPE_2__ hr_item; int /*<<< orphan*/  hr_write_timeout_work; int /*<<< orphan*/  hr_dev_name; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  size_t ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long INT_MAX ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/ * I_BDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ O2HB_LIVE_THRESHOLD ; 
 scalar_t__ O2NM_MAX_NODES ; 
 size_t PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int bdev_logical_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t blkdev_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,int) ; 
 struct file* fget (long) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 
 struct inode* igrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct o2hb_region*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mlog_errno (size_t) ; 
 int /*<<< orphan*/  o2hb_init_region_params (struct o2hb_region*) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 size_t o2hb_map_slot_data (struct o2hb_region*) ; 
 size_t o2hb_populate_slot_data (struct o2hb_region*) ; 
 int /*<<< orphan*/  o2hb_steady_queue ; 
 int /*<<< orphan*/  o2hb_thread ; 
 int /*<<< orphan*/  o2hb_write_timeout ; 
 scalar_t__ o2nm_this_node () ; 
 long simple_strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t o2hb_region_dev_write(struct o2hb_region *reg,
				     const char *page,
				     size_t count)
{
	struct task_struct *hb_task;
	long fd;
	int sectsize;
	char *p = (char *)page;
	struct file *filp = NULL;
	struct inode *inode = NULL;
	ssize_t ret = -EINVAL;

	if (reg->hr_bdev)
		goto out;

	/* We can't heartbeat without having had our node number
	 * configured yet. */
	if (o2nm_this_node() == O2NM_MAX_NODES)
		goto out;

	fd = simple_strtol(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		goto out;

	if (fd < 0 || fd >= INT_MAX)
		goto out;

	filp = fget(fd);
	if (filp == NULL)
		goto out;

	if (reg->hr_blocks == 0 || reg->hr_start_block == 0 ||
	    reg->hr_block_bytes == 0)
		goto out;

	inode = igrab(filp->f_mapping->host);
	if (inode == NULL)
		goto out;

	if (!S_ISBLK(inode->i_mode))
		goto out;

	reg->hr_bdev = I_BDEV(filp->f_mapping->host);
	ret = blkdev_get(reg->hr_bdev, FMODE_WRITE | FMODE_READ);
	if (ret) {
		reg->hr_bdev = NULL;
		goto out;
	}
	inode = NULL;

	bdevname(reg->hr_bdev, reg->hr_dev_name);

	sectsize = bdev_logical_block_size(reg->hr_bdev);
	if (sectsize != reg->hr_block_bytes) {
		mlog(ML_ERROR,
		     "blocksize %u incorrect for device, expected %d",
		     reg->hr_block_bytes, sectsize);
		ret = -EINVAL;
		goto out;
	}

	o2hb_init_region_params(reg);

	/* Generation of zero is invalid */
	do {
		get_random_bytes(&reg->hr_generation,
				 sizeof(reg->hr_generation));
	} while (reg->hr_generation == 0);

	ret = o2hb_map_slot_data(reg);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = o2hb_populate_slot_data(reg);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	INIT_DELAYED_WORK(&reg->hr_write_timeout_work, o2hb_write_timeout);

	/*
	 * A node is considered live after it has beat LIVE_THRESHOLD
	 * times.  We're not steady until we've given them a chance
	 * _after_ our first read.
	 */
	atomic_set(&reg->hr_steady_iterations, O2HB_LIVE_THRESHOLD + 1);

	hb_task = kthread_run(o2hb_thread, reg, "o2hb-%s",
			      reg->hr_item.ci_name);
	if (IS_ERR(hb_task)) {
		ret = PTR_ERR(hb_task);
		mlog_errno(ret);
		goto out;
	}

	spin_lock(&o2hb_live_lock);
	reg->hr_task = hb_task;
	spin_unlock(&o2hb_live_lock);

	ret = wait_event_interruptible(o2hb_steady_queue,
				atomic_read(&reg->hr_steady_iterations) == 0);
	if (ret) {
		/* We got interrupted (hello ptrace!).  Clean up */
		spin_lock(&o2hb_live_lock);
		hb_task = reg->hr_task;
		reg->hr_task = NULL;
		spin_unlock(&o2hb_live_lock);

		if (hb_task)
			kthread_stop(hb_task);
		goto out;
	}

	/* Ok, we were woken.  Make sure it wasn't by drop_item() */
	spin_lock(&o2hb_live_lock);
	hb_task = reg->hr_task;
	spin_unlock(&o2hb_live_lock);

	if (hb_task)
		ret = count;
	else
		ret = -EIO;

out:
	if (filp)
		fput(filp);
	if (inode)
		iput(inode);
	if (ret < 0) {
		if (reg->hr_bdev) {
			blkdev_put(reg->hr_bdev, FMODE_READ|FMODE_WRITE);
			reg->hr_bdev = NULL;
		}
	}
	return ret;
}