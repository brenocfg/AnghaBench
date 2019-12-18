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
struct cx231xx_i2c {int nr; struct cx231xx* dev; } ;
struct cx231xx {scalar_t__ tuner_type; int (* cx231xx_gpio_i2c_write ) (struct cx231xx*,int,int*,int) ;int (* cx231xx_gpio_i2c_read ) (struct cx231xx*,int,int*,int) ;int (* cx231xx_send_usb_command ) (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ;scalar_t__ xc_fw_load_done; } ;

/* Variables and functions */
 scalar_t__ TUNER_XC5000 ; 
 int /*<<< orphan*/  dprintk1 (int,char*,...) ; 
 int stub1 (struct cx231xx*,int,int*,int) ; 
 int stub2 (struct cx231xx*,int,int*,int) ; 
 int stub3 (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ; 
 int stub4 (struct cx231xx_i2c*,struct cx231xx_i2c_xfer_data*) ; 

__attribute__((used)) static int cx231xx_i2c_recv_bytes(struct i2c_adapter *i2c_adap,
				  const struct i2c_msg *msg)
{
	struct cx231xx_i2c *bus = i2c_adap->algo_data;
	struct cx231xx *dev = bus->dev;
	struct cx231xx_i2c_xfer_data req_data;
	int status = 0;
	u16 saddr = 0;
	u8 need_gpio = 0;

	if ((bus->nr == 1) && (msg->addr == 0x61)
	    && dev->tuner_type == TUNER_XC5000) {

		if (msg->len == 2)
			saddr = msg->buf[0] << 8 | msg->buf[1];
		else if (msg->len == 1)
			saddr = msg->buf[0];

		if (dev->xc_fw_load_done) {

			switch (saddr) {
			case 0x0009:	/* BUSY check */
				dprintk1(1,
				"GPIO R E A D: Special case BUSY check \n");
				/*Try read BUSY register, just set it to zero*/
				msg->buf[0] = 0;
				if (msg->len == 2)
					msg->buf[1] = 0;
				return 0;
			case 0x0004:	/* read Lock status */
				need_gpio = 1;
				break;

			}

			if (need_gpio) {
				/* this is a special case to handle Xceive tuner
				clock stretch issue with gpio based I2C */

				dprintk1(1,
				"GPIO R E A D: addr 0x%x, len %d, saddr 0x%x\n",
				msg->addr, msg->len,
				msg->buf[0] << 8 | msg->buf[1]);

				status =
				    dev->cx231xx_gpio_i2c_write(dev, msg->addr,
								msg->buf,
								msg->len);
				status =
				    dev->cx231xx_gpio_i2c_read(dev, msg->addr,
							       msg->buf,
							       msg->len);
				return status;
			}
		}

		/* prepare xfer_data struct */
		req_data.dev_addr = msg->addr;
		req_data.direction = msg->flags;
		req_data.saddr_len = msg->len;
		req_data.saddr_dat = msg->buf[0] << 8 | msg->buf[1];
		req_data.buf_size = msg->len;
		req_data.p_buffer = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &req_data);

	} else {

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