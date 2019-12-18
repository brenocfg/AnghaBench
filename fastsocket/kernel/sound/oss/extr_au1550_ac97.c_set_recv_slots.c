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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_AC97CFG ; 
 int PSC_AC97CFG_DE_ENABLE ; 
 int PSC_AC97CFG_RXSLOT_ENA (int) ; 
 int PSC_AC97CFG_RXSLOT_MASK ; 
 int /*<<< orphan*/  PSC_AC97STAT ; 
 int PSC_AC97STAT_DR ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_recv_slots(int num_channels)
{
	u32	ac97_config, stat;

	ac97_config = au_readl(PSC_AC97CFG);
	au_sync();
	ac97_config &= ~(PSC_AC97CFG_RXSLOT_MASK | PSC_AC97CFG_DE_ENABLE);
	au_writel(ac97_config, PSC_AC97CFG);
	au_sync();

	/* Always enable slots 3 and 4 (stereo). Slot 6 is
	 * optional Mic ADC, which we don't support yet.
	 */
	ac97_config |= PSC_AC97CFG_RXSLOT_ENA(3);
	ac97_config |= PSC_AC97CFG_RXSLOT_ENA(4);

	au_writel(ac97_config, PSC_AC97CFG);
	au_sync();

	ac97_config |= PSC_AC97CFG_DE_ENABLE;
	au_writel(ac97_config, PSC_AC97CFG);
	au_sync();

	/* Wait for Device ready.
	*/
	do {
		stat = au_readl(PSC_AC97STAT);
		au_sync();
	} while ((stat & PSC_AC97STAT_DR) == 0);
}