#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct legacy_data {int* clock; scalar_t__ timing; scalar_t__ fast; } ;
struct ata_timing {int /*<<< orphan*/  recover; int /*<<< orphan*/  active; } ;
struct ata_port {TYPE_1__* host; } ;
struct ata_device {size_t devno; scalar_t__ class; int /*<<< orphan*/  pio_mode; } ;
struct TYPE_2__ {struct legacy_data* private_data; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,int /*<<< orphan*/ ,struct ata_timing*,int,int) ; 
 int clamp_val (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void qdi6580_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct ata_timing t;
	struct legacy_data *ld_qdi = ap->host->private_data;
	int active, recovery;
	u8 timing;

	/* Get the timing data in cycles */
	ata_timing_compute(adev, adev->pio_mode, &t, 30303, 1000);

	if (ld_qdi->fast) {
		active = 8 - clamp_val(t.active, 1, 8);
		recovery = 18 - clamp_val(t.recover, 3, 18);
	} else {
		active = 9 - clamp_val(t.active, 2, 9);
		recovery = 15 - clamp_val(t.recover, 0, 15);
	}
	timing = (recovery << 4) | active | 0x08;
	ld_qdi->clock[adev->devno] = timing;
	outb(timing, ld_qdi->timing + 2 * adev->devno);
	/* Clear the FIFO */
	if (adev->class != ATA_DEV_ATA)
		outb(0x5F, ld_qdi->timing + 3);
}