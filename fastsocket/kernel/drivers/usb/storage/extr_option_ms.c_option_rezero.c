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
struct us_data {int /*<<< orphan*/  recv_bulk_pipe; int /*<<< orphan*/  send_bulk_pipe; } ;
typedef  int /*<<< orphan*/  rezero_msg ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RESPONSE_LEN ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_XFER_ERROR ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int option_rezero(struct us_data *us)
{
	const unsigned char rezero_msg[] = {
	  0x55, 0x53, 0x42, 0x43, 0x78, 0x56, 0x34, 0x12,
	  0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x06, 0x01,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	char *buffer;
	int result;

	US_DEBUGP("Option MS: %s", "DEVICE MODE SWITCH\n");

	buffer = kzalloc(RESPONSE_LEN, GFP_KERNEL);
	if (buffer == NULL)
		return USB_STOR_TRANSPORT_ERROR;

	memcpy(buffer, rezero_msg, sizeof(rezero_msg));
	result = usb_stor_bulk_transfer_buf(us,
			us->send_bulk_pipe,
			buffer, sizeof(rezero_msg), NULL);
	if (result != USB_STOR_XFER_GOOD) {
		result = USB_STOR_XFER_ERROR;
		goto out;
	}

	/* Some of the devices need to be asked for a response, but we don't
	 * care what that response is.
	 */
	usb_stor_bulk_transfer_buf(us,
			us->recv_bulk_pipe,
			buffer, RESPONSE_LEN, NULL);

	/* Read the CSW */
	usb_stor_bulk_transfer_buf(us,
			us->recv_bulk_pipe,
			buffer, 13, NULL);

	result = USB_STOR_XFER_GOOD;

out:
	kfree(buffer);
	return result;
}