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
struct us_data {unsigned char* iobuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int sddr55_bulk_transport (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int sddr55_read_deviceID(struct us_data *us,
		unsigned char *manufacturerID,
		unsigned char *deviceID) {

	int result;
	unsigned char *command = us->iobuf;
	unsigned char *content = us->iobuf;

	memset(command, 0, 8);
	command[5] = 0xB0;
	command[7] = 0x84;
	result = sddr55_bulk_transport(us, DMA_TO_DEVICE, command, 8);

	US_DEBUGP("Result of send_control for device ID is %d\n",
		result);

	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	result = sddr55_bulk_transport(us,
		DMA_FROM_DEVICE, content, 4);

	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	*manufacturerID = content[0];
	*deviceID = content[1];

	if (content[0] != 0xff)	{
    		result = sddr55_bulk_transport(us,
			DMA_FROM_DEVICE, content, 2);
	}

	return USB_STOR_TRANSPORT_GOOD;
}