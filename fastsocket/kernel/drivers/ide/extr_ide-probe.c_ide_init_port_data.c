#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long data; int /*<<< orphan*/ * function; } ;
struct TYPE_5__ {unsigned int index; char* name; int /*<<< orphan*/ * tp_ops; int /*<<< orphan*/  gendev_rel_comp; TYPE_2__ timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  major; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  default_tp_ops ; 
 int /*<<< orphan*/ * ide_hwif_to_major ; 
 int /*<<< orphan*/  ide_port_init_devices_data (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_timer_expiry ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ide_init_port_data(ide_hwif_t *hwif, unsigned int index)
{
	/* fill in any non-zero initial values */
	hwif->index	= index;
	hwif->major	= ide_hwif_to_major[index];

	hwif->name[0]	= 'i';
	hwif->name[1]	= 'd';
	hwif->name[2]	= 'e';
	hwif->name[3]	= '0' + index;

	spin_lock_init(&hwif->lock);

	init_timer(&hwif->timer);
	hwif->timer.function = &ide_timer_expiry;
	hwif->timer.data = (unsigned long)hwif;

	init_completion(&hwif->gendev_rel_comp);

	hwif->tp_ops = &default_tp_ops;

	ide_port_init_devices_data(hwif);
}