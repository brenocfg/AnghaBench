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
struct TYPE_2__ {int /*<<< orphan*/  perfctr; int /*<<< orphan*/  evntsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_perfctr_nmi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_evntsel_nmi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reserve_perfctr_nmi (int /*<<< orphan*/ ) ; 
 TYPE_1__* wd_ops ; 

__attribute__((used)) static int single_msr_reserve(void)
{
	if (!reserve_perfctr_nmi(wd_ops->perfctr))
		return 0;

	if (!reserve_evntsel_nmi(wd_ops->evntsel)) {
		release_perfctr_nmi(wd_ops->perfctr);
		return 0;
	}
	return 1;
}