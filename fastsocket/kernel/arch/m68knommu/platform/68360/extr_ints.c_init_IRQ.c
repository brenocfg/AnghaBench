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
struct TYPE_4__ {int depth; int /*<<< orphan*/ * chip; int /*<<< orphan*/ * action; int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int intr_cicr; int intr_cimr; } ;

/* Variables and functions */
 int CPMVEC_ERROR ; 
 int CPMVEC_IDMA1 ; 
 int CPMVEC_IDMA2 ; 
 int CPMVEC_PIO_PC0 ; 
 int CPMVEC_PIO_PC1 ; 
 int CPMVEC_PIO_PC10 ; 
 int CPMVEC_PIO_PC11 ; 
 int CPMVEC_PIO_PC2 ; 
 int CPMVEC_PIO_PC3 ; 
 int CPMVEC_PIO_PC4 ; 
 int CPMVEC_PIO_PC5 ; 
 int CPMVEC_PIO_PC6 ; 
 int CPMVEC_PIO_PC7 ; 
 int CPMVEC_PIO_PC8 ; 
 int CPMVEC_PIO_PC9 ; 
 int CPMVEC_RESERVED1 ; 
 int CPMVEC_RESERVED2 ; 
 int CPMVEC_RESERVED3 ; 
 int CPMVEC_RISCTIMER ; 
 int CPMVEC_SCC1 ; 
 int CPMVEC_SCC2 ; 
 int CPMVEC_SCC3 ; 
 int CPMVEC_SCC4 ; 
 int CPMVEC_SDMA_CB_ERR ; 
 int CPMVEC_SMC1 ; 
 int CPMVEC_SMC2 ; 
 int CPMVEC_SPI ; 
 int CPMVEC_TIMER1 ; 
 int CPMVEC_TIMER2 ; 
 int CPMVEC_TIMER3 ; 
 int CPMVEC_TIMER4 ; 
 int CPM_VECTOR_BASE ; 
 int /*<<< orphan*/  IRQ_DISABLED ; 
 int NR_IRQS ; 
 int /*<<< orphan*/ * _ramvec ; 
 int /*<<< orphan*/  bad_interrupt ; 
 int /*<<< orphan*/  buserr ; 
 int /*<<< orphan*/  cpm_interrupt_init () ; 
 int /*<<< orphan*/  intc_irq_chip ; 
 int /*<<< orphan*/  inthandler ; 
 TYPE_2__* irq_desc ; 
 TYPE_1__* pquicc ; 
 int /*<<< orphan*/  system_call ; 
 int /*<<< orphan*/  trap ; 

void init_IRQ(void)
{
	int i;
	int vba = (CPM_VECTOR_BASE<<4);

	/* set up the vectors */
	_ramvec[2] = buserr;
	_ramvec[3] = trap;
	_ramvec[4] = trap;
	_ramvec[5] = trap;
	_ramvec[6] = trap;
	_ramvec[7] = trap;
	_ramvec[8] = trap;
	_ramvec[9] = trap;
	_ramvec[10] = trap;
	_ramvec[11] = trap;
	_ramvec[12] = trap;
	_ramvec[13] = trap;
	_ramvec[14] = trap;
	_ramvec[15] = trap;

	_ramvec[32] = system_call;
	_ramvec[33] = trap;

	cpm_interrupt_init();

	/* set up CICR for vector base address and irq level */
	/* irl = 4, hp = 1f - see MC68360UM p 7-377 */
	pquicc->intr_cicr = 0x00e49f00 | vba;

	/* CPM interrupt vectors: (p 7-376) */
	_ramvec[vba+CPMVEC_ERROR]       = bad_interrupt; /* Error */
	_ramvec[vba+CPMVEC_PIO_PC11]    = inthandler;   /* pio - pc11 */
	_ramvec[vba+CPMVEC_PIO_PC10]    = inthandler;   /* pio - pc10 */
	_ramvec[vba+CPMVEC_SMC2]        = inthandler;   /* smc2/pip */
	_ramvec[vba+CPMVEC_SMC1]        = inthandler;   /* smc1 */
	_ramvec[vba+CPMVEC_SPI]         = inthandler;   /* spi */
	_ramvec[vba+CPMVEC_PIO_PC9]     = inthandler;   /* pio - pc9 */
	_ramvec[vba+CPMVEC_TIMER4]      = inthandler;   /* timer 4 */
	_ramvec[vba+CPMVEC_RESERVED1]   = inthandler;   /* reserved */
	_ramvec[vba+CPMVEC_PIO_PC8]     = inthandler;   /* pio - pc8 */
	_ramvec[vba+CPMVEC_PIO_PC7]     = inthandler;  /* pio - pc7 */
	_ramvec[vba+CPMVEC_PIO_PC6]     = inthandler;  /* pio - pc6 */
	_ramvec[vba+CPMVEC_TIMER3]      = inthandler;  /* timer 3 */
	_ramvec[vba+CPMVEC_RISCTIMER]   = inthandler;  /* reserved */
	_ramvec[vba+CPMVEC_PIO_PC5]     = inthandler;  /* pio - pc5 */
	_ramvec[vba+CPMVEC_PIO_PC4]     = inthandler;  /* pio - pc4 */
	_ramvec[vba+CPMVEC_RESERVED2]   = inthandler;  /* reserved */
	_ramvec[vba+CPMVEC_RISCTIMER]   = inthandler;  /* timer table */
	_ramvec[vba+CPMVEC_TIMER2]      = inthandler;  /* timer 2 */
	_ramvec[vba+CPMVEC_RESERVED3]   = inthandler;  /* reserved */
	_ramvec[vba+CPMVEC_IDMA2]       = inthandler;  /* idma 2 */
	_ramvec[vba+CPMVEC_IDMA1]       = inthandler;  /* idma 1 */
	_ramvec[vba+CPMVEC_SDMA_CB_ERR] = inthandler;  /* sdma channel bus error */
	_ramvec[vba+CPMVEC_PIO_PC3]     = inthandler;  /* pio - pc3 */
	_ramvec[vba+CPMVEC_PIO_PC2]     = inthandler;  /* pio - pc2 */
	/* _ramvec[vba+CPMVEC_TIMER1]      = cpm_isr_timer1; */  /* timer 1 */
	_ramvec[vba+CPMVEC_TIMER1]      = inthandler;  /* timer 1 */
	_ramvec[vba+CPMVEC_PIO_PC1]     = inthandler;  /* pio - pc1 */
	_ramvec[vba+CPMVEC_SCC4]        = inthandler;  /* scc 4 */
	_ramvec[vba+CPMVEC_SCC3]        = inthandler;  /* scc 3 */
	_ramvec[vba+CPMVEC_SCC2]        = inthandler;  /* scc 2 */
	_ramvec[vba+CPMVEC_SCC1]        = inthandler;  /* scc 1 */
	_ramvec[vba+CPMVEC_PIO_PC0]     = inthandler;  /* pio - pc0 */


	/* turn off all CPM interrupts */
	pquicc->intr_cimr = 0x00000000;

	for (i = 0; (i < NR_IRQS); i++) {
		irq_desc[i].status = IRQ_DISABLED;
		irq_desc[i].action = NULL;
		irq_desc[i].depth = 1;
		irq_desc[i].chip = &intc_irq_chip;
	}
}