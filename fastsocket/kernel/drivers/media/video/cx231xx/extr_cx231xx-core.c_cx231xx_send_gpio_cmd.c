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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  void* u16 ;
struct cx231xx {int dummy; } ;
struct VENDOR_REQUEST_IN {int /*<<< orphan*/  direction; scalar_t__ wLength; scalar_t__* pBuff; scalar_t__ bData; void* wIndex; int /*<<< orphan*/  bRequest; void* wValue; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  VRT_GET_GPIE ; 
 int /*<<< orphan*/  VRT_GET_GPIO ; 
 int /*<<< orphan*/  VRT_SET_GPIE ; 
 int /*<<< orphan*/  VRT_SET_GPIO ; 
 int /*<<< orphan*/  cx231xx_info (char*,int) ; 
 int cx231xx_send_vendor_cmd (struct cx231xx*,struct VENDOR_REQUEST_IN*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,scalar_t__) ; 

int cx231xx_send_gpio_cmd(struct cx231xx *dev, u32 gpio_bit, u8 *gpio_val,
			  u8 len, u8 request, u8 direction)
{
	int status = 0;
	struct VENDOR_REQUEST_IN ven_req;

	/* Set wValue */
	ven_req.wValue = (u16) (gpio_bit >> 16 & 0xffff);

	/* set request */
	if (!request) {
		if (direction)
			ven_req.bRequest = VRT_GET_GPIO;	/* 0x8 gpio */
		else
			ven_req.bRequest = VRT_SET_GPIO;	/* 0x9 gpio */
	} else {
		if (direction)
			ven_req.bRequest = VRT_GET_GPIE;	/* 0xa gpie */
		else
			ven_req.bRequest = VRT_SET_GPIE;	/* 0xb gpie */
	}

	/* set index value */
	ven_req.wIndex = (u16) (gpio_bit & 0xffff);

	/* set wLength value */
	ven_req.wLength = len;

	/* set bData value */
	ven_req.bData = 0;

	/* set the buffer for read / write */
	ven_req.pBuff = gpio_val;

	/* set the direction */
	if (direction) {
		ven_req.direction = USB_DIR_IN;
		memset(ven_req.pBuff, 0x00, ven_req.wLength);
	} else
		ven_req.direction = USB_DIR_OUT;


	/* call common vendor command request */
	status = cx231xx_send_vendor_cmd(dev, &ven_req);
	if (status < 0) {
		cx231xx_info
		    ("UsbInterface::sendCommand, failed with status -%d\n",
		     status);
	}

	return status;
}