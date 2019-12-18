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
typedef  int u32 ;
struct sisusb_usb_data {int dummy; } ;
struct sisusb_packet {int address; int header; int data; } ;

/* Variables and functions */
 int sisusb_send_packet (struct sisusb_usb_data*,int,struct sisusb_packet*) ; 

__attribute__((used)) static int sisusb_read_memio_long(struct sisusb_usb_data *sisusb, int type,
							u32 addr, u32 *data)
{
	struct sisusb_packet packet;
	int ret = 0;

	packet.address = addr & ~3;

	switch (addr & 3) {
		case 0:
			packet.header  = (type << 6) | 0x000f;
			ret = sisusb_send_packet(sisusb, 6, &packet);
			*data = packet.data;
			break;
		case 1:
			packet.header  = (type << 6) | 0x000e;
			ret = sisusb_send_packet(sisusb, 6, &packet);
			*data = packet.data >> 8;
			packet.header  = (type << 6) | 0x0001;
			packet.address = (addr & ~3) + 4;
			ret |= sisusb_send_packet(sisusb, 6, &packet);
			*data |= (packet.data << 24);
			break;
		case 2:
			packet.header  = (type << 6) | 0x000c;
			ret = sisusb_send_packet(sisusb, 6, &packet);
			*data = packet.data >> 16;
			packet.header  = (type << 6) | 0x0003;
			packet.address = (addr & ~3) + 4;
			ret |= sisusb_send_packet(sisusb, 6, &packet);
			*data |= (packet.data << 16);
			break;
		case 3:
			packet.header  = (type << 6) | 0x0008;
			ret = sisusb_send_packet(sisusb, 6, &packet);
			*data = packet.data >> 24;
			packet.header  = (type << 6) | 0x0007;
			packet.address = (addr & ~3) + 4;
			ret |= sisusb_send_packet(sisusb, 6, &packet);
			*data |= (packet.data << 8);
	}

	return ret;
}