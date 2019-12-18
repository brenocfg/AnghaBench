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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ autoneg; } ;
struct tg3 {int phy_flags; TYPE_1__ link_config; scalar_t__ link_up; scalar_t__ serdes_counter; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED1000 ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_TG3_DSP_ADDRESS ; 
 int MII_TG3_DSP_EXP1_INT_STAT ; 
 int /*<<< orphan*/  MII_TG3_DSP_RW_PORT ; 
 int /*<<< orphan*/  MII_TG3_MISC_SHDW ; 
 int TG3_PHYFLG_PARALLEL_DETECT ; 
 int /*<<< orphan*/  tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tg3_serdes_parallel_detect(struct tg3 *tp)
{
	if (tp->serdes_counter) {
		/* Give autoneg time to complete. */
		tp->serdes_counter--;
		return;
	}

	if (!tp->link_up &&
	    (tp->link_config.autoneg == AUTONEG_ENABLE)) {
		u32 bmcr;

		tg3_readphy(tp, MII_BMCR, &bmcr);
		if (bmcr & BMCR_ANENABLE) {
			u32 phy1, phy2;

			/* Select shadow register 0x1f */
			tg3_writephy(tp, MII_TG3_MISC_SHDW, 0x7c00);
			tg3_readphy(tp, MII_TG3_MISC_SHDW, &phy1);

			/* Select expansion interrupt status register */
			tg3_writephy(tp, MII_TG3_DSP_ADDRESS,
					 MII_TG3_DSP_EXP1_INT_STAT);
			tg3_readphy(tp, MII_TG3_DSP_RW_PORT, &phy2);
			tg3_readphy(tp, MII_TG3_DSP_RW_PORT, &phy2);

			if ((phy1 & 0x10) && !(phy2 & 0x20)) {
				/* We have signal detect and not receiving
				 * config code words, link is up by parallel
				 * detection.
				 */

				bmcr &= ~BMCR_ANENABLE;
				bmcr |= BMCR_SPEED1000 | BMCR_FULLDPLX;
				tg3_writephy(tp, MII_BMCR, bmcr);
				tp->phy_flags |= TG3_PHYFLG_PARALLEL_DETECT;
			}
		}
	} else if (tp->link_up &&
		   (tp->link_config.autoneg == AUTONEG_ENABLE) &&
		   (tp->phy_flags & TG3_PHYFLG_PARALLEL_DETECT)) {
		u32 phy2;

		/* Select expansion interrupt status register */
		tg3_writephy(tp, MII_TG3_DSP_ADDRESS,
				 MII_TG3_DSP_EXP1_INT_STAT);
		tg3_readphy(tp, MII_TG3_DSP_RW_PORT, &phy2);
		if (phy2 & 0x20) {
			u32 bmcr;

			/* Config code words received, turn on autoneg. */
			tg3_readphy(tp, MII_BMCR, &bmcr);
			tg3_writephy(tp, MII_BMCR, bmcr | BMCR_ANENABLE);

			tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;

		}
	}
}