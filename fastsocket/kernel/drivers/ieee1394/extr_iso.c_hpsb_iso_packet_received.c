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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct hpsb_iso_packet_info {void* sy; void* tag; void* channel; void* cycle; void* total_len; void* len; int /*<<< orphan*/  offset; } ;
struct hpsb_iso {int n_ready_packets; int buf_packets; size_t pkt_dma; int /*<<< orphan*/  lock; struct hpsb_iso_packet_info* infos; int /*<<< orphan*/  bytes_discarded; int /*<<< orphan*/  overflows; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hpsb_iso_packet_received(struct hpsb_iso *iso, u32 offset, u16 len,
			      u16 total_len, u16 cycle, u8 channel, u8 tag,
			      u8 sy)
{
	unsigned long flags;
	spin_lock_irqsave(&iso->lock, flags);

	if (iso->n_ready_packets == iso->buf_packets) {
		/* overflow! */
		atomic_inc(&iso->overflows);
		/* Record size of this discarded packet */
		iso->bytes_discarded += total_len;
	} else {
		struct hpsb_iso_packet_info *info = &iso->infos[iso->pkt_dma];
		info->offset = offset;
		info->len = len;
		info->total_len = total_len;
		info->cycle = cycle;
		info->channel = channel;
		info->tag = tag;
		info->sy = sy;

		iso->pkt_dma = (iso->pkt_dma + 1) % iso->buf_packets;
		iso->n_ready_packets++;
	}

	spin_unlock_irqrestore(&iso->lock, flags);
}