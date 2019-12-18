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

/* Variables and functions */
 int AUXIO_LED ; 
 int PMC_IDLE_ON ; 
 int /*<<< orphan*/  PMC_IDLE_REG ; 
 int pmc_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_auxio (int,int) ; 

__attribute__((used)) static void pmc_swift_idle(void)
{
#ifdef PMC_DEBUG_LED
	set_auxio(0x00, AUXIO_LED);
#endif

	pmc_writeb(pmc_readb(PMC_IDLE_REG) | PMC_IDLE_ON, PMC_IDLE_REG);

#ifdef PMC_DEBUG_LED
	set_auxio(AUXIO_LED, 0x00);
#endif
}