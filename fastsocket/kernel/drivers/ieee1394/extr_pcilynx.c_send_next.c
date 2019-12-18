#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ti_pcl {TYPE_2__* buffer; scalar_t__ pcl_status; void* async_error_next; void* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct lynx_send_data {int /*<<< orphan*/  channel; int /*<<< orphan*/  pcl_start; int /*<<< orphan*/  pcl; void* data_dma; void* header_dma; int /*<<< orphan*/  pcl_queue; TYPE_1__ queue; } ;
struct ti_lynx {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; struct lynx_send_data async; struct lynx_send_data iso_send; } ;
struct hpsb_packet {int header_size; int data_size; int speed_code; int type; int /*<<< orphan*/  data; int /*<<< orphan*/  header; int /*<<< orphan*/  driver_list; } ;
struct TYPE_4__ {int control; void* pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int PCL_BIGENDIAN ; 
 int PCL_CMD_UNFXMT ; 
 int PCL_CMD_XMT ; 
 int PCL_ISOMODE ; 
 int PCL_LAST_BUFF ; 
 void* PCL_NEXT_INVALID ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct hpsb_packet* driver_packet (int /*<<< orphan*/ ) ; 
#define  hpsb_async 130 
#define  hpsb_iso 129 
#define  hpsb_raw 128 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pcl (struct ti_lynx*,int /*<<< orphan*/ ,struct ti_pcl*) ; 
 int /*<<< orphan*/  run_pcl (struct ti_lynx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_next(struct ti_lynx *lynx, int what)
{
        struct ti_pcl pcl;
        struct lynx_send_data *d;
        struct hpsb_packet *packet;

#if 0 /* has been removed from ieee1394 core */
        d = (what == hpsb_iso ? &lynx->iso_send : &lynx->async);
#else
	d = &lynx->async;
#endif
        if (!list_empty(&d->pcl_queue)) {
                PRINT(KERN_ERR, lynx->id, "trying to queue a new packet in nonempty fifo");
                BUG();
        }

        packet = driver_packet(d->queue.next);
	list_move_tail(&packet->driver_list, &d->pcl_queue);

        d->header_dma = pci_map_single(lynx->dev, packet->header,
                                       packet->header_size, PCI_DMA_TODEVICE);
        if (packet->data_size) {
                d->data_dma = pci_map_single(lynx->dev, packet->data,
                                             packet->data_size,
                                             PCI_DMA_TODEVICE);
        } else {
                d->data_dma = 0;
        }

        pcl.next = PCL_NEXT_INVALID;
        pcl.async_error_next = PCL_NEXT_INVALID;
        pcl.pcl_status = 0;
        pcl.buffer[0].control = packet->speed_code << 14 | packet->header_size;
#ifndef __BIG_ENDIAN
        pcl.buffer[0].control |= PCL_BIGENDIAN;
#endif
        pcl.buffer[0].pointer = d->header_dma;
        pcl.buffer[1].control = PCL_LAST_BUFF | packet->data_size;
        pcl.buffer[1].pointer = d->data_dma;

        switch (packet->type) {
        case hpsb_async:
                pcl.buffer[0].control |= PCL_CMD_XMT;
                break;
#if 0 /* has been removed from ieee1394 core */
        case hpsb_iso:
                pcl.buffer[0].control |= PCL_CMD_XMT | PCL_ISOMODE;
                break;
#endif
        case hpsb_raw:
                pcl.buffer[0].control |= PCL_CMD_UNFXMT;
                break;
        }

        put_pcl(lynx, d->pcl, &pcl);
        run_pcl(lynx, d->pcl_start, d->channel);
}