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
struct ata_timing {int dummy; } ;
struct ata_port {int /*<<< orphan*/  dev; TYPE_1__* host; } ;
struct ata_device {int /*<<< orphan*/  pio_mode; } ;
struct at32_ide_info {int dummy; } ;
struct TYPE_2__ {struct at32_ide_info* private_data; } ;

/* Variables and functions */
 int ata_timing_compute (struct ata_device*,int /*<<< orphan*/ ,struct ata_timing*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int pata_at32_setup_timing (int /*<<< orphan*/ ,struct at32_ide_info*,struct ata_timing*) ; 

__attribute__((used)) static void pata_at32_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct ata_timing timing;
	struct at32_ide_info *info = ap->host->private_data;

	int ret;

	/* Compute ATA timing */
	ret = ata_timing_compute(adev, adev->pio_mode, &timing, 1000, 0);
	if (ret) {
		dev_warn(ap->dev, "Failed to compute ATA timing %d\n", ret);
		return;
	}

	/* Setup SMC to ATA timing */
	ret = pata_at32_setup_timing(ap->dev, info, &timing);
	if (ret) {
		dev_warn(ap->dev, "Failed to setup ATA timing %d\n", ret);
		return;
	}
}