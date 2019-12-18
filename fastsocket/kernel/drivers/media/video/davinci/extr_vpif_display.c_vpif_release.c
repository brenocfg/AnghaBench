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
struct vpif_fh {scalar_t__ initialized; int /*<<< orphan*/  prio; scalar_t__* io_allowed; struct channel_obj* channel; } ;
struct file {struct vpif_fh* private_data; } ;
struct common_obj {int started; int /*<<< orphan*/  lock; int /*<<< orphan*/  numbuffers; int /*<<< orphan*/  buffer_queue; scalar_t__ io_usrs; } ;
struct channel_obj {size_t channel_id; int /*<<< orphan*/  prio; scalar_t__ initialized; int /*<<< orphan*/  usrs; struct common_obj* common; } ;
struct TYPE_2__ {int /*<<< orphan*/ * numbuffers; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 size_t VPIF_CHANNEL2_VIDEO ; 
 size_t VPIF_CHANNEL3_VIDEO ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel2_intr_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel3_intr_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__ config_params ; 
 int /*<<< orphan*/  enable_channel2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_channel3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vpif_fh*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_mmap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpif_release(struct file *filep)
{
	struct vpif_fh *fh = filep->private_data;
	struct channel_obj *ch = fh->channel;
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];

	if (mutex_lock_interruptible(&common->lock))
		return -ERESTARTSYS;

	/* if this instance is doing IO */
	if (fh->io_allowed[VPIF_VIDEO_INDEX]) {
		/* Reset io_usrs member of channel object */
		common->io_usrs = 0;
		/* Disable channel */
		if (VPIF_CHANNEL2_VIDEO == ch->channel_id) {
			enable_channel2(0);
			channel2_intr_enable(0);
		}
		if ((VPIF_CHANNEL3_VIDEO == ch->channel_id) ||
		    (2 == common->started)) {
			enable_channel3(0);
			channel3_intr_enable(0);
		}
		common->started = 0;
		/* Free buffers allocated */
		videobuf_queue_cancel(&common->buffer_queue);
		videobuf_mmap_free(&common->buffer_queue);
		common->numbuffers =
		    config_params.numbuffers[ch->channel_id];
	}

	mutex_unlock(&common->lock);

	/* Decrement channel usrs counter */
	atomic_dec(&ch->usrs);
	/* If this file handle has initialize encoder device, reset it */
	if (fh->initialized)
		ch->initialized = 0;

	/* Close the priority */
	v4l2_prio_close(&ch->prio, &fh->prio);
	filep->private_data = NULL;
	fh->initialized = 0;
	kfree(fh);

	return 0;
}