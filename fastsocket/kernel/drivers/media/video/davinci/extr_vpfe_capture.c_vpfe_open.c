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
struct vpfe_fh {int /*<<< orphan*/  prio; scalar_t__ io_allowed; struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  prio; int /*<<< orphan*/  usrs; int /*<<< orphan*/  initialized; int /*<<< orphan*/  v4l2_dev; TYPE_1__* cfg; } ;
struct file {struct vpfe_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_subdevs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_PRIORITY_UNSET ; 
 int /*<<< orphan*/  debug ; 
 struct vpfe_fh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_prio_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 scalar_t__ vpfe_initialize_device (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_open(struct file *file)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	struct vpfe_fh *fh;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_open\n");

	if (!vpfe_dev->cfg->num_subdevs) {
		v4l2_err(&vpfe_dev->v4l2_dev, "No decoder registered\n");
		return -ENODEV;
	}

	/* Allocate memory for the file handle object */
	fh = kmalloc(sizeof(struct vpfe_fh), GFP_KERNEL);
	if (NULL == fh) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"unable to allocate memory for file handle object\n");
		return -ENOMEM;
	}
	/* store pointer to fh in private_data member of file */
	file->private_data = fh;
	fh->vpfe_dev = vpfe_dev;
	mutex_lock(&vpfe_dev->lock);
	/* If decoder is not initialized. initialize it */
	if (!vpfe_dev->initialized) {
		if (vpfe_initialize_device(vpfe_dev)) {
			mutex_unlock(&vpfe_dev->lock);
			return -ENODEV;
		}
	}
	/* Increment device usrs counter */
	vpfe_dev->usrs++;
	/* Set io_allowed member to false */
	fh->io_allowed = 0;
	/* Initialize priority of this instance to default priority */
	fh->prio = V4L2_PRIORITY_UNSET;
	v4l2_prio_open(&vpfe_dev->prio, &fh->prio);
	mutex_unlock(&vpfe_dev->lock);
	return 0;
}