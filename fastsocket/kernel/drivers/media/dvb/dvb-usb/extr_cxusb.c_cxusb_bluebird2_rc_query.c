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
struct i2c_msg {int addr; scalar_t__* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_usb_rc_key {int /*<<< orphan*/  event; } ;
struct TYPE_2__ {int rc_key_map_size; struct dvb_usb_rc_key* rc_key_map; } ;
struct dvb_usb_device {TYPE_1__ props; int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int REMOTE_KEY_PRESSED ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int cxusb_i2c_xfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 scalar_t__ rc5_custom (struct dvb_usb_rc_key*) ; 
 scalar_t__ rc5_data (struct dvb_usb_rc_key*) ; 

__attribute__((used)) static int cxusb_bluebird2_rc_query(struct dvb_usb_device *d, u32 *event,
				    int *state)
{
	struct dvb_usb_rc_key *keymap = d->props.rc_key_map;
	u8 ircode[4];
	int i;
	struct i2c_msg msg = { .addr = 0x6b, .flags = I2C_M_RD,
			       .buf = ircode, .len = 4 };

	*event = 0;
	*state = REMOTE_NO_KEY_PRESSED;

	if (cxusb_i2c_xfer(&d->i2c_adap, &msg, 1) != 1)
		return 0;

	for (i = 0; i < d->props.rc_key_map_size; i++) {
		if (rc5_custom(&keymap[i]) == ircode[1] &&
		    rc5_data(&keymap[i]) == ircode[2]) {
			*event = keymap[i].event;
			*state = REMOTE_KEY_PRESSED;

			return 0;
		}
	}

	return 0;
}