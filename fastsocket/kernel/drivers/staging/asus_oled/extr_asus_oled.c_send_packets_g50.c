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
struct usb_device {int dummy; } ;
struct asus_oled_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  send_packet (struct usb_device*,struct asus_oled_packet*,int,int,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void send_packets_g50(struct usb_device *udev,
			     struct asus_oled_packet *packet, char *buf)
{
	send_packet(udev, packet,     0, 0x100, buf,
		    0x10, 0x00, 0x02, 0x01, 0x00, 0x01);
	send_packet(udev, packet, 0x100, 0x080, buf,
		    0x10, 0x00, 0x02, 0x02, 0x80, 0x00);

	send_packet(udev, packet, 0x180, 0x100, buf,
		    0x11, 0x00, 0x03, 0x01, 0x00, 0x01);
	send_packet(udev, packet, 0x280, 0x100, buf,
		    0x11, 0x00, 0x03, 0x02, 0x00, 0x01);
	send_packet(udev, packet, 0x380, 0x080, buf,
		    0x11, 0x00, 0x03, 0x03, 0x80, 0x00);
}