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
struct lme2510_state {int i2c_talk_onoff; int tuner_config; int signal_lock; int stream_on; int signal_level; int signal_sn; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; struct lme2510_state* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
#define  TUNER_LG 129 
#define  TUNER_S7395 128 
 int /*<<< orphan*/  deb_info (int,char*,int,int) ; 
 int /*<<< orphan*/  lme2510_stream_restart (struct dvb_usb_device*) ; 
 int lme2510_usb_talk (struct dvb_usb_device*,int*,int,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lme2510_msg(struct dvb_usb_device *d,
		u8 *wbuf, int wlen, u8 *rbuf, int rlen)
{
	int ret = 0;
	struct lme2510_state *st = d->priv;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
			return -EAGAIN;

	if (st->i2c_talk_onoff == 1) {

		ret = lme2510_usb_talk(d, wbuf, wlen, rbuf, rlen);

		switch (st->tuner_config) {
		case TUNER_LG:
			if (wbuf[2] == 0x1c) {
				if (wbuf[3] == 0x0e) {
					st->signal_lock = rbuf[1];
					if ((st->stream_on & 1) &&
						(st->signal_lock & 0x10)) {
						lme2510_stream_restart(d);
						st->i2c_talk_onoff = 0;
					}
					msleep(80);
				}
			}
			break;
		case TUNER_S7395:
			if (wbuf[2] == 0xd0) {
				if (wbuf[3] == 0x24) {
					st->signal_lock = rbuf[1];
					if ((st->stream_on & 1) &&
						(st->signal_lock & 0x8)) {
						lme2510_stream_restart(d);
						st->i2c_talk_onoff = 0;
					}
				}
				if ((wbuf[3] != 0x6) & (wbuf[3] != 0x5))
					msleep(5);
			}
			break;
		default:
			break;
		}
	} else {
		switch (st->tuner_config) {
		case TUNER_LG:
			switch (wbuf[3]) {
			case 0x0e:
				rbuf[0] = 0x55;
				rbuf[1] = st->signal_lock;
				break;
			case 0x43:
				rbuf[0] = 0x55;
				rbuf[1] = st->signal_level;
				break;
			case 0x1c:
				rbuf[0] = 0x55;
				rbuf[1] = st->signal_sn;
				break;
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
				rbuf[0] = 0x55;
				rbuf[1] = 0x00;
				break;
			default:
				lme2510_usb_talk(d, wbuf, wlen, rbuf, rlen);
				st->i2c_talk_onoff = 1;
				break;
			}
			break;
		case TUNER_S7395:
			switch (wbuf[3]) {
			case 0x10:
				rbuf[0] = 0x55;
				rbuf[1] = (st->signal_level & 0x80)
						? 0 : (st->signal_level * 2);
				break;
			case 0x2d:
				rbuf[0] = 0x55;
				rbuf[1] = st->signal_sn;
				break;
			case 0x24:
				rbuf[0] = 0x55;
				rbuf[1] = st->signal_lock;
				break;
			case 0x2e:
			case 0x26:
			case 0x27:
				rbuf[0] = 0x55;
				rbuf[1] = 0x00;
				break;
			default:
				lme2510_usb_talk(d, wbuf, wlen, rbuf, rlen);
				st->i2c_talk_onoff = 1;
				break;
			}
			break;
		default:
			break;
		}

		deb_info(4, "I2C From Interupt Message out(%02x) in(%02x)",
				wbuf[3], rbuf[1]);

	}

	mutex_unlock(&d->i2c_mutex);

	return ret;
}