#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mt_cpu {int /*<<< orphan*/ * mtc_snaps; } ;
struct TYPE_3__ {struct mt_cpu cpu_monotonic; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXED_CTR_CTRL ; 
 int FIXED_CTR_CTRL_ENABLE ; 
 int FIXED_CTR_CTRL_INIT ; 
 int /*<<< orphan*/  GLOBAL_CTRL ; 
 int GLOBAL_CTRL_FIXED_EN ; 
 int MT_CORE_NFIXED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mt_core_set_snap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_core_supported ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
core_up(cpu_data_t *cpu)
{
	struct mt_cpu *mtc;

	if (!mt_core_supported) {
		return;
	}

	assert(ml_get_interrupts_enabled() == FALSE);

	mtc = &cpu->cpu_monotonic;

	for (int i = 0; i < MT_CORE_NFIXED; i++) {
		mt_core_set_snap(i, mtc->mtc_snaps[i]);
	}
	wrmsr64(FIXED_CTR_CTRL, FIXED_CTR_CTRL_INIT | FIXED_CTR_CTRL_ENABLE);
	wrmsr64(GLOBAL_CTRL, GLOBAL_CTRL_FIXED_EN);
}