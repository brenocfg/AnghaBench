#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct timeval {int tv_sec; int tv_usec; } ;
struct skb_frame_desc {int flags; int desc_len; int /*<<< orphan*/  desc; TYPE_3__* entry; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct rt2x00dump_hdr {void* timestamp_usec; void* timestamp_sec; int /*<<< orphan*/  entry_index; int /*<<< orphan*/  queue_index; void* type; void* chip_rev; void* chip_rf; void* chip_rt; void* data_length; void* desc_length; void* header_length; void* version; } ;
struct rt2x00debug_intf {int /*<<< orphan*/  frame_dump_skbqueue; int /*<<< orphan*/  frame_dump_flags; int /*<<< orphan*/  frame_dump_waitqueue; } ;
struct TYPE_4__ {int rt; int rf; int rev; } ;
struct rt2x00_dev {TYPE_1__ chip; struct rt2x00debug_intf* debugfs_intf; } ;
typedef  enum rt2x00_dump_type { ____Placeholder_rt2x00_dump_type } rt2x00_dump_type ;
struct TYPE_6__ {int /*<<< orphan*/  entry_idx; TYPE_2__* queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int DUMP_HEADER_VERSION ; 
 int /*<<< orphan*/  FRAME_DUMP_FILE_OPEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SKBDESC_DESC_IN_SKB ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 struct skb_frame_desc* get_skb_frame_desc (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00_dbg (struct rt2x00_dev*,char*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void rt2x00debug_dump_frame(struct rt2x00_dev *rt2x00dev,
			    enum rt2x00_dump_type type, struct sk_buff *skb)
{
	struct rt2x00debug_intf *intf = rt2x00dev->debugfs_intf;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(skb);
	struct sk_buff *skbcopy;
	struct rt2x00dump_hdr *dump_hdr;
	struct timeval timestamp;
	u32 data_len;

	if (likely(!test_bit(FRAME_DUMP_FILE_OPEN, &intf->frame_dump_flags)))
		return;

	do_gettimeofday(&timestamp);

	if (skb_queue_len(&intf->frame_dump_skbqueue) > 20) {
		rt2x00_dbg(rt2x00dev, "txrx dump queue length exceeded\n");
		return;
	}

	data_len = skb->len;
	if (skbdesc->flags & SKBDESC_DESC_IN_SKB)
		data_len -= skbdesc->desc_len;

	skbcopy = alloc_skb(sizeof(*dump_hdr) + skbdesc->desc_len + data_len,
			    GFP_ATOMIC);
	if (!skbcopy) {
		rt2x00_dbg(rt2x00dev, "Failed to copy skb for dump\n");
		return;
	}

	dump_hdr = (struct rt2x00dump_hdr *)skb_put(skbcopy, sizeof(*dump_hdr));
	dump_hdr->version = cpu_to_le32(DUMP_HEADER_VERSION);
	dump_hdr->header_length = cpu_to_le32(sizeof(*dump_hdr));
	dump_hdr->desc_length = cpu_to_le32(skbdesc->desc_len);
	dump_hdr->data_length = cpu_to_le32(data_len);
	dump_hdr->chip_rt = cpu_to_le16(rt2x00dev->chip.rt);
	dump_hdr->chip_rf = cpu_to_le16(rt2x00dev->chip.rf);
	dump_hdr->chip_rev = cpu_to_le16(rt2x00dev->chip.rev);
	dump_hdr->type = cpu_to_le16(type);
	dump_hdr->queue_index = skbdesc->entry->queue->qid;
	dump_hdr->entry_index = skbdesc->entry->entry_idx;
	dump_hdr->timestamp_sec = cpu_to_le32(timestamp.tv_sec);
	dump_hdr->timestamp_usec = cpu_to_le32(timestamp.tv_usec);

	if (!(skbdesc->flags & SKBDESC_DESC_IN_SKB))
		memcpy(skb_put(skbcopy, skbdesc->desc_len), skbdesc->desc,
		       skbdesc->desc_len);
	memcpy(skb_put(skbcopy, skb->len), skb->data, skb->len);

	skb_queue_tail(&intf->frame_dump_skbqueue, skbcopy);
	wake_up_interruptible(&intf->frame_dump_waitqueue);

	/*
	 * Verify that the file has not been closed while we were working.
	 */
	if (!test_bit(FRAME_DUMP_FILE_OPEN, &intf->frame_dump_flags))
		skb_queue_purge(&intf->frame_dump_skbqueue);
}