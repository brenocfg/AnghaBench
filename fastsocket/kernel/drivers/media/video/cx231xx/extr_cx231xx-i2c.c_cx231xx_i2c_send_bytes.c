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
struct i2c_msg {int addr; int len; int* buf; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {struct cx231xx_i2c* algo_data; } ;
struct cx231xx_i2c_xfer_data {int dev_addr; int saddr_len; int saddr_dat; int buf_size; int* p_buffer; int /*<<< orphan*/  direction; } ;
struct cx231xx_i2c {int nr; int i2c_nostop; int i2c_reserve; struct cx231xx* dev; } ;
struct cx231xx {scalar_t__ tuner_type; int xc_fw_load_done; int (* cx231xx_gpio_i2c_write ) (struct cx231xx*,int,int*,int) ;int (* cx231xx_send_usb_command ) (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ;} ;

/* Variables and functions */
 scalar_t__ TUNER_XC5000 ; 
 int /*<<< orphan*/  dprintk1 (int,char*,int,int,int) ; 
 int stub1 (struct cx231xx*,int,int*,int) ; 
 int stub2 (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ; 
 int stub3 (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ; 

int cx231xx_i2c_send_bytes(struct i2c_adapter *i2c_adap,
			   const struct i2c_msg *msg)
{
	struct cx231xx_i2c *bus = i2c_adap->algo_data;
	struct cx231xx *dev = bus->dev;
	struct cx231xx_i2c_xfer_data req_data;
	int status = 0;
	u16 size = 0;
	u8 loop = 0;
	u8 saddr_len = 1;
	u8 *buf_ptr = NULL;
	u16 saddr = 0;
	u8 need_gpio = 0;

	if ((bus->nr == 1) && (msg->addr == 0x61)
	    && (dev->tuner_type == TUNER_XC5000)) {

		size = msg->len;

		if (size == 2) {	/* register write sub addr */
			/* Just writing sub address will cause problem
			* to XC5000. So ignore the request */
			return 0;
		} else if (size == 4) {	/* register write with sub addr */
			if (msg->len >= 2)
				saddr = msg->buf[0] << 8 | msg->buf[1];
			else if (msg->len == 1)
				saddr = msg->buf[0];

			switch (saddr) {
			case 0x0000:	/* start tuner calibration mode */
				need_gpio = 1;
				/* FW Loading is done */
				dev->xc_fw_load_done = 1;
				break;
			case 0x000D:	/* Set signal source */
			case 0x0001:	/* Set TV standard - Video */
			case 0x0002:	/* Set TV standard - Audio */
			case 0x0003:	/* Set RF Frequency */
				need_gpio = 1;
				break;
			default:
				if (dev->xc_fw_load_done)
					need_gpio = 1;
				break;
			}

			if (need_gpio) {
				dprintk1(1,
				"GPIO WRITE: addr 0x%x, len %d, saddr 0x%x\n",
				msg->addr, msg->len, saddr);

				return dev->cx231xx_gpio_i2c_write(dev,
								   msg->addr,
								   msg->buf,
								   msg->len);
			}
		}

		/* special case for Xc5000 tuner case */
		saddr_len = 1;

		/* adjust the length to correct length */
		size -= saddr_len;
		buf_ptr = (u8 *) (msg->buf + 1);

		do {
			/* prepare xfer_data struct */
			req_data.dev_addr = msg->addr;
			req_data.direction = msg->flags;
			req_data.saddr_len = saddr_len;
			req_data.saddr_dat = msg->buf[0];
			req_data.buf_size = size > 16 ? 16 : size;
			req_data.p_buffer = (u8 *) (buf_ptr + loop * 16);

			bus->i2c_nostop = (size > 16) ? 1 : 0;
			bus->i2c_reserve = (loop == 0) ? 0 : 1;

			/* usb send command */
			status = dev->cx231xx_send_usb_command(bus, &req_data);
			loop++;

			if (size >= 16)
				size -= 16;
			else
				size = 0;

		} while (size > 0);

		bus->i2c_nostop = 0;
		bus->i2c_reserve = 0;

	} else {		/* regular case */

		/* prepare xfer_data struct */
		req_data.dev_addr = msg->addr;
		req_data.direction = msg->flags;
		req_data.saddr_len = 0;
		req_data.saddr_dat = 0;
		req_data.buf_size = msg->len;
		req_data.p_buffer = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &req_data);
	}

	return status < 0 ? status : 0;
}