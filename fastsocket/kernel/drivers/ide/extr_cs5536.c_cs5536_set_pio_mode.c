#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_11__ {int dn; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST ; 
 int IDE_CAST_CMD_MASK ; 
 int IDE_CAST_CMD_SHIFT ; 
 int IDE_CAST_D0_SHIFT ; 
 int IDE_CAST_D1_SHIFT ; 
 int IDE_CAST_DRV_MASK ; 
 int IDE_DRV_MASK ; 
 int /*<<< orphan*/  cs5536_program_dtc (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  cs5536_read (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cs5536_write (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ide_get_best_pio_mode (TYPE_2__*,int,int) ; 
 scalar_t__ ide_get_drivedata (TYPE_2__*) ; 
 TYPE_2__* ide_get_pair_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_set_drivedata (TYPE_2__*,void*) ; 
 int min (int const,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs5536_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	static const u8 drv_timings[5] = {
		0x98, 0x55, 0x32, 0x21, 0x20,
	};

	static const u8 addr_timings[5] = {
		0x2, 0x1, 0x0, 0x0, 0x0,
	};

	static const u8 cmd_timings[5] = {
		0x99, 0x92, 0x90, 0x22, 0x20,
	};

	struct pci_dev *pdev = to_pci_dev(drive->hwif->dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	int cshift = (drive->dn & 1) ? IDE_CAST_D1_SHIFT : IDE_CAST_D0_SHIFT;
	unsigned long timings = (unsigned long)ide_get_drivedata(drive);
	u32 cast;
	u8 cmd_pio = pio;

	if (pair)
		cmd_pio = min(pio, ide_get_best_pio_mode(pair, 255, 4));

	timings &= (IDE_DRV_MASK << 8);
	timings |= drv_timings[pio];
	ide_set_drivedata(drive, (void *)timings);

	cs5536_program_dtc(drive, drv_timings[pio]);

	cs5536_read(pdev, CAST, &cast);

	cast &= ~(IDE_CAST_DRV_MASK << cshift);
	cast |= addr_timings[pio] << cshift;

	cast &= ~(IDE_CAST_CMD_MASK << IDE_CAST_CMD_SHIFT);
	cast |= cmd_timings[cmd_pio] << IDE_CAST_CMD_SHIFT;

	cs5536_write(pdev, CAST, cast);
}