#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct txentry_desc {int dummy; } ;
struct skb_frame_desc {int desc_len; int /*<<< orphan*/  desc; int /*<<< orphan*/  flags; } ;
struct rt2x00_dev {int dummy; } ;
struct queue_entry {TYPE_2__* skb; int /*<<< orphan*/  entry_idx; TYPE_1__* queue; } ;
struct TYPE_8__ {unsigned int len; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int winfo_size; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCN_TIME_CFG ; 
 int /*<<< orphan*/  BCN_TIME_CFG_BEACON_GEN ; 
 int /*<<< orphan*/  DUMP_FRAME_BEACON ; 
 unsigned int HW_BEACON_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKBDESC_DESC_IN_SKB ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 struct skb_frame_desc* get_skb_frame_desc (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 unsigned int roundup (unsigned int,int) ; 
 int /*<<< orphan*/  rt2800_register_multiwrite (struct rt2x00_dev*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_write_tx_data (struct queue_entry*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (struct rt2x00_dev*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ skb_pad (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  skb_push (TYPE_2__*,int const) ; 

void rt2800_write_beacon(struct queue_entry *entry, struct txentry_desc *txdesc)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	unsigned int beacon_base;
	unsigned int padding_len;
	u32 orig_reg, reg;
	const int txwi_desc_size = entry->queue->winfo_size;

	/*
	 * Disable beaconing while we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	rt2800_register_read(rt2x00dev, BCN_TIME_CFG, &reg);
	orig_reg = reg;
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 0);
	rt2800_register_write(rt2x00dev, BCN_TIME_CFG, reg);

	/*
	 * Add space for the TXWI in front of the skb.
	 */
	memset(skb_push(entry->skb, txwi_desc_size), 0, txwi_desc_size);

	/*
	 * Register descriptor details in skb frame descriptor.
	 */
	skbdesc->flags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = entry->skb->data;
	skbdesc->desc_len = txwi_desc_size;

	/*
	 * Add the TXWI for the beacon to the skb.
	 */
	rt2800_write_tx_data(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry->skb);

	/*
	 * Write entire beacon with TXWI and padding to register.
	 */
	padding_len = roundup(entry->skb->len, 4) - entry->skb->len;
	if (padding_len && skb_pad(entry->skb, padding_len)) {
		rt2x00_err(rt2x00dev, "Failure padding beacon, aborting\n");
		/* skb freed by skb_pad() on failure */
		entry->skb = NULL;
		rt2800_register_write(rt2x00dev, BCN_TIME_CFG, orig_reg);
		return;
	}

	beacon_base = HW_BEACON_OFFSET(entry->entry_idx);
	rt2800_register_multiwrite(rt2x00dev, beacon_base, entry->skb->data,
				   entry->skb->len + padding_len);

	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_GEN, 1);
	rt2800_register_write(rt2x00dev, BCN_TIME_CFG, reg);

	/*
	 * Clean up beacon skb.
	 */
	dev_kfree_skb_any(entry->skb);
	entry->skb = NULL;
}