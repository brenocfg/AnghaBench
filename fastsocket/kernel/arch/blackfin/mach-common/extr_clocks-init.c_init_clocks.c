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
struct dma_register {scalar_t__ cfg; } ;

/* Variables and functions */
 scalar_t__ ANOMALY_05000435 ; 
 int CLKBUFOE ; 
 int CONFIG_CCLK_ACT_DIV ; 
 int /*<<< orphan*/  CONFIG_MEM_EBIU_DDRQUE ; 
 int CONFIG_SCLK_DIV ; 
 int IWR_DISABLE_ALL ; 
 int IWR_ENABLE (int) ; 
 size_t MAX_DMA_CHANNELS ; 
 int /*<<< orphan*/  PLL_CTL ; 
 int PLL_CTL_VAL ; 
 int SDGCTL_WIDTH ; 
 int SRFS ; 
 int SRREQ ; 
 int /*<<< orphan*/  VR_CTL ; 
 int /*<<< orphan*/  bfin_read16 (int /*<<< orphan*/ ) ; 
 int bfin_read_EBIU_RSTCTL () ; 
 int bfin_read_EBIU_SDGCTL () ; 
 int bfin_read_VR_CTL () ; 
 int /*<<< orphan*/  bfin_write16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfin_write_EBIU_DDRCTL0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EBIU_DDRCTL1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EBIU_DDRCTL2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EBIU_DDRQUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_EBIU_RSTCTL (int) ; 
 int /*<<< orphan*/  bfin_write_EBIU_SDGCTL (int) ; 
 int /*<<< orphan*/  bfin_write_EBIU_SDRRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_PLL_DIV (int) ; 
 int /*<<< orphan*/  bfin_write_PLL_LOCKCNT (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR0 (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR1 (int) ; 
 int /*<<< orphan*/  bfin_write_SIC_IWR2 (int) ; 
 struct dma_register** dma_io_base_addr ; 
 int /*<<< orphan*/  do_sync () ; 
 int /*<<< orphan*/  mem_DDRCTL0 ; 
 int /*<<< orphan*/  mem_DDRCTL1 ; 
 int /*<<< orphan*/  mem_DDRCTL2 ; 
 int mem_SDGCTL ; 
 int /*<<< orphan*/  mem_SDRRC ; 

__attribute__((l1_text))
void init_clocks(void)
{
	/* Kill any active DMAs as they may trigger external memory accesses
	 * in the middle of reprogramming things, and that'll screw us up.
	 * For example, any automatic DMAs left by U-Boot for splash screens.
	 */
	size_t i;
	for (i = 0; i < MAX_DMA_CHANNELS; ++i) {
		struct dma_register *dma = dma_io_base_addr[i];
		dma->cfg = 0;
	}

	do_sync();

#ifdef SIC_IWR0
	bfin_write_SIC_IWR0(IWR_ENABLE(0));
# ifdef SIC_IWR1
	/* BF52x system reset does not properly reset SIC_IWR1 which
	 * will screw up the bootrom as it relies on MDMA0/1 waking it
	 * up from IDLE instructions.  See this report for more info:
	 * http://blackfin.uclinux.org/gf/tracker/4323
	 */
	if (ANOMALY_05000435)
		bfin_write_SIC_IWR1(IWR_ENABLE(10) | IWR_ENABLE(11));
	else
		bfin_write_SIC_IWR1(IWR_DISABLE_ALL);
# endif
# ifdef SIC_IWR2
	bfin_write_SIC_IWR2(IWR_DISABLE_ALL);
# endif
#else
	bfin_write_SIC_IWR(IWR_ENABLE(0));
#endif
	do_sync();
#ifdef EBIU_SDGCTL
	bfin_write_EBIU_SDGCTL(bfin_read_EBIU_SDGCTL() | SRFS);
	do_sync();
#endif

#ifdef CLKBUFOE
	bfin_write16(VR_CTL, bfin_read_VR_CTL() | CLKBUFOE);
	do_sync();
	__asm__ __volatile__("IDLE;");
#endif
	bfin_write_PLL_LOCKCNT(0x300);
	do_sync();
	/* We always write PLL_CTL thus avoiding Anomaly 05000242 */
	bfin_write16(PLL_CTL, PLL_CTL_VAL);
	__asm__ __volatile__("IDLE;");
	bfin_write_PLL_DIV(CONFIG_CCLK_ACT_DIV | CONFIG_SCLK_DIV);
#ifdef EBIU_SDGCTL
	bfin_write_EBIU_SDRRC(mem_SDRRC);
	bfin_write_EBIU_SDGCTL((bfin_read_EBIU_SDGCTL() & SDGCTL_WIDTH) | mem_SDGCTL);
#else
	bfin_write_EBIU_RSTCTL(bfin_read_EBIU_RSTCTL() & ~(SRREQ));
	do_sync();
	bfin_write_EBIU_RSTCTL(bfin_read_EBIU_RSTCTL() | 0x1);
	bfin_write_EBIU_DDRCTL0(mem_DDRCTL0);
	bfin_write_EBIU_DDRCTL1(mem_DDRCTL1);
	bfin_write_EBIU_DDRCTL2(mem_DDRCTL2);
#ifdef CONFIG_MEM_EBIU_DDRQUE
	bfin_write_EBIU_DDRQUE(CONFIG_MEM_EBIU_DDRQUE);
#endif
#endif
	do_sync();
	bfin_read16(0);
}