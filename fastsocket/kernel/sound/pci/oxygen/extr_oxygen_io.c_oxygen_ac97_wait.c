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
typedef  unsigned int u8 ;
struct oxygen {int /*<<< orphan*/  ac97_waitqueue; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OXYGEN_AC97_INTERRUPT_STATUS ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 unsigned int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int oxygen_ac97_wait(struct oxygen *chip, unsigned int mask)
{
	u8 status = 0;

	/*
	 * Reading the status register also clears the bits, so we have to save
	 * the read bits in status.
	 */
	wait_event_timeout(chip->ac97_waitqueue,
			   ({ status |= oxygen_read8(chip, OXYGEN_AC97_INTERRUPT_STATUS);
			      status & mask; }),
			   msecs_to_jiffies(1) + 1);
	/*
	 * Check even after a timeout because this function should not require
	 * the AC'97 interrupt to be enabled.
	 */
	status |= oxygen_read8(chip, OXYGEN_AC97_INTERRUPT_STATUS);
	return status & mask ? 0 : -EIO;
}