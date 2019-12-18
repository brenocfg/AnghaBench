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
struct ath_hw {int dummy; } ;
struct ath_common {TYPE_1__* bus_ops; } ;
struct TYPE_2__ {scalar_t__ ath_bus_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CFG ; 
 int AR_CFG_SWRB ; 
 int AR_CFG_SWRD ; 
 int AR_CFG_SWRG ; 
 int AR_CFG_SWTB ; 
 int AR_CFG_SWTD ; 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ ATH_USB ; 
 int INIT_CONFIG_STATUS ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ath9k_hw_init_desc(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	if (AR_SREV_9100(ah)) {
		u32 mask;
		mask = REG_READ(ah, AR_CFG);
		if (mask & (AR_CFG_SWRB | AR_CFG_SWTB | AR_CFG_SWRG)) {
			ath_dbg(common, RESET, "CFG Byte Swap Set 0x%x\n",
				mask);
		} else {
			mask = INIT_CONFIG_STATUS | AR_CFG_SWRB | AR_CFG_SWTB;
			REG_WRITE(ah, AR_CFG, mask);
			ath_dbg(common, RESET, "Setting CFG 0x%x\n",
				REG_READ(ah, AR_CFG));
		}
	} else {
		if (common->bus_ops->ath_bus_type == ATH_USB) {
			/* Configure AR9271 target WLAN */
			if (AR_SREV_9271(ah))
				REG_WRITE(ah, AR_CFG, AR_CFG_SWRB | AR_CFG_SWTB);
			else
				REG_WRITE(ah, AR_CFG, AR_CFG_SWTD | AR_CFG_SWRD);
		}
#ifdef __BIG_ENDIAN
		else if (AR_SREV_9330(ah) || AR_SREV_9340(ah) ||
			 AR_SREV_9550(ah))
			REG_RMW(ah, AR_CFG, AR_CFG_SWRB | AR_CFG_SWTB, 0);
		else
			REG_WRITE(ah, AR_CFG, AR_CFG_SWTD | AR_CFG_SWRD);
#endif
	}
}