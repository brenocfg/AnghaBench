#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct asus_oled_packet {int* bitmap; } ;
struct asus_oled_header {int dummy; } ;
struct asus_oled_dev {scalar_t__ enabled; TYPE_1__* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct asus_oled_packet*) ; 
 struct asus_oled_packet* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_packet_header (struct asus_oled_packet*,int,int,int,int,int,int,int) ; 
 int usb_bulk_msg (TYPE_1__*,int /*<<< orphan*/ ,struct asus_oled_packet*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int) ; 

__attribute__((used)) static void enable_oled(struct asus_oled_dev *odev, uint8_t enabl)
{
	int a;
	int retval;
	int act_len;
	struct asus_oled_packet *packet;

	packet = kzalloc(sizeof(struct asus_oled_packet), GFP_KERNEL);

	if (!packet) {
		dev_err(&odev->udev->dev, "out of memory\n");
		return;
	}

	setup_packet_header(packet, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00);

	if (enabl)
		packet->bitmap[0] = 0xaf;
	else
		packet->bitmap[0] = 0xae;

	for (a = 0; a < 1; a++) {
		retval = usb_bulk_msg(odev->udev,
			usb_sndbulkpipe(odev->udev, 2),
			packet,
			sizeof(struct asus_oled_header) + 1,
			&act_len,
			-1);

		if (retval)
			dev_dbg(&odev->udev->dev, "retval = %d\n", retval);
	}

	odev->enabled = enabl;

	kfree(packet);
}