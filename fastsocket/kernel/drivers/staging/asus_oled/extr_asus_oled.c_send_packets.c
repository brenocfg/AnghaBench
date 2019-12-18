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
typedef  int uint8_t ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct asus_oled_packet {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
#define  ASUS_OLED_FLASH 130 
 size_t ASUS_OLED_PACKET_BUF_SIZE ; 
#define  ASUS_OLED_ROLL 129 
#define  ASUS_OLED_STATIC 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  setup_packet_header (struct asus_oled_packet*,int,int,int,int,int,int,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,struct asus_oled_packet*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int) ; 

__attribute__((used)) static void send_packets(struct usb_device *udev,
			 struct asus_oled_packet *packet,
			 char *buf, uint8_t p_type, size_t p_num)
{
	size_t i;
	int act_len;

	for (i = 0; i < p_num; i++) {
		int retval;

		switch (p_type) {
		case ASUS_OLED_ROLL:
			setup_packet_header(packet, 0x40, 0x80, p_num,
					    i + 1, 0x00, 0x01, 0xff);
			break;
		case ASUS_OLED_STATIC:
			setup_packet_header(packet, 0x10 + i, 0x80, 0x01,
					    0x01, 0x00, 0x01, 0x00);
			break;
		case ASUS_OLED_FLASH:
			setup_packet_header(packet, 0x10 + i, 0x80, 0x01,
					    0x01, 0x00, 0x00, 0xff);
			break;
		}

		memcpy(packet->bitmap, buf + (ASUS_OLED_PACKET_BUF_SIZE*i),
		       ASUS_OLED_PACKET_BUF_SIZE);

		retval = usb_bulk_msg(udev, usb_sndctrlpipe(udev, 2),
				      packet, sizeof(struct asus_oled_packet),
				      &act_len, -1);

		if (retval)
			dev_dbg(&udev->dev, "retval = %d\n", retval);
	}
}