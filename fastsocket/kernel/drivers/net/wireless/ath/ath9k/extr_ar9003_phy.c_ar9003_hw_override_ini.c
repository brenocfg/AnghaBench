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

/* Variables and functions */
 int AR_ADHOC_MCAST_KEYID_ENABLE ; 
 int AR_AGG_WEP_ENABLE ; 
 int AR_AGG_WEP_ENABLE_FIX ; 
 int AR_DIAG_RX_ABORT ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2 ; 
 int /*<<< orphan*/  AR_PHY_CCK_DETECT ; 
 int AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9003_hw_override_ini(struct ath_hw *ah)
{
	u32 val;

	/*
	 * Set the RX_ABORT and RX_DIS and clear it only after
	 * RXE is set for MAC. This prevents frames with
	 * corrupted descriptor status.
	 */
	REG_SET_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

	/*
	 * For AR9280 and above, there is a new feature that allows
	 * Multicast search based on both MAC Address and Key ID. By default,
	 * this feature is enabled. But since the driver is not using this
	 * feature, we switch it off; otherwise multicast search based on
	 * MAC addr only will fail.
	 */
	val = REG_READ(ah, AR_PCU_MISC_MODE2) & (~AR_ADHOC_MCAST_KEYID_ENABLE);
	REG_WRITE(ah, AR_PCU_MISC_MODE2,
		  val | AR_AGG_WEP_ENABLE_FIX | AR_AGG_WEP_ENABLE);

	REG_SET_BIT(ah, AR_PHY_CCK_DETECT,
		    AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV);
}