#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ kind; } ;
typedef  TYPE_2__ pmac_ide_hwif_t ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct TYPE_10__ {TYPE_1__ gendev; } ;
typedef  TYPE_3__ ide_hwif_t ;
struct TYPE_11__ {TYPE_3__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ controller_k2_ata6 ; 
 scalar_t__ controller_sh_ata6 ; 
 scalar_t__ controller_un_ata6 ; 
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_ide_apply_timings (TYPE_4__*) ; 
 int /*<<< orphan*/  pmac_ide_kauai_apply_timings (TYPE_4__*) ; 

__attribute__((used)) static void
pmac_ide_do_update_timings(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	pmac_ide_hwif_t *pmif =
		(pmac_ide_hwif_t *)dev_get_drvdata(hwif->gendev.parent);

	if (pmif->kind == controller_sh_ata6 ||
	    pmif->kind == controller_un_ata6 ||
	    pmif->kind == controller_k2_ata6)
		pmac_ide_kauai_apply_timings(drive);
	else
		pmac_ide_apply_timings(drive);
}