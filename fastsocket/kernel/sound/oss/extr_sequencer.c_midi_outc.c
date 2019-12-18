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
struct TYPE_2__ {int /*<<< orphan*/  (* outputc ) (int,unsigned char) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  interruptible_sleep_on_timeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock ; 
 TYPE_1__** midi_devs ; 
 int /*<<< orphan*/  seq_sleeper ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int,unsigned char) ; 

__attribute__((used)) static void midi_outc(int dev, unsigned char data)
{
	/*
	 * NOTE! Calls sleep(). Don't call this from interrupt.
	 */

	int n;
	unsigned long flags;

	/*
	 * This routine sends one byte to the Midi channel.
	 * If the output FIFO is full, it waits until there
	 * is space in the queue
	 */

	n = 3 * HZ;		/* Timeout */

	spin_lock_irqsave(&lock,flags);
 	while (n && !midi_devs[dev]->outputc(dev, data)) {
 		interruptible_sleep_on_timeout(&seq_sleeper, HZ/25);
  		n--;
  	}
	spin_unlock_irqrestore(&lock,flags);
}