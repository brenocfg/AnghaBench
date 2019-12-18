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
struct vpif_fh {scalar_t__ initialized; int /*<<< orphan*/  prio; scalar_t__* io_allowed; struct channel_obj* channel; } ;
struct file {struct vpif_fh* private_data; } ;
struct common_obj {int started; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_queue; scalar_t__ io_usrs; } ;
struct channel_obj {scalar_t__ channel_id; scalar_t__ initialized; int /*<<< orphan*/  prio; int /*<<< orphan*/  usrs; struct common_obj* common; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ VPIF_CHANNEL0_VIDEO ; 
 scalar_t__ VPIF_CHANNEL1_VIDEO ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  channel0_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel1_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  enable_channel0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_channel1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vpif_fh*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_release(struct file *filep)
{
	struct vpif_fh *fh = filep->private_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common;

	vpif_dbg(2, debug, "vpif_release\n");

	common = &ch->common[VPIF_VIDEO_INDEX];

	if (mutex_lock_interruptible(&common->lock))
		return -ERESTARTSYS;

	/* if this instance is doing IO */
	if (fh->io_allowed[VPIF_VIDEO_INDEX]) {
		/* Reset io_usrs member of channel object */
		common->io_usrs = 0;
		/* Disable channel as per its device type and channel id */
		if (VPIF_CHANNEL0_VIDEO == ch->channel_id) {
			enable_channel0(0);
			channel0_intr_enable(0);
		}
		if ((VPIF_CHANNEL1_VIDEO == ch->channel_id) ||
		    (2 == common->started)) {
			enable_channel1(0);
			channel1_intr_enable(0);
		}
		common->started = 0;
		/* Free buffers allocated */
		videobuf_queue_cancel(&common->buffer_queue);
		videobuf_mmap_free(&common->buffer_queue);
	}

	/* Decrement channel usrs counter */
	ch->usrs--;

	/* unlock mutex on channel object */
	mutex_unlock(&common->lock);

	/* Close the priority */
	v4l2_prio_close(&ch->prio, &fh->prio);

	if (fh->initialized)
		ch->initialized = 0;

	filep->private_data = NULL;
	kfree(fh);
	return 0;
}