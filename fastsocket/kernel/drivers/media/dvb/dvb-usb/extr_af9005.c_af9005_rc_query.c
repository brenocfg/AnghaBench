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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct dvb_usb_device {int /*<<< orphan*/  last_event; struct af9005_device_state* priv; } ;
struct af9005_device_state {int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int EIO ; 
 int REMOTE_KEY_REPEAT ; 
 int REMOTE_NO_KEY_PRESSED ; 
 int /*<<< orphan*/  deb_rc (char*,int,...) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*,int,int /*<<< orphan*/ )) ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int rc_decode (struct dvb_usb_device*,int*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int af9005_rc_query(struct dvb_usb_device *d, u32 * event, int *state)
{
	struct af9005_device_state *st = d->priv;
	int ret, len;

	u8 obuf[5];
	u8 ibuf[256];

	*state = REMOTE_NO_KEY_PRESSED;
	if (rc_decode == NULL) {
		/* it shouldn't never come here */
		return 0;
	}
	/* deb_info("rc_query\n"); */
	obuf[0] = 3;		/* rest of packet length low */
	obuf[1] = 0;		/* rest of packet lentgh high */
	obuf[2] = 0x40;		/* read remote */
	obuf[3] = 1;		/* rest of packet length */
	obuf[4] = st->sequence++;	/* sequence number */
	ret = dvb_usb_generic_rw(d, obuf, 5, ibuf, 256, 0);
	if (ret) {
		err("rc query failed");
		return ret;
	}
	if (ibuf[2] != 0x41) {
		err("rc query bad header.");
		return -EIO;
	}
	if (ibuf[4] != obuf[4]) {
		err("rc query bad sequence.");
		return -EIO;
	}
	len = ibuf[5];
	if (len > 246) {
		err("rc query invalid length");
		return -EIO;
	}
	if (len > 0) {
		deb_rc("rc data (%d) ", len);
		debug_dump((ibuf + 6), len, deb_rc);
		ret = rc_decode(d, &ibuf[6], len, event, state);
		if (ret) {
			err("rc_decode failed");
			return ret;
		} else {
			deb_rc("rc_decode state %x event %x\n", *state, *event);
			if (*state == REMOTE_KEY_REPEAT)
				*event = d->last_event;
		}
	}
	return 0;
}