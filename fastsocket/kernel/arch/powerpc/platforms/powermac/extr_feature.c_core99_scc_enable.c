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
struct macio_chip {unsigned long flags; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 long ENODEV ; 
 long EPERM ; 
 int /*<<< orphan*/  KEYLARGO_FCR0 ; 
 int KL0_IRDA_CLK19_ENABLE ; 
 int KL0_IRDA_CLK32_ENABLE ; 
 int KL0_IRDA_DEFAULT0 ; 
 int KL0_IRDA_DEFAULT1 ; 
 int KL0_IRDA_ENABLE ; 
 int KL0_IRDA_FAST_CONNECT ; 
 int KL0_IRDA_HIGH_BAND ; 
 int /*<<< orphan*/  KL0_IRDA_RESET ; 
 int KL0_IRDA_SOURCE1_SEL ; 
 int KL0_IRDA_SOURCE2_SEL ; 
 int KL0_SCCA_ENABLE ; 
 int KL0_SCCB_ENABLE ; 
 int KL0_SCC_A_INTF_ENABLE ; 
 int KL0_SCC_B_INTF_ENABLE ; 
 int KL0_SCC_CELL_ENABLE ; 
 int /*<<< orphan*/  KL0_SCC_RESET ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long MACIO_FLAG_SCCA_ON ; 
 unsigned long MACIO_FLAG_SCCB_ON ; 
 int MACIO_FLAG_SCC_LOCKED ; 
 int MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT32 (int /*<<< orphan*/ ,int) ; 
 long PMAC_SCC_FLAG_XMON ; 
 long PMAC_SCC_I2S1 ; 
 long PMAC_SCC_IRDA ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static long core99_scc_enable(struct device_node *node, long param, long value)
{
	struct macio_chip*	macio;
	unsigned long		flags;
	unsigned long		chan_mask;
	u32			fcr;

	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;
	if (!strcmp(node->name, "ch-a"))
		chan_mask = MACIO_FLAG_SCCA_ON;
	else if (!strcmp(node->name, "ch-b"))
		chan_mask = MACIO_FLAG_SCCB_ON;
	else
		return -ENODEV;

	if (value) {
		int need_reset_scc = 0;
		int need_reset_irda = 0;

		LOCK(flags);
		fcr = MACIO_IN32(KEYLARGO_FCR0);
		/* Check if scc cell need enabling */
		if (!(fcr & KL0_SCC_CELL_ENABLE)) {
			fcr |= KL0_SCC_CELL_ENABLE;
			need_reset_scc = 1;
		}
		if (chan_mask & MACIO_FLAG_SCCA_ON) {
			fcr |= KL0_SCCA_ENABLE;
			/* Don't enable line drivers for I2S modem */
			if ((param & 0xfff) == PMAC_SCC_I2S1)
				fcr &= ~KL0_SCC_A_INTF_ENABLE;
			else
				fcr |= KL0_SCC_A_INTF_ENABLE;
		}
		if (chan_mask & MACIO_FLAG_SCCB_ON) {
			fcr |= KL0_SCCB_ENABLE;
			/* Perform irda specific inits */
			if ((param & 0xfff) == PMAC_SCC_IRDA) {
				fcr &= ~KL0_SCC_B_INTF_ENABLE;
				fcr |= KL0_IRDA_ENABLE;
				fcr |= KL0_IRDA_CLK32_ENABLE | KL0_IRDA_CLK19_ENABLE;
				fcr |= KL0_IRDA_SOURCE1_SEL;
				fcr &= ~(KL0_IRDA_FAST_CONNECT|KL0_IRDA_DEFAULT1|KL0_IRDA_DEFAULT0);
				fcr &= ~(KL0_IRDA_SOURCE2_SEL|KL0_IRDA_HIGH_BAND);
				need_reset_irda = 1;
			} else
				fcr |= KL0_SCC_B_INTF_ENABLE;
		}
		MACIO_OUT32(KEYLARGO_FCR0, fcr);
		macio->flags |= chan_mask;
		if (need_reset_scc)  {
			MACIO_BIS(KEYLARGO_FCR0, KL0_SCC_RESET);
			(void)MACIO_IN32(KEYLARGO_FCR0);
			UNLOCK(flags);
			mdelay(15);
			LOCK(flags);
			MACIO_BIC(KEYLARGO_FCR0, KL0_SCC_RESET);
		}
		if (need_reset_irda)  {
			MACIO_BIS(KEYLARGO_FCR0, KL0_IRDA_RESET);
			(void)MACIO_IN32(KEYLARGO_FCR0);
			UNLOCK(flags);
			mdelay(15);
			LOCK(flags);
			MACIO_BIC(KEYLARGO_FCR0, KL0_IRDA_RESET);
		}
		UNLOCK(flags);
		if (param & PMAC_SCC_FLAG_XMON)
			macio->flags |= MACIO_FLAG_SCC_LOCKED;
	} else {
		if (macio->flags & MACIO_FLAG_SCC_LOCKED)
			return -EPERM;
		LOCK(flags);
		fcr = MACIO_IN32(KEYLARGO_FCR0);
		if (chan_mask & MACIO_FLAG_SCCA_ON)
			fcr &= ~KL0_SCCA_ENABLE;
		if (chan_mask & MACIO_FLAG_SCCB_ON) {
			fcr &= ~KL0_SCCB_ENABLE;
			/* Perform irda specific clears */
			if ((param & 0xfff) == PMAC_SCC_IRDA) {
				fcr &= ~KL0_IRDA_ENABLE;
				fcr &= ~(KL0_IRDA_CLK32_ENABLE | KL0_IRDA_CLK19_ENABLE);
				fcr &= ~(KL0_IRDA_FAST_CONNECT|KL0_IRDA_DEFAULT1|KL0_IRDA_DEFAULT0);
				fcr &= ~(KL0_IRDA_SOURCE1_SEL|KL0_IRDA_SOURCE2_SEL|KL0_IRDA_HIGH_BAND);
			}
		}
		MACIO_OUT32(KEYLARGO_FCR0, fcr);
		if ((fcr & (KL0_SCCA_ENABLE | KL0_SCCB_ENABLE)) == 0) {
			fcr &= ~KL0_SCC_CELL_ENABLE;
			MACIO_OUT32(KEYLARGO_FCR0, fcr);
		}
		macio->flags &= ~(chan_mask);
		UNLOCK(flags);
		mdelay(10);
	}
	return 0;
}