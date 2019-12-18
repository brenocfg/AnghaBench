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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RTT_CTRL ; 
 int /*<<< orphan*/  AR_PHY_RTT_CTRL_RESTORE_MASK ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9003_hw_rtt_set_mask(struct ath_hw *ah, u32 rtt_mask)
{
	REG_RMW_FIELD(ah, AR_PHY_RTT_CTRL,
		      AR_PHY_RTT_CTRL_RESTORE_MASK, rtt_mask);
}