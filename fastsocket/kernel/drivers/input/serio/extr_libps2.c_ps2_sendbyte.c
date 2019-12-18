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
struct ps2dev {int nak; int flags; int /*<<< orphan*/  serio; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int PS2_FLAG_ACK ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 
 scalar_t__ serio_write (int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ps2_sendbyte(struct ps2dev *ps2dev, unsigned char byte, int timeout)
{
	serio_pause_rx(ps2dev->serio);
	ps2dev->nak = 1;
	ps2dev->flags |= PS2_FLAG_ACK;
	serio_continue_rx(ps2dev->serio);

	if (serio_write(ps2dev->serio, byte) == 0)
		wait_event_timeout(ps2dev->wait,
				   !(ps2dev->flags & PS2_FLAG_ACK),
				   msecs_to_jiffies(timeout));

	serio_pause_rx(ps2dev->serio);
	ps2dev->flags &= ~PS2_FLAG_ACK;
	serio_continue_rx(ps2dev->serio);

	return -ps2dev->nak;
}