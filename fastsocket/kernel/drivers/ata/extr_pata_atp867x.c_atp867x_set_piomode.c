#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct atp867x_priv {int /*<<< orphan*/  eightb_piospd; int /*<<< orphan*/  mstr_piospd; int /*<<< orphan*/  slave_piospd; int /*<<< orphan*/  dma_mode; } ;
struct ata_timing {int /*<<< orphan*/  rec8b; int /*<<< orphan*/  act8b; int /*<<< orphan*/  recover; int /*<<< orphan*/  active; } ;
struct ata_port {struct atp867x_priv* private_data; } ;
struct ata_device {int pio_mode; int devno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_TIMING_8BIT ; 
 int ATP867X_IO_DMAMODE_MSTR_MASK ; 
 int ATP867X_IO_DMAMODE_SLAVE_MASK ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 int /*<<< orphan*/  ata_timing_compute (struct ata_device*,int,struct ata_timing*,int,int) ; 
 int /*<<< orphan*/  ata_timing_merge (struct ata_timing*,struct ata_timing*,struct ata_timing*,int /*<<< orphan*/ ) ; 
 int atp867x_get_active_clocks_shifted (struct ata_port*,int /*<<< orphan*/ ) ; 
 int atp867x_get_recover_clocks_shifted (int /*<<< orphan*/ ) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atp867x_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	struct ata_device *peer = ata_dev_pair(adev);
	struct atp867x_priv *dp = ap->private_data;
	u8 speed = adev->pio_mode;
	struct ata_timing t, p;
	int T, UT;
	u8 b;

	T = 1000000000 / 33333;
	UT = T / 4;

	ata_timing_compute(adev, speed, &t, T, UT);
	if (peer && peer->pio_mode) {
		ata_timing_compute(peer, peer->pio_mode, &p, T, UT);
		ata_timing_merge(&p, &t, &t, ATA_TIMING_8BIT);
	}

	b = ioread8(dp->dma_mode);
	if (adev->devno & 1)
		b = (b & ~ATP867X_IO_DMAMODE_SLAVE_MASK);
	else
		b = (b & ~ATP867X_IO_DMAMODE_MSTR_MASK);
	iowrite8(b, dp->dma_mode);

	b = atp867x_get_active_clocks_shifted(ap, t.active) |
	    atp867x_get_recover_clocks_shifted(t.recover);

	if (adev->devno & 1)
		iowrite8(b, dp->slave_piospd);
	else
		iowrite8(b, dp->mstr_piospd);

	b = atp867x_get_active_clocks_shifted(ap, t.act8b) |
	    atp867x_get_recover_clocks_shifted(t.rec8b);

	iowrite8(b, dp->eightb_piospd);
}