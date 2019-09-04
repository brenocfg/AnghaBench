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
struct TYPE_3__ {int /*<<< orphan*/  cpu_monotonic; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GLOBAL_CTRL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mt_core_supported ; 
 int /*<<< orphan*/  mt_mtc_update_fixed_counts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
core_down(cpu_data_t *cpu)
{
	if (!mt_core_supported) {
		return;
	}

	assert(ml_get_interrupts_enabled() == FALSE);

	wrmsr64(GLOBAL_CTRL, 0);
	mt_mtc_update_fixed_counts(&cpu->cpu_monotonic, NULL, NULL);
}