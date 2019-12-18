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
typedef  int u16 ;
struct lme2510_state {int i2c_gate; int i2c_tuner_addr; int i2c_tuner_gate_r; int i2c_tuner_gate_w; } ;
struct i2c_msg {int flags; int addr; int len; int* buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {struct lme2510_state* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  deb_info (int,char*) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ lme2510_msg (struct dvb_usb_device*,int*,int,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int lme2510_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
				 int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct lme2510_state *st = d->priv;
	static u8 obuf[64], ibuf[512];
	int i, read, read_o;
	u16 len;
	u8 gate = st->i2c_gate;

	if (gate == 0)
		gate = 5;

	if (num > 2)
		warn("more than 2 i2c messages"
			"at a time is not handled yet.	TODO.");

	for (i = 0; i < num; i++) {
		read_o = 1 & (msg[i].flags & I2C_M_RD);
		read = i+1 < num && (msg[i+1].flags & I2C_M_RD);
		read |= read_o;
		gate = (msg[i].addr == st->i2c_tuner_addr)
			? (read)	? st->i2c_tuner_gate_r
					: st->i2c_tuner_gate_w
			: st->i2c_gate;
		obuf[0] = gate | (read << 7);

		if (gate == 5)
			obuf[1] = (read) ? 2 : msg[i].len + 1;
		else
			obuf[1] = msg[i].len + read + 1;

		obuf[2] = msg[i].addr;
		if (read) {
			if (read_o)
				len = 3;
			else {
				memcpy(&obuf[3], msg[i].buf, msg[i].len);
				obuf[msg[i].len+3] = msg[i+1].len;
				len = msg[i].len+4;
			}
		} else {
			memcpy(&obuf[3], msg[i].buf, msg[i].len);
			len = msg[i].len+3;
		}

		if (lme2510_msg(d, obuf, len, ibuf, 512) < 0) {
			deb_info(1, "i2c transfer failed.");
			return -EAGAIN;
		}

		if (read) {
			if (read_o)
				memcpy(msg[i].buf, &ibuf[1], msg[i].len);
			else {
				memcpy(msg[i+1].buf, &ibuf[1], msg[i+1].len);
				i++;
			}
		}
	}
	return i;
}