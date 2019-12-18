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
struct us_data {char* iobuf; int /*<<< orphan*/  send_ctrl_pipe; int /*<<< orphan*/  recv_ctrl_pipe; } ;

/* Variables and functions */
 int HZ ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int usb_stor_control_msg (struct us_data*,int /*<<< orphan*/ ,int,int,int,int,char*,int,int) ; 

__attribute__((used)) static int init_freecom(struct us_data *us)
{
	int result;
	char *buffer = us->iobuf;

	/* The DMA-mapped I/O buffer is 64 bytes long, just right for
	 * all our packets.  No need to allocate any extra buffer space.
	 */

	result = usb_stor_control_msg(us, us->recv_ctrl_pipe,
			0x4c, 0xc0, 0x4346, 0x0, buffer, 0x20, 3*HZ);
	buffer[32] = '\0';
	US_DEBUGP("String returned from FC init is: %s\n", buffer);

	/* Special thanks to the people at Freecom for providing me with
	 * this "magic sequence", which they use in their Windows and MacOS
	 * drivers to make sure that all the attached perhiperals are
	 * properly reset.
	 */

	/* send reset */
	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			0x4d, 0x40, 0x24d8, 0x0, NULL, 0x0, 3*HZ);
	US_DEBUGP("result from activate reset is %d\n", result);

	/* wait 250ms */
	mdelay(250);

	/* clear reset */
	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			0x4d, 0x40, 0x24f8, 0x0, NULL, 0x0, 3*HZ);
	US_DEBUGP("result from clear reset is %d\n", result);

	/* wait 3 seconds */
	mdelay(3 * 1000);

	return USB_STOR_TRANSPORT_GOOD;
}