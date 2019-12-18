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

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 

int af9005_send_command(struct dvb_usb_device *d, u8 command, u8 * wbuf,
			int wlen, u8 * rbuf, int rlen)
{
	struct af9005_device_state *st = d->priv;

	int ret, i, packet_len;
	u8 buf[64];
	u8 ibuf[64];

	if (wlen < 0) {
		err("send command, wlen less than 0 bytes. Makes no sense.");
		return -EINVAL;
	}
	if (wlen > 54) {
		err("send command, wlen more than 54 bytes. Not supported.");
		return -EINVAL;
	}
	if (rlen > 54) {
		err("send command, rlen more than 54 bytes. Not supported.");
		return -EINVAL;
	}
	packet_len = wlen + 5;
	buf[0] = (u8) (packet_len & 0xff);
	buf[1] = (u8) ((packet_len & 0xff00) >> 8);

	buf[2] = 0x26;		/* packet type */
	buf[3] = wlen + 3;
	buf[4] = st->sequence++;
	buf[5] = command;
	buf[6] = wlen;
	for (i = 0; i < wlen; i++)
		buf[7 + i] = wbuf[i];
	ret = dvb_usb_generic_rw(d, buf, wlen + 7, ibuf, rlen + 7, 0);
	if (ret)
		return ret;
	if (ibuf[2] != 0x27) {
		err("send command, wrong reply code.");
		return -EIO;
	}
	if (ibuf[4] != buf[4]) {
		err("send command, wrong sequence in reply.");
		return -EIO;
	}
	if (ibuf[5] != 0x01) {
		err("send command, wrong status code in reply.");
		return -EIO;
	}
	if (ibuf[6] != rlen) {
		err("send command, invalid data length in reply.");
		return -EIO;
	}
	for (i = 0; i < rlen; i++)
		rbuf[i] = ibuf[i + 7];
	return 0;
}