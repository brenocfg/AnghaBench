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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_rc_key {int /*<<< orphan*/  event; } ;
struct TYPE_2__ {int rc_key_map_size; struct dvb_usb_rc_key* rc_key_map; } ;
struct dvb_usb_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_IR_CODE ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  cxusb_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ rc5_custom (struct dvb_usb_rc_key*) ; 
 scalar_t__ rc5_data (struct dvb_usb_rc_key*) ; 

__attribute__((used)) static int cxusb_rc_query(struct dvb_usb_device *d, u32 *event, int *state)
{
	struct dvb_usb_rc_key *keymap = d->props.rc_key_map;
	u8 ircode[4];
	int i;

	cxusb_ctrl_msg(d, CMD_GET_IR_CODE, NULL, 0, ircode, 4);

	*event = 0;
	*state = REMOTE_NO_KEY_PRESSED;

	for (i = 0; i < d->props.rc_key_map_size; i++) {
		if (rc5_custom(&keymap[i]) == ircode[2] &&
		    rc5_data(&keymap[i]) == ircode[3]) {
			*event = keymap[i].event;
			*state = REMOTE_KEY_PRESSED;

			return 0;
		}
	}

	return 0;
}