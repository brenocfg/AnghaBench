#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  regbase; scalar_t__ mediabay; } ;
typedef  TYPE_2__ pmac_ide_hwif_t ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_1__ gendev; } ;
typedef  TYPE_3__ ide_hwif_t ;
struct TYPE_9__ {int /*<<< orphan*/  dev_flags; TYPE_3__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_DFLAG_NOPROBE ; 
 int /*<<< orphan*/  MB_CD ; 
 scalar_t__ check_media_bay_by_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmac_ide_init_dev(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	pmac_ide_hwif_t *pmif =
		(pmac_ide_hwif_t *)dev_get_drvdata(hwif->gendev.parent);

	if (pmif->mediabay) {
#ifdef CONFIG_PMAC_MEDIABAY
		if (check_media_bay_by_base(pmif->regbase, MB_CD) == 0) {
			drive->dev_flags &= ~IDE_DFLAG_NOPROBE;
			return;
		}
#endif
		drive->dev_flags |= IDE_DFLAG_NOPROBE;
	}
}