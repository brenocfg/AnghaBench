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

/* Variables and functions */
 size_t IEV_SZ ; 
 scalar_t__ SEQ_1 ; 
 int SEQ_MAX_QUEUE ; 
 int iqlen ; 
 size_t iqtail ; 
 int /*<<< orphan*/ * iqueue ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  midi_sleeper ; 
 scalar_t__ seq_mode ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void seq_copy_to_input(unsigned char *event_rec, int len)
{
	unsigned long flags;

	/*
	 * Verify that the len is valid for the current mode.
	 */

	if (len != 4 && len != 8)
		return;
	if ((seq_mode == SEQ_1) != (len == 4))
		return;

	if (iqlen >= (SEQ_MAX_QUEUE - 1))
		return;		/* Overflow */

	spin_lock_irqsave(&lock,flags);
	memcpy(&iqueue[iqtail * IEV_SZ], event_rec, len);
	iqlen++;
	iqtail = (iqtail + 1) % SEQ_MAX_QUEUE;
	wake_up(&midi_sleeper);
	spin_unlock_irqrestore(&lock,flags);
}