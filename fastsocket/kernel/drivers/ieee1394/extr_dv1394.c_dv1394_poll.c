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
struct video_card {scalar_t__ n_frames; int active_frame; scalar_t__ n_clear_frames; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  waitq; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 struct video_card* file_to_video_card (struct file*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int dv1394_poll(struct file *file, struct poll_table_struct *wait)
{
	struct video_card *video = file_to_video_card(file);
	unsigned int mask = 0;
	unsigned long flags;

	poll_wait(file, &video->waitq, wait);

	spin_lock_irqsave(&video->spinlock, flags);
	if ( video->n_frames == 0 ) {

	} else if ( video->active_frame == -1 ) {
		/* nothing going on */
		mask |= POLLOUT;
	} else {
		/* any clear/ready buffers? */
		if (video->n_clear_frames >0)
			mask |= POLLOUT | POLLIN;
	}
	spin_unlock_irqrestore(&video->spinlock, flags);

	return mask;
}