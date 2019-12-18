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
typedef  int u16 ;
struct pcmcia_init {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PB1000_MDR ; 
 int /*<<< orphan*/  PB1000_PCR ; 
 int /*<<< orphan*/  PCMCIA_BOARD_REG ; 
 int PCMCIA_NUM_SOCKS ; 
 int PCR_SLOT_0_RST ; 
 int PCR_SLOT_1_RST ; 
 int PC_DEASSERT_RST ; 
 int PC_DRV_EN ; 
 int SET_VCC_VPP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VCC_HIZ ; 
 int /*<<< orphan*/  VPP_HIZ ; 
 int au_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_sync_delay (int) ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pb1x00_pcmcia_init(struct pcmcia_init *init)
{
#ifdef CONFIG_MIPS_PB1000
	u16 pcr;
	pcr = PCR_SLOT_0_RST | PCR_SLOT_1_RST;

	au_writel(0x8000, PB1000_MDR); /* clear pcmcia interrupt */
	au_sync_delay(100);
	au_writel(0x4000, PB1000_MDR); /* enable pcmcia interrupt */
	au_sync();

	pcr |= SET_VCC_VPP(VCC_HIZ,VPP_HIZ,0);
	pcr |= SET_VCC_VPP(VCC_HIZ,VPP_HIZ,1);
	au_writel(pcr, PB1000_PCR);
	au_sync_delay(20);
	  
	return PCMCIA_NUM_SOCKS;

#else /* fixme -- take care of the Pb1500 at some point */

	u16 pcr;
	pcr = au_readw(PCMCIA_BOARD_REG) & ~0xf; /* turn off power */
	pcr &= ~(PC_DEASSERT_RST | PC_DRV_EN);
	au_writew(pcr, PCMCIA_BOARD_REG);
	au_sync_delay(500);
	return PCMCIA_NUM_SOCKS;
#endif
}