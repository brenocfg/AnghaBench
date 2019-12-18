#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct txentry_desc {int dummy; } ;
struct rt2x00_dev {int dummy; } ;
struct queue_entry {int /*<<< orphan*/  skb; TYPE_1__* queue; } ;
struct TYPE_2__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR14 ; 
 int /*<<< orphan*/  CSR14_BEACON_GEN ; 
 int /*<<< orphan*/  DUMP_FRAME_BEACON ; 
 int /*<<< orphan*/  rt2400pci_write_tx_desc (struct queue_entry*,struct txentry_desc*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00debug_dump_frame (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00queue_map_txskb (struct queue_entry*) ; 

__attribute__((used)) static void rt2400pci_write_beacon(struct queue_entry *entry,
				   struct txentry_desc *txdesc)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	u32 reg;

	/*
	 * Disable beaconing while we are reloading the beacon data,
	 * otherwise we might be sending out invalid data.
	 */
	rt2x00mmio_register_read(rt2x00dev, CSR14, &reg);
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 0);
	rt2x00mmio_register_write(rt2x00dev, CSR14, reg);

	if (rt2x00queue_map_txskb(entry)) {
		rt2x00_err(rt2x00dev, "Fail to map beacon, aborting\n");
		goto out;
	}
	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 1);
	/*
	 * Write the TX descriptor for the beacon.
	 */
	rt2400pci_write_tx_desc(entry, txdesc);

	/*
	 * Dump beacon to userspace through debugfs.
	 */
	rt2x00debug_dump_frame(rt2x00dev, DUMP_FRAME_BEACON, entry->skb);
out:
	/*
	 * Enable beaconing again.
	 */
	rt2x00_set_field32(&reg, CSR14_BEACON_GEN, 1);
	rt2x00mmio_register_write(rt2x00dev, CSR14, reg);
}