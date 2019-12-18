#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct via82cxxx_dev {TYPE_1__* via_config; } ;
struct pci_dev {int dummy; } ;
struct ide_timing {int dummy; } ;
struct ide_host {struct via82cxxx_dev* host_priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_11__ {int /*<<< orphan*/  dn; int /*<<< orphan*/  const current_speed; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_9__ {int udma_mask; } ;

/* Variables and functions */
#define  ATA_UDMA2 131 
#define  ATA_UDMA4 130 
#define  ATA_UDMA5 129 
#define  ATA_UDMA6 128 
 int /*<<< orphan*/  IDE_TIMING_8BIT ; 
 TYPE_3__* ide_get_pair_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  ide_timing_compute (TYPE_3__*,int /*<<< orphan*/  const,struct ide_timing*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ide_timing_merge (struct ide_timing*,struct ide_timing*,struct ide_timing*,int /*<<< orphan*/ ) ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int via_clock ; 
 int /*<<< orphan*/  via_set_speed (TYPE_2__*,int /*<<< orphan*/ ,struct ide_timing*) ; 

__attribute__((used)) static void via_set_drive(ide_drive_t *drive, const u8 speed)
{
	ide_hwif_t *hwif = drive->hwif;
	ide_drive_t *peer = ide_get_pair_dev(drive);
	struct pci_dev *dev = to_pci_dev(hwif->dev);
	struct ide_host *host = pci_get_drvdata(dev);
	struct via82cxxx_dev *vdev = host->host_priv;
	struct ide_timing t, p;
	unsigned int T, UT;

	T = 1000000000 / via_clock;

	switch (vdev->via_config->udma_mask) {
	case ATA_UDMA2: UT = T;   break;
	case ATA_UDMA4: UT = T/2; break;
	case ATA_UDMA5: UT = T/3; break;
	case ATA_UDMA6: UT = T/4; break;
	default:	UT = T;
	}

	ide_timing_compute(drive, speed, &t, T, UT);

	if (peer) {
		ide_timing_compute(peer, peer->current_speed, &p, T, UT);
		ide_timing_merge(&p, &t, &t, IDE_TIMING_8BIT);
	}

	via_set_speed(hwif, drive->dn, &t);
}