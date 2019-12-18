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
struct ps2dev {int* cmdbuf; int /*<<< orphan*/  serio; int /*<<< orphan*/  cmdcnt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  PS2_CMD_GETID 129 
#define  PS2_CMD_RESET_BAT 128 
 int msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  ps2_is_keyboard_id (int) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps2_adjust_timeout(struct ps2dev *ps2dev, int command, int timeout)
{
	switch (command) {
		case PS2_CMD_RESET_BAT:
			/*
			 * Device has sent the first response byte after
			 * reset command, reset is thus done, so we can
			 * shorten the timeout.
			 * The next byte will come soon (keyboard) or not
			 * at all (mouse).
			 */
			if (timeout > msecs_to_jiffies(100))
				timeout = msecs_to_jiffies(100);
			break;

		case PS2_CMD_GETID:
			/*
			 * Microsoft Natural Elite keyboard responds to
			 * the GET ID command as it were a mouse, with
			 * a single byte. Fail the command so atkbd will
			 * use alternative probe to detect it.
			 */
			if (ps2dev->cmdbuf[1] == 0xaa) {
				serio_pause_rx(ps2dev->serio);
				ps2dev->flags = 0;
				serio_continue_rx(ps2dev->serio);
				timeout = 0;
			}

			/*
			 * If device behind the port is not a keyboard there
			 * won't be 2nd byte of ID response.
			 */
			if (!ps2_is_keyboard_id(ps2dev->cmdbuf[1])) {
				serio_pause_rx(ps2dev->serio);
				ps2dev->flags = ps2dev->cmdcnt = 0;
				serio_continue_rx(ps2dev->serio);
				timeout = 0;
			}
			break;

		default:
			break;
	}

	return timeout;
}