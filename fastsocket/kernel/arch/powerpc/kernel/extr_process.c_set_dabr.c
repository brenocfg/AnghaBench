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
typedef  unsigned long __get_cpu_var ;
struct TYPE_2__ {int (* set_dabr ) (unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_DABR ; 
 int /*<<< orphan*/  SPRN_DAC1 ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ ppc_md ; 
 int stub1 (unsigned long) ; 

int set_dabr(unsigned long dabr)
{
	__get_cpu_var(current_dabr) = dabr;

	if (ppc_md.set_dabr)
		return ppc_md.set_dabr(dabr);

	/* XXX should we have a CPU_FTR_HAS_DABR ? */
#if defined(CONFIG_BOOKE)
	mtspr(SPRN_DAC1, dabr);
#elif defined(CONFIG_PPC_BOOK3S)
	mtspr(SPRN_DABR, dabr);
#endif


	return 0;
}