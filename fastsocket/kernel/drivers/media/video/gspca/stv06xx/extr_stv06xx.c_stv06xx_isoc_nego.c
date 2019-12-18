#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct usb_host_interface {TYPE_5__* endpoint; } ;
struct sd {TYPE_3__* sensor; } ;
struct gspca_dev {size_t curr_mode; int /*<<< orphan*/  iface; TYPE_6__* dev; } ;
struct TYPE_12__ {TYPE_2__* config; } ;
struct TYPE_10__ {int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_11__ {TYPE_4__ desc; } ;
struct TYPE_9__ {int* min_packet_size; } ;
struct TYPE_8__ {TYPE_1__** intf_cache; } ;
struct TYPE_7__ {struct usb_host_interface* altsetting; } ;

/* Variables and functions */
 int D_ERR ; 
 int D_STREAM ; 
 int EIO ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_set_interface (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv06xx_isoc_nego(struct gspca_dev *gspca_dev)
{
	int ret, packet_size, min_packet_size;
	struct usb_host_interface *alt;
	struct sd *sd = (struct sd *) gspca_dev;

	alt = &gspca_dev->dev->config->intf_cache[0]->altsetting[1];
	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	min_packet_size = sd->sensor->min_packet_size[gspca_dev->curr_mode];
	if (packet_size <= min_packet_size)
		return -EIO;

	packet_size -= 100;
	if (packet_size < min_packet_size)
		packet_size = min_packet_size;
	alt->endpoint[0].desc.wMaxPacketSize = cpu_to_le16(packet_size);

	ret = usb_set_interface(gspca_dev->dev, gspca_dev->iface, 1);
	if (ret < 0)
		PDEBUG(D_ERR|D_STREAM, "set alt 1 err %d", ret);

	return ret;
}