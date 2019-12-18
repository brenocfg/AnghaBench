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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct ide_timing {int udma; } ;
struct TYPE_7__ {scalar_t__ ultra_mask; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {scalar_t__ const current_speed; int /*<<< orphan*/  dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_UDMA2 ; 
 int /*<<< orphan*/  IDE_TIMING_8BIT ; 
 scalar_t__ const XFER_UDMA_5 ; 
 scalar_t__ const XFER_UDMA_6 ; 
 int amd_clock ; 
 int /*<<< orphan*/  amd_set_speed (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,struct ide_timing*) ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_timing_compute (TYPE_2__*,scalar_t__ const,struct ide_timing*,int,int) ; 
 int /*<<< orphan*/  ide_timing_merge (struct ide_timing*,struct ide_timing*,struct ide_timing*,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd_set_drive(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif = drive->hwif;
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	ide_drive_t *peer = ide_get_pair_dev(drive);
	struct ide_timing t, p;
	int T, UT;
	u8 udma_mask = hwif->ultra_mask;

	T = 1000000000 / amd_clock;
	UT = (udma_mask == ATA_UDMA2) ? T : (T / 2);

	ide_timing_compute(drive, speed, &t, T, UT);

	if (peer) {
		ide_timing_compute(peer, peer->current_speed, &p, T, UT);
		ide_timing_merge(&p, &t, &t, IDE_TIMING_8BIT);
	}

	if (speed == XFER_UDMA_5 && amd_clock <= 33333) t.udma = 1;
	if (speed == XFER_UDMA_6 && amd_clock <= 33333) t.udma = 15;

	amd_set_speed(dev, drive->dn, udma_mask, &t);
}