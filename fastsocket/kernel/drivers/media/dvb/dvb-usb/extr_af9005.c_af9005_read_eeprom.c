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
struct dvb_usb_device {struct af9005_device_state* priv; } ;
struct af9005_device_state {int /*<<< orphan*/  sequence; } ;
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  ibuf ;

/* Variables and functions */
 int EIO ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int af9005_read_eeprom(struct dvb_usb_device *d, u8 address, u8 * values,
		       int len)
{
	struct af9005_device_state *st = d->priv;
	u8 obuf[16], ibuf[14];
	int ret, i;

	memset(obuf, 0, sizeof(obuf));
	memset(ibuf, 0, sizeof(ibuf));

	obuf[0] = 14;		/* length of rest of packet low */
	obuf[1] = 0;		/* length of rest of packer high */

	obuf[2] = 0x2a;		/* read/write eeprom */

	obuf[3] = 12;		/* size */

	obuf[4] = st->sequence++;

	obuf[5] = 0;		/* read */

	obuf[6] = len;
	obuf[7] = address;
	ret = dvb_usb_generic_rw(d, obuf, 16, ibuf, 14, 0);
	if (ret)
		return ret;
	if (ibuf[2] != 0x2b) {
		err("Read eeprom, invalid reply code");
		return -EIO;
	}
	if (ibuf[3] != 10) {
		err("Read eeprom, invalid reply length");
		return -EIO;
	}
	if (ibuf[4] != obuf[4]) {
		err("Read eeprom, wrong sequence in reply ");
		return -EIO;
	}
	if (ibuf[5] != 1) {
		err("Read eeprom, wrong status in reply ");
		return -EIO;
	}
	for (i = 0; i < len; i++) {
		values[i] = ibuf[6 + i];
	}
	return 0;
}