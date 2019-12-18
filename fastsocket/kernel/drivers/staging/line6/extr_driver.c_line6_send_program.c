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
struct usb_line6 {int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  ep_control_write; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 unsigned char LINE6_CHANNEL_HOST ; 
 unsigned char LINE6_PROGRAM_CHANGE ; 
 int LINE6_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_write_hexdump (struct usb_line6*,char,unsigned char*,int) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,unsigned int*,int) ; 
 int /*<<< orphan*/  usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int line6_send_program(struct usb_line6 *line6, int value)
{
	int retval;
	unsigned char *buffer;
	unsigned int partial;

	buffer = kmalloc(2, GFP_KERNEL);

	if (!buffer) {
		dev_err(line6->ifcdev, "out of memory\n");
		return -ENOMEM;
	}

	buffer[0] = LINE6_PROGRAM_CHANGE | LINE6_CHANNEL_HOST;
	buffer[1] = value;

#if DO_DUMP_URB_SEND
	line6_write_hexdump(line6, 'S', buffer, 2);
#endif

	retval = usb_interrupt_msg(line6->usbdev,
				   usb_sndintpipe(line6->usbdev,
						  line6->ep_control_write),
				   buffer, 2, &partial, LINE6_TIMEOUT * HZ);

	if (retval)
		dev_err(line6->ifcdev, "usb_interrupt_msg failed (%d)\n", retval);

	kfree(buffer);
	return retval;
}