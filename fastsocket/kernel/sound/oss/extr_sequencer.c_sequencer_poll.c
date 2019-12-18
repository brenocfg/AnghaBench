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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 scalar_t__ SEQ_MAX_QUEUE ; 
 scalar_t__ iqlen ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  midi_sleeper ; 
 scalar_t__ output_threshold ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qlen ; 
 int /*<<< orphan*/  seq_sleeper ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned int sequencer_poll(int dev, struct file *file, poll_table * wait)
{
	unsigned long flags;
	unsigned int mask = 0;

	dev = dev >> 4;

	spin_lock_irqsave(&lock,flags);
	/* input */
	poll_wait(file, &midi_sleeper, wait);
	if (iqlen)
		mask |= POLLIN | POLLRDNORM;

	/* output */
	poll_wait(file, &seq_sleeper, wait);
	if ((SEQ_MAX_QUEUE - qlen) >= output_threshold)
		mask |= POLLOUT | POLLWRNORM;
	spin_unlock_irqrestore(&lock,flags);
	return mask;
}