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
struct snapshot_handle {int dummy; } ;
struct snapshot_data {int swap; int mode; scalar_t__ platform_support; scalar_t__ ready; scalar_t__ frozen; int /*<<< orphan*/  handle; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct snapshot_data* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PM_HIBERNATION_PREPARE ; 
 int /*<<< orphan*/  PM_POST_HIBERNATION ; 
 int /*<<< orphan*/  PM_POST_RESTORE ; 
 int /*<<< orphan*/  PM_RESTORE_PREPARE ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ create_basic_memory_bitmaps () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pm_mutex ; 
 int pm_notifier_call_chain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snapshot_device_available ; 
 struct snapshot_data snapshot_state ; 
 int swap_type_of (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ swsusp_resume_device ; 
 int /*<<< orphan*/  wait_for_device_probe () ; 

__attribute__((used)) static int snapshot_open(struct inode *inode, struct file *filp)
{
	struct snapshot_data *data;
	int error;

	mutex_lock(&pm_mutex);

	if (!atomic_add_unless(&snapshot_device_available, -1, 0)) {
		error = -EBUSY;
		goto Unlock;
	}

	if ((filp->f_flags & O_ACCMODE) == O_RDWR) {
		atomic_inc(&snapshot_device_available);
		error = -ENOSYS;
		goto Unlock;
	}
	if(create_basic_memory_bitmaps()) {
		atomic_inc(&snapshot_device_available);
		error = -ENOMEM;
		goto Unlock;
	}
	nonseekable_open(inode, filp);
	data = &snapshot_state;
	filp->private_data = data;
	memset(&data->handle, 0, sizeof(struct snapshot_handle));
	if ((filp->f_flags & O_ACCMODE) == O_RDONLY) {
		/* Hibernating.  The image device should be accessible. */
		data->swap = swsusp_resume_device ?
			swap_type_of(swsusp_resume_device, 0, NULL) : -1;
		data->mode = O_RDONLY;
		error = pm_notifier_call_chain(PM_HIBERNATION_PREPARE);
		if (error)
			pm_notifier_call_chain(PM_POST_HIBERNATION);
	} else {
		/*
		 * Resuming.  We may need to wait for the image device to
		 * appear.
		 */
		wait_for_device_probe();

		data->swap = -1;
		data->mode = O_WRONLY;
		error = pm_notifier_call_chain(PM_RESTORE_PREPARE);
		if (error)
			pm_notifier_call_chain(PM_POST_RESTORE);
	}
	if (error)
		atomic_inc(&snapshot_device_available);
	data->frozen = 0;
	data->ready = 0;
	data->platform_support = 0;

 Unlock:
	mutex_unlock(&pm_mutex);

	return error;
}