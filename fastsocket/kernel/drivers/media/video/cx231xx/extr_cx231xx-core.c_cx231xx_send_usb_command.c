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
struct cx231xx_i2c_xfer_data {int saddr_len; int dev_addr; int direction; int saddr_dat; int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  buf_size; } ;
struct cx231xx_i2c {int i2c_period; int i2c_nostop; int i2c_reserve; scalar_t__ nr; struct cx231xx* dev; } ;
struct cx231xx {int dummy; } ;
struct VENDOR_REQUEST_IN {int wValue; int wIndex; int /*<<< orphan*/  pBuff; int /*<<< orphan*/  direction; int /*<<< orphan*/  wLength; scalar_t__ bData; scalar_t__ bRequest; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int I2C_SYNC ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  cx231xx_info (char*,int) ; 
 int cx231xx_send_vendor_cmd (struct cx231xx*,struct VENDOR_REQUEST_IN*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int cx231xx_send_usb_command(struct cx231xx_i2c *i2c_bus,
			     struct cx231xx_i2c_xfer_data *req_data)
{
	int status = 0;
	struct cx231xx *dev = i2c_bus->dev;
	struct VENDOR_REQUEST_IN ven_req;

	u8 saddr_len = 0;
	u8 _i2c_period = 0;
	u8 _i2c_nostop = 0;
	u8 _i2c_reserve = 0;

	/* Get the I2C period, nostop and reserve parameters */
	_i2c_period = i2c_bus->i2c_period;
	_i2c_nostop = i2c_bus->i2c_nostop;
	_i2c_reserve = i2c_bus->i2c_reserve;

	saddr_len = req_data->saddr_len;

	/* Set wValue */
	if (saddr_len == 1)	/* need check saddr_len == 0  */
		ven_req.wValue =
		    req_data->
		    dev_addr << 9 | _i2c_period << 4 | saddr_len << 2 |
		    _i2c_nostop << 1 | I2C_SYNC | _i2c_reserve << 6;
	else
		ven_req.wValue =
		    req_data->
		    dev_addr << 9 | _i2c_period << 4 | saddr_len << 2 |
		    _i2c_nostop << 1 | I2C_SYNC | _i2c_reserve << 6;

	/* set channel number */
	if (req_data->direction & I2C_M_RD) {
		/* channel number, for read,spec required channel_num +4 */
		ven_req.bRequest = i2c_bus->nr + 4;
	} else
		ven_req.bRequest = i2c_bus->nr;	/* channel number,  */

	/* set index value */
	switch (saddr_len) {
	case 0:
		ven_req.wIndex = 0;	/* need check */
		break;
	case 1:
		ven_req.wIndex = (req_data->saddr_dat & 0xff);
		break;
	case 2:
		ven_req.wIndex = req_data->saddr_dat;
		break;
	}

	/* set wLength value */
	ven_req.wLength = req_data->buf_size;

	/* set bData value */
	ven_req.bData = 0;

	/* set the direction */
	if (req_data->direction) {
		ven_req.direction = USB_DIR_IN;
		memset(req_data->p_buffer, 0x00, ven_req.wLength);
	} else
		ven_req.direction = USB_DIR_OUT;

	/* set the buffer for read / write */
	ven_req.pBuff = req_data->p_buffer;


	/* call common vendor command request */
	status = cx231xx_send_vendor_cmd(dev, &ven_req);
	if (status < 0) {
		cx231xx_info
		    ("UsbInterface::sendCommand, failed with status -%d\n",
		     status);
	}

	return status;
}