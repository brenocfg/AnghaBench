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
struct device {int dummy; } ;
struct ata_port {int /*<<< orphan*/  prd; int /*<<< orphan*/  prd_dma; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PRD_TBL_SZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dmam_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ata_port_start(struct ata_port *ap)
{
	struct device *dev = ap->dev;

	ap->prd = dmam_alloc_coherent(dev, ATA_PRD_TBL_SZ, &ap->prd_dma,
				      GFP_KERNEL);
	if (!ap->prd)
		return -ENOMEM;

	return 0;
}