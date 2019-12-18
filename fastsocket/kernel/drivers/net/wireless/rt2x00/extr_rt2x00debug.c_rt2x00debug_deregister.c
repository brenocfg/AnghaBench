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
struct TYPE_4__ {struct rt2x00debug_intf* data; } ;
struct TYPE_3__ {struct rt2x00debug_intf* data; } ;
struct rt2x00debug_intf {TYPE_2__ driver_blob; TYPE_1__ chipset_blob; int /*<<< orphan*/  driver_folder; int /*<<< orphan*/  driver_entry; int /*<<< orphan*/  chipset_entry; int /*<<< orphan*/  cap_flags; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  register_folder; int /*<<< orphan*/  csr_off_entry; int /*<<< orphan*/  csr_val_entry; int /*<<< orphan*/  eeprom_off_entry; int /*<<< orphan*/  eeprom_val_entry; int /*<<< orphan*/  bbp_off_entry; int /*<<< orphan*/  bbp_val_entry; int /*<<< orphan*/  rf_off_entry; int /*<<< orphan*/  rf_val_entry; int /*<<< orphan*/  rfcsr_off_entry; int /*<<< orphan*/  rfcsr_val_entry; int /*<<< orphan*/  queue_folder; int /*<<< orphan*/  queue_frame_dump_entry; int /*<<< orphan*/  queue_stats_entry; int /*<<< orphan*/  crypto_stats_entry; int /*<<< orphan*/  frame_dump_skbqueue; } ;
struct rt2x00_dev {struct rt2x00debug_intf* debugfs_intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rt2x00debug_intf*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void rt2x00debug_deregister(struct rt2x00_dev *rt2x00dev)
{
	struct rt2x00debug_intf *intf = rt2x00dev->debugfs_intf;

	if (unlikely(!intf))
		return;

	skb_queue_purge(&intf->frame_dump_skbqueue);

#ifdef CONFIG_RT2X00_LIB_CRYPTO
	debugfs_remove(intf->crypto_stats_entry);
#endif
	debugfs_remove(intf->queue_stats_entry);
	debugfs_remove(intf->queue_frame_dump_entry);
	debugfs_remove(intf->queue_folder);
	debugfs_remove(intf->rfcsr_val_entry);
	debugfs_remove(intf->rfcsr_off_entry);
	debugfs_remove(intf->rf_val_entry);
	debugfs_remove(intf->rf_off_entry);
	debugfs_remove(intf->bbp_val_entry);
	debugfs_remove(intf->bbp_off_entry);
	debugfs_remove(intf->eeprom_val_entry);
	debugfs_remove(intf->eeprom_off_entry);
	debugfs_remove(intf->csr_val_entry);
	debugfs_remove(intf->csr_off_entry);
	debugfs_remove(intf->register_folder);
	debugfs_remove(intf->dev_flags);
	debugfs_remove(intf->cap_flags);
	debugfs_remove(intf->chipset_entry);
	debugfs_remove(intf->driver_entry);
	debugfs_remove(intf->driver_folder);
	kfree(intf->chipset_blob.data);
	kfree(intf->driver_blob.data);
	kfree(intf);

	rt2x00dev->debugfs_intf = NULL;
}