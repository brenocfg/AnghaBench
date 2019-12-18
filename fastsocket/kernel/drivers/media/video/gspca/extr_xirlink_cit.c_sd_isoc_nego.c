#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_host_interface {TYPE_4__* endpoint; } ;
struct gspca_dev {int width; int /*<<< orphan*/  iface; TYPE_5__* dev; } ;
struct TYPE_10__ {TYPE_2__* config; } ;
struct TYPE_8__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_9__ {TYPE_3__ desc; } ;
struct TYPE_7__ {TYPE_1__** intf_cache; } ;
struct TYPE_6__ {struct usb_host_interface* altsetting; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_set_interface (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_isoc_nego(struct gspca_dev *gspca_dev)
{
	int ret, packet_size, min_packet_size;
	struct usb_host_interface *alt;

	switch (gspca_dev->width) {
	case 160:
		min_packet_size = 200;
		break;
	case 176:
		min_packet_size = 266;
		break;
	default:
		min_packet_size = 400;
		break;
	}

	alt = &gspca_dev->dev->config->intf_cache[0]->altsetting[1];
	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	if (packet_size <= min_packet_size)
		return -EIO;

	packet_size -= 100;
	if (packet_size < min_packet_size)
		packet_size = min_packet_size;
	alt->endpoint[0].desc.wMaxPacketSize = cpu_to_le16(packet_size);

	ret = usb_set_interface(gspca_dev->dev, gspca_dev->iface, 1);
	if (ret < 0)
		err("set alt 1 err %d", ret);

	return ret;
}