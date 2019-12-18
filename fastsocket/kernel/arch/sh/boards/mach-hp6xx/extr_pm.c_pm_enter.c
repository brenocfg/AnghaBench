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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCR ; 
 int FRQCR_PLLEN ; 
 int FRQCR_PSTBY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ INTR_OFFSET ; 
 int /*<<< orphan*/  MCR ; 
 int MCR_RFSH ; 
 int MCR_RMODE ; 
 int /*<<< orphan*/  RTCNT ; 
 int /*<<< orphan*/  STBCR ; 
 int STBCR_MSTP2 ; 
 int STBCR_STBY ; 
 int WTCSR_CKS_4096 ; 
 int WTCSR_TME ; 
 int /*<<< orphan*/  clear_bl_bit () ; 
 int /*<<< orphan*/  cpu_sleep () ; 
 int ctrl_inb (int /*<<< orphan*/ ) ; 
 int ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (scalar_t__) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bl_bit () ; 
 int sh_wdt_read_csr () ; 
 int /*<<< orphan*/  sh_wdt_write_cnt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_wdt_write_csr (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wakeup_end ; 
 int /*<<< orphan*/  wakeup_start ; 

__attribute__((used)) static void pm_enter(void)
{
	u8 stbcr, csr;
	u16 frqcr, mcr;
	u32 vbr_new, vbr_old;

	set_bl_bit();

	/* set wdt */
	csr = sh_wdt_read_csr();
	csr &= ~WTCSR_TME;
	csr |= WTCSR_CKS_4096;
	sh_wdt_write_csr(csr);
	csr = sh_wdt_read_csr();
	sh_wdt_write_cnt(0);

	/* disable PLL1 */
	frqcr = ctrl_inw(FRQCR);
	frqcr &= ~(FRQCR_PLLEN | FRQCR_PSTBY);
	ctrl_outw(frqcr, FRQCR);

	/* enable standby */
	stbcr = ctrl_inb(STBCR);
	ctrl_outb(stbcr | STBCR_STBY | STBCR_MSTP2, STBCR);

	/* set self-refresh */
	mcr = ctrl_inw(MCR);
	ctrl_outw(mcr & ~MCR_RFSH, MCR);

	/* set interrupt handler */
	asm volatile("stc vbr, %0" : "=r" (vbr_old));
	vbr_new = get_zeroed_page(GFP_ATOMIC);
	udelay(50);
	memcpy((void*)(vbr_new + INTR_OFFSET),
	       &wakeup_start, &wakeup_end - &wakeup_start);
	asm volatile("ldc %0, vbr" : : "r" (vbr_new));

	ctrl_outw(0, RTCNT);
	ctrl_outw(mcr | MCR_RFSH | MCR_RMODE, MCR);

	cpu_sleep();

	asm volatile("ldc %0, vbr" : : "r" (vbr_old));

	free_page(vbr_new);

	/* enable PLL1 */
	frqcr = ctrl_inw(FRQCR);
	frqcr |= FRQCR_PSTBY;
	ctrl_outw(frqcr, FRQCR);
	udelay(50);
	frqcr |= FRQCR_PLLEN;
	ctrl_outw(frqcr, FRQCR);

	ctrl_outb(stbcr, STBCR);

	clear_bl_bit();
}