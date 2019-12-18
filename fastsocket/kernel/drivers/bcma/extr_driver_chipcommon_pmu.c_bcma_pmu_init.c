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
struct TYPE_2__ {int rev; } ;
struct bcma_drv_cc {TYPE_1__ pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_PMU_CTL ; 
 int /*<<< orphan*/  BCMA_CC_PMU_CTL_NOILPONW ; 
 int /*<<< orphan*/  bcma_cc_mask32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_cc_set32 (struct bcma_drv_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_resources_init (struct bcma_drv_cc*) ; 
 int /*<<< orphan*/  bcma_pmu_workarounds (struct bcma_drv_cc*) ; 

void bcma_pmu_init(struct bcma_drv_cc *cc)
{
	if (cc->pmu.rev == 1)
		bcma_cc_mask32(cc, BCMA_CC_PMU_CTL,
			      ~BCMA_CC_PMU_CTL_NOILPONW);
	else
		bcma_cc_set32(cc, BCMA_CC_PMU_CTL,
			     BCMA_CC_PMU_CTL_NOILPONW);

	bcma_pmu_resources_init(cc);
	bcma_pmu_workarounds(cc);
}