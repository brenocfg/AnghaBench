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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL3 ; 
 int /*<<< orphan*/  PLL3_DO_MEAS_MASK ; 
 int /*<<< orphan*/  PLL4 ; 
 int PLL4_MEAS_DONE ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SQSUM_DVC_MASK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

u32 ar9003_get_pll_sqsum_dvc(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int i = 0;

	REG_CLR_BIT(ah, PLL3, PLL3_DO_MEAS_MASK);
	udelay(100);
	REG_SET_BIT(ah, PLL3, PLL3_DO_MEAS_MASK);

	while ((REG_READ(ah, PLL4) & PLL4_MEAS_DONE) == 0) {

		udelay(100);

		if (WARN_ON_ONCE(i >= 100)) {
			ath_err(common, "PLL4 meaurement not done\n");
			break;
		}

		i++;
	}

	return (REG_READ(ah, PLL3) & SQSUM_DVC_MASK) >> 3;
}