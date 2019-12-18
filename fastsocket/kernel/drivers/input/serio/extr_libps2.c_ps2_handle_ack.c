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
struct ps2dev {int nak; int flags; int /*<<< orphan*/  wait; scalar_t__ cmdcnt; } ;

/* Variables and functions */
 int PS2_FLAG_ACK ; 
 int PS2_FLAG_CMD ; 
 int PS2_FLAG_CMD1 ; 
 int PS2_FLAG_NAK ; 
 int PS2_FLAG_WAITID ; 
#define  PS2_RET_ACK 130 
#define  PS2_RET_ERR 129 
#define  PS2_RET_NAK 128 
 int /*<<< orphan*/  ps2_handle_response (struct ps2dev*,unsigned char) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int ps2_handle_ack(struct ps2dev *ps2dev, unsigned char data)
{
	switch (data) {
		case PS2_RET_ACK:
			ps2dev->nak = 0;
			break;

		case PS2_RET_NAK:
			ps2dev->flags |= PS2_FLAG_NAK;
			ps2dev->nak = PS2_RET_NAK;
			break;

		case PS2_RET_ERR:
			if (ps2dev->flags & PS2_FLAG_NAK) {
				ps2dev->flags &= ~PS2_FLAG_NAK;
				ps2dev->nak = PS2_RET_ERR;
				break;
			}

		/*
		 * Workaround for mice which don't ACK the Get ID command.
		 * These are valid mouse IDs that we recognize.
		 */
		case 0x00:
		case 0x03:
		case 0x04:
			if (ps2dev->flags & PS2_FLAG_WAITID) {
				ps2dev->nak = 0;
				break;
			}
			/* Fall through */
		default:
			return 0;
	}


	if (!ps2dev->nak) {
		ps2dev->flags &= ~PS2_FLAG_NAK;
		if (ps2dev->cmdcnt)
			ps2dev->flags |= PS2_FLAG_CMD | PS2_FLAG_CMD1;
	}

	ps2dev->flags &= ~PS2_FLAG_ACK;
	wake_up(&ps2dev->wait);

	if (data != PS2_RET_ACK)
		ps2_handle_response(ps2dev, data);

	return 1;
}