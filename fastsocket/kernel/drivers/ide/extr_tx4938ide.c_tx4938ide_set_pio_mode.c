#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tx4938ide_platform_info {int /*<<< orphan*/  gbus_clock; int /*<<< orphan*/  ebus_ch; } ;
struct TYPE_9__ {TYPE_1__* dev; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_10__ {TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_8__ {struct tx4938ide_platform_info* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_get_best_pio_mode (TYPE_3__*,int,int) ; 
 TYPE_3__* ide_get_pair_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx4938ide_tune_ebusc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx4938ide_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	ide_hwif_t *hwif = drive->hwif;
	struct tx4938ide_platform_info *pdata = hwif->dev->platform_data;
	u8 safe = pio;
	ide_drive_t *pair;

	pair = ide_get_pair_dev(drive);
	if (pair)
		safe = min(safe, ide_get_best_pio_mode(pair, 255, 5));
	tx4938ide_tune_ebusc(pdata->ebus_ch, pdata->gbus_clock, safe);
}