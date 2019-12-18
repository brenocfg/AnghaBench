#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ata_timing {int /*<<< orphan*/  setup; int /*<<< orphan*/  recover; int /*<<< orphan*/  active; } ;
struct TYPE_3__ {int /*<<< orphan*/  nsect_addr; int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  data_addr; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  error_addr; } ;
struct ata_port {TYPE_2__* host; TYPE_1__ ioaddr; } ;
struct ata_device {int devno; int /*<<< orphan*/  pio_mode; } ;
struct TYPE_4__ {struct ata_port* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TIMING_SETUP ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,int /*<<< orphan*/ ,struct ata_timing*,int,int) ; 
 int /*<<< orphan*/  ata_timing_merge (struct ata_timing*,struct ata_timing*,struct ata_timing*,int /*<<< orphan*/ ) ; 
 size_t clamp_val (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ioread16 (int /*<<< orphan*/ ) ; 
 size_t ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 
 int opti_syscfg (int) ; 

__attribute__((used)) static void opti82c46x_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	u8 active, recover, setup;
	struct ata_timing t;
	struct ata_device *pair = ata_dev_pair(adev);
	int clock;
	int khz[4] = { 50000, 40000, 33000, 25000 };
	u8 rc;
	u8 sysclk;

	/* Get the clock */
	sysclk = opti_syscfg(0xAC) & 0xC0;	/* BIOS set */

	/* Enter configuration mode */
	ioread16(ap->ioaddr.error_addr);
	ioread16(ap->ioaddr.error_addr);
	iowrite8(3, ap->ioaddr.nsect_addr);

	/* Read VLB clock strapping */
	clock = 1000000000 / khz[sysclk];

	/* Get the timing data in cycles */
	ata_timing_compute(adev, adev->pio_mode, &t, clock, 1000);

	/* Setup timing is shared */
	if (pair) {
		struct ata_timing tp;
		ata_timing_compute(pair, pair->pio_mode, &tp, clock, 1000);

		ata_timing_merge(&t, &tp, &t, ATA_TIMING_SETUP);
	}

	active = clamp_val(t.active, 2, 17) - 2;
	recover = clamp_val(t.recover, 1, 16) - 1;
	setup = clamp_val(t.setup, 1, 4) - 1;

	/* Select the right timing bank for write timing */
	rc = ioread8(ap->ioaddr.lbal_addr);
	rc &= 0x7F;
	rc |= (adev->devno << 7);
	iowrite8(rc, ap->ioaddr.lbal_addr);

	/* Write the timings */
	iowrite8(active << 4 | recover, ap->ioaddr.error_addr);

	/* Select the right bank for read timings, also
	   load the shared timings for address */
	rc = ioread8(ap->ioaddr.device_addr);
	rc &= 0xC0;
	rc |= adev->devno;	/* Index select */
	rc |= (setup << 4) | 0x04;
	iowrite8(rc, ap->ioaddr.device_addr);

	/* Load the read timings */
	iowrite8(active << 4 | recover, ap->ioaddr.data_addr);

	/* Ensure the timing register mode is right */
	rc = ioread8(ap->ioaddr.lbal_addr);
	rc &= 0x73;
	rc |= 0x84;
	iowrite8(rc, ap->ioaddr.lbal_addr);

	/* Exit command mode */
	iowrite8(0x83,  ap->ioaddr.nsect_addr);

	/* We need to know this for quad device on the MVB */
	ap->host->private_data = ap;
}