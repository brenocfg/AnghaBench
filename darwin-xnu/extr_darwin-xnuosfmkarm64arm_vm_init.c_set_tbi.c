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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tbi ;
struct TYPE_2__ {int /*<<< orphan*/  tcr_el1; } ;

/* Variables and functions */
 scalar_t__ PE_parse_boot_argn (char*,int*,int) ; 
 int TBI_KERNEL ; 
 int TBI_USER ; 
 int /*<<< orphan*/  TCR_TBI0_TOPBYTE_IGNORED ; 
 int /*<<< orphan*/  TCR_TBI1_TOPBYTE_IGNORED ; 
 int /*<<< orphan*/  get_tcr () ; 
 int /*<<< orphan*/  set_tcr (int /*<<< orphan*/ ) ; 
 TYPE_1__ sysreg_restore ; 
 int user_tbi ; 

__attribute__((used)) static void
set_tbi(void)
{
#if !__ARM_KERNEL_PROTECT__
	/* If we are not built with __ARM_KERNEL_PROTECT__, TBI can be turned
	 * off with a boot-arg.
	 */
	uint64_t old_tcr, new_tcr;
	int tbi = 0;

	if (PE_parse_boot_argn("tbi", &tbi, sizeof(tbi)))
		user_tbi = ((tbi & TBI_USER) == TBI_USER);
	old_tcr = new_tcr = get_tcr();
	new_tcr |= (user_tbi) ? TCR_TBI0_TOPBYTE_IGNORED : 0;
	new_tcr |= (tbi & TBI_KERNEL) ? TCR_TBI1_TOPBYTE_IGNORED : 0;

	if (old_tcr != new_tcr) {
		set_tcr(new_tcr);
		sysreg_restore.tcr_el1 = new_tcr;
	}
#endif /* !__ARM_KERNEL_PROTECT__ */
}