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
struct TYPE_2__ {int intr_cicr; scalar_t__ intr_cimr; } ;

/* Variables and functions */
 int CICR_HP_MASK ; 
 int CICR_SCA_SCC1 ; 
 int CICR_SCB_SCC2 ; 
 int CICR_SCC_SCC3 ; 
 int CICR_SCD_SCC4 ; 
 int CICR_SPS ; 
 int CPM_INTERRUPT ; 
 int CPM_VECTOR_BASE ; 
 TYPE_1__* pquicc ; 

void
cpm_interrupt_init(void)
{
	/* Initialize the CPM interrupt controller.
	 * NOTE THAT pquicc had better have been initialized!
	 * reference: MC68360UM p. 7-377
	 */
	pquicc->intr_cicr =
		(CICR_SCD_SCC4 | CICR_SCC_SCC3 | CICR_SCB_SCC2 | CICR_SCA_SCC1) |
		(CPM_INTERRUPT << 13) |
		CICR_HP_MASK |
		(CPM_VECTOR_BASE << 5) |
		CICR_SPS;

	/* mask all CPM interrupts from reaching the cpu32 core: */
	pquicc->intr_cimr = 0;


	/* mles - If I understand correctly, the 360 just pops over to the CPM
	 * specific vector, obviating the necessity to vector through the IRQ
	 * whose priority the CPM is set to. This needs a closer look, though.
	 */

	/* Set our interrupt handler with the core CPU. */
/* 	if (request_irq(CPM_INTERRUPT, cpm_interrupt, 0, "cpm", NULL) != 0) */
/* 		panic("Could not allocate CPM IRQ!"); */

	/* Install our own error handler.
	 */
	/* I think we want to hold off on this one for the moment - mles */
	/* cpm_install_handler(CPMVEC_ERROR, cpm_error_interrupt, NULL); */

	/* master CPM interrupt enable */
	/* pquicc->intr_cicr |= CICR_IEN; */ /* no such animal for 360 */
}