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
struct lynx_send_data {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  pcl_queue; int /*<<< orphan*/  queue; } ;
struct ti_lynx {int /*<<< orphan*/  id; struct lynx_send_data iso_send; struct lynx_send_data async; } ;
struct hpsb_packet {int data_size; int type; scalar_t__ tcode; int /*<<< orphan*/  driver_list; int /*<<< orphan*/ * header; } ;
struct hpsb_host {struct ti_lynx* hostdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ TCODE_READQ_RESPONSE ; 
 scalar_t__ TCODE_WRITEQ ; 
 int /*<<< orphan*/  cpu_to_be32s (int /*<<< orphan*/ *) ; 
#define  hpsb_async 130 
#define  hpsb_iso 129 
#define  hpsb_raw 128 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_next (struct ti_lynx*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lynx_transmit(struct hpsb_host *host, struct hpsb_packet *packet)
{
        struct ti_lynx *lynx = host->hostdata;
        struct lynx_send_data *d;
        unsigned long flags;

        if (packet->data_size >= 4096) {
                PRINT(KERN_ERR, lynx->id, "transmit packet data too big (%Zd)",
                      packet->data_size);
                return -EOVERFLOW;
        }

        switch (packet->type) {
        case hpsb_async:
        case hpsb_raw:
                d = &lynx->async;
                break;
#if 0 /* has been removed from ieee1394 core */
        case hpsb_iso:
                d = &lynx->iso_send;
                break;
#endif
        default:
                PRINT(KERN_ERR, lynx->id, "invalid packet type %d",
                      packet->type);
                return -EINVAL;
        }

        if (packet->tcode == TCODE_WRITEQ
            || packet->tcode == TCODE_READQ_RESPONSE) {
                cpu_to_be32s(&packet->header[3]);
        }

        spin_lock_irqsave(&d->queue_lock, flags);

	list_add_tail(&packet->driver_list, &d->queue);
	if (list_empty(&d->pcl_queue))
                send_next(lynx, packet->type);

        spin_unlock_irqrestore(&d->queue_lock, flags);

        return 0;
}