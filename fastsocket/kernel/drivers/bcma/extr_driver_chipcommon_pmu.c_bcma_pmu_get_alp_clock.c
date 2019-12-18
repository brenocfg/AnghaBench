#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  rev; } ;
struct bcma_drv_cc {TYPE_3__ pmu; TYPE_1__* core; } ;
struct TYPE_5__ {int id; } ;
struct bcma_bus {TYPE_2__ chipinfo; } ;
struct TYPE_4__ {struct bcma_bus* bus; } ;

/* Variables and functions */
 int BCMA_CC_PMU_ALP_CLOCK ; 
#define  BCMA_CHIP_ID_BCM4313 136 
#define  BCMA_CHIP_ID_BCM4706 135 
#define  BCMA_CHIP_ID_BCM4716 134 
#define  BCMA_CHIP_ID_BCM47162 133 
#define  BCMA_CHIP_ID_BCM4748 132 
#define  BCMA_CHIP_ID_BCM4749 131 
#define  BCMA_CHIP_ID_BCM5356 130 
#define  BCMA_CHIP_ID_BCM5357 129 
#define  BCMA_CHIP_ID_BCM53572 128 
 int /*<<< orphan*/  bcma_warn (struct bcma_bus*,char*,int,int /*<<< orphan*/ ,int) ; 

u32 bcma_pmu_get_alp_clock(struct bcma_drv_cc *cc)
{
	struct bcma_bus *bus = cc->core->bus;

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
	case BCMA_CHIP_ID_BCM47162:
	case BCMA_CHIP_ID_BCM4313:
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
	case BCMA_CHIP_ID_BCM53572:
		/* always 20Mhz */
		return 20000 * 1000;
	case BCMA_CHIP_ID_BCM5356:
	case BCMA_CHIP_ID_BCM4706:
		/* always 25Mhz */
		return 25000 * 1000;
	default:
		bcma_warn(bus, "No ALP clock specified for %04X device, pmu rev. %d, using default %d Hz\n",
			  bus->chipinfo.id, cc->pmu.rev, BCMA_CC_PMU_ALP_CLOCK);
	}
	return BCMA_CC_PMU_ALP_CLOCK;
}