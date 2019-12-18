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
struct TYPE_2__ {int /*<<< orphan*/  frame_wait_queue; } ;
struct vino_channel_settings {TYPE_1__ fb_queue; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 scalar_t__ vino_queue_get_outgoing (TYPE_1__*,unsigned int*) ; 

__attribute__((used)) static unsigned int vino_poll(struct file *file, poll_table *pt)
{
	struct vino_channel_settings *vcs = video_drvdata(file);
	unsigned int outgoing;
	unsigned int ret = 0;

	// lock mutex (?)
	// TODO: this has to be corrected for different read modes

	dprintk("poll():\n");

	if (vino_queue_get_outgoing(&vcs->fb_queue, &outgoing)) {
		dprintk("poll(): vino_queue_get_outgoing() failed\n");
		ret = POLLERR;
		goto error;
	}
	if (outgoing > 0)
		goto over;

	poll_wait(file, &vcs->fb_queue.frame_wait_queue, pt);

	if (vino_queue_get_outgoing(&vcs->fb_queue, &outgoing)) {
		dprintk("poll(): vino_queue_get_outgoing() failed\n");
		ret = POLLERR;
		goto error;
	}

over:
	dprintk("poll(): data %savailable\n",
		(outgoing > 0) ? "" : "not ");

	if (outgoing > 0)
		ret = POLLIN | POLLRDNORM;

error:
	return ret;
}