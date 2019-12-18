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
typedef  int /*<<< orphan*/  wait_queue_t ;
struct TYPE_2__ {int /*<<< orphan*/  frame_wait_queue; } ;
struct vino_channel_settings {TYPE_1__ fb_queue; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vino_wait_for_frame(struct vino_channel_settings *vcs)
{
	wait_queue_t wait;
	int err = 0;

	dprintk("vino_wait_for_frame():\n");

	init_waitqueue_entry(&wait, current);
	/* add ourselves into wait queue */
	add_wait_queue(&vcs->fb_queue.frame_wait_queue, &wait);

	/* to ensure that schedule_timeout will return immediately
	 * if VINO interrupt was triggered meanwhile */
	schedule_timeout_interruptible(msecs_to_jiffies(100));

	if (signal_pending(current))
		err = -EINTR;

	remove_wait_queue(&vcs->fb_queue.frame_wait_queue, &wait);

	dprintk("vino_wait_for_frame(): waiting for frame %s\n",
		err ? "failed" : "ok");

	return err;
}