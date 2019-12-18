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
struct sn9c102_device {int state; int /*<<< orphan*/  kref; int /*<<< orphan*/  open_mutex; TYPE_1__* v4ldev; scalar_t__ frame_count; scalar_t__ nbuffers; int /*<<< orphan*/  stream; int /*<<< orphan*/  io; scalar_t__ users; int /*<<< orphan*/  wait_open; int /*<<< orphan*/  probe; } ;
struct file {int f_flags; struct sn9c102_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,...) ; 
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  IO_NONE ; 
 int O_NDELAY ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  STREAM_OFF ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn9c102_dev_lock ; 
 int /*<<< orphan*/  sn9c102_empty_framequeues (struct sn9c102_device*) ; 
 int sn9c102_init (struct sn9c102_device*) ; 
 int /*<<< orphan*/  sn9c102_release_resources ; 
 int sn9c102_start_transfer (struct sn9c102_device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct sn9c102_device* video_drvdata (struct file*) ; 
 int wait_event_interruptible_exclusive (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sn9c102_open(struct file *filp)
{
	struct sn9c102_device* cam;
	int err = 0;

	/*
	   A read_trylock() in open() is the only safe way to prevent race
	   conditions with disconnect(), one close() and multiple (not
	   necessarily simultaneous) attempts to open(). For example, it
	   prevents from waiting for a second access, while the device
	   structure is being deallocated, after a possible disconnect() and
	   during a following close() holding the write lock: given that, after
	   this deallocation, no access will be possible anymore, using the
	   non-trylock version would have let open() gain the access to the
	   device structure improperly.
	   For this reason the lock must also not be per-device.
	*/
	if (!down_read_trylock(&sn9c102_dev_lock))
		return -ERESTARTSYS;

	cam = video_drvdata(filp);

	if (wait_for_completion_interruptible(&cam->probe)) {
		up_read(&sn9c102_dev_lock);
		return -ERESTARTSYS;
	}

	kref_get(&cam->kref);

	/*
	    Make sure to isolate all the simultaneous opens.
	*/
	if (mutex_lock_interruptible(&cam->open_mutex)) {
		kref_put(&cam->kref, sn9c102_release_resources);
		up_read(&sn9c102_dev_lock);
		return -ERESTARTSYS;
	}

	if (cam->state & DEV_DISCONNECTED) {
		DBG(1, "Device not present");
		err = -ENODEV;
		goto out;
	}

	if (cam->users) {
		DBG(2, "Device /dev/video%d is already in use",
		       cam->v4ldev->num);
		DBG(3, "Simultaneous opens are not supported");
		/*
		   open() must follow the open flags and should block
		   eventually while the device is in use.
		*/
		if ((filp->f_flags & O_NONBLOCK) ||
		    (filp->f_flags & O_NDELAY)) {
			err = -EWOULDBLOCK;
			goto out;
		}
		DBG(2, "A blocking open() has been requested. Wait for the "
		       "device to be released...");
		up_read(&sn9c102_dev_lock);
		/*
		   We will not release the "open_mutex" lock, so that only one
		   process can be in the wait queue below. This way the process
		   will be sleeping while holding the lock, without loosing its
		   priority after any wake_up().
		*/
		err = wait_event_interruptible_exclusive(cam->wait_open,
						(cam->state & DEV_DISCONNECTED)
							 || !cam->users);
		down_read(&sn9c102_dev_lock);
		if (err)
			goto out;
		if (cam->state & DEV_DISCONNECTED) {
			err = -ENODEV;
			goto out;
		}
	}

	if (cam->state & DEV_MISCONFIGURED) {
		err = sn9c102_init(cam);
		if (err) {
			DBG(1, "Initialization failed again. "
			       "I will retry on next open().");
			goto out;
		}
		cam->state &= ~DEV_MISCONFIGURED;
	}

	if ((err = sn9c102_start_transfer(cam)))
		goto out;

	filp->private_data = cam;
	cam->users++;
	cam->io = IO_NONE;
	cam->stream = STREAM_OFF;
	cam->nbuffers = 0;
	cam->frame_count = 0;
	sn9c102_empty_framequeues(cam);

	DBG(3, "Video device /dev/video%d is open", cam->v4ldev->num);

out:
	mutex_unlock(&cam->open_mutex);
	if (err)
		kref_put(&cam->kref, sn9c102_release_resources);

	up_read(&sn9c102_dev_lock);
	return err;
}