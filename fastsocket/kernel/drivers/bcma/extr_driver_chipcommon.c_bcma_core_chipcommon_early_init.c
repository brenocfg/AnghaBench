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
struct bcma_drv_cc {int early_setup_done; int capabilities; void* capabilities_ext; TYPE_2__* core; void* status; int /*<<< orphan*/  gpio_lock; } ;
struct TYPE_3__ {int rev; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CC_CAP ; 
 int /*<<< orphan*/  BCMA_CC_CAP_EXT ; 
 int BCMA_CC_CAP_PMU ; 
 int /*<<< orphan*/  BCMA_CC_CHIPSTAT ; 
 void* bcma_cc_read32 (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_pmu_early_init (struct bcma_drv_cc*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void bcma_core_chipcommon_early_init(struct bcma_drv_cc *cc)
{
	if (cc->early_setup_done)
		return;

	spin_lock_init(&cc->gpio_lock);

	if (cc->core->id.rev >= 11)
		cc->status = bcma_cc_read32(cc, BCMA_CC_CHIPSTAT);
	cc->capabilities = bcma_cc_read32(cc, BCMA_CC_CAP);
	if (cc->core->id.rev >= 35)
		cc->capabilities_ext = bcma_cc_read32(cc, BCMA_CC_CAP_EXT);

	if (cc->capabilities & BCMA_CC_CAP_PMU)
		bcma_pmu_early_init(cc);

	cc->early_setup_done = true;
}