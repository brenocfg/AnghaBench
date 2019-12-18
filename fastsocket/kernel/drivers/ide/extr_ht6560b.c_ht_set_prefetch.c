#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int HT_PREFETCH_MODE ; 
 int /*<<< orphan*/  IDE_DFLAG_NO_UNMASK ; 
 int /*<<< orphan*/  IDE_DFLAG_UNMASK ; 
 int /*<<< orphan*/  ht6560b_lock ; 
 scalar_t__ ide_get_drivedata (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_set_drivedata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ht_set_prefetch(ide_drive_t *drive, u8 state)
{
	unsigned long flags, config;
	int t = HT_PREFETCH_MODE << 8;

	spin_lock_irqsave(&ht6560b_lock, flags);

	config = (unsigned long)ide_get_drivedata(drive);

	/*
	 *  Prefetch mode and unmask irq seems to conflict
	 */
	if (state) {
		config |= t;   /* enable prefetch mode */
		drive->dev_flags |= IDE_DFLAG_NO_UNMASK;
		drive->dev_flags &= ~IDE_DFLAG_UNMASK;
	} else {
		config &= ~t;  /* disable prefetch mode */
		drive->dev_flags &= ~IDE_DFLAG_NO_UNMASK;
	}

	ide_set_drivedata(drive, (void *)config);

	spin_unlock_irqrestore(&ht6560b_lock, flags);

#ifdef DEBUG
	printk("ht6560b: drive %s prefetch mode %sabled\n", drive->name, (state ? "en" : "dis"));
#endif
}