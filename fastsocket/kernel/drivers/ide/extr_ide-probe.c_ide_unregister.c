#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  major; int /*<<< orphan*/  sg_table; int /*<<< orphan*/  gendev_rel_comp; int /*<<< orphan*/  gendev; int /*<<< orphan*/ * portdev; int /*<<< orphan*/  irq; scalar_t__ present; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int MAX_DRIVES ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PARTN_BITS ; 
 int /*<<< orphan*/  __ide_port_unregister_devices (TYPE_1__*) ; 
 int /*<<< orphan*/  blk_unregister_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ide_cfg_mtx ; 
 int /*<<< orphan*/  ide_proc_unregister_port (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_release_dma_engine (TYPE_1__*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_unregister(ide_hwif_t *hwif)
{
	BUG_ON(in_interrupt());
	BUG_ON(irqs_disabled());

	mutex_lock(&ide_cfg_mtx);

	if (hwif->present) {
		__ide_port_unregister_devices(hwif);
		hwif->present = 0;
	}

	ide_proc_unregister_port(hwif);

	free_irq(hwif->irq, hwif);

	device_unregister(hwif->portdev);
	device_unregister(&hwif->gendev);
	wait_for_completion(&hwif->gendev_rel_comp);

	/*
	 * Remove us from the kernel's knowledge
	 */
	blk_unregister_region(MKDEV(hwif->major, 0), MAX_DRIVES<<PARTN_BITS);
	kfree(hwif->sg_table);
	unregister_blkdev(hwif->major, hwif->name);

	ide_release_dma_engine(hwif);

	mutex_unlock(&ide_cfg_mtx);
}