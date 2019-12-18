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
 int AH_RX_STOP_DMA_TIMEOUT ; 
 int AH_TIME_QUANTUM ; 
 int /*<<< orphan*/  AR_CR ; 
 int AR_CR_RXD ; 
 int AR_CR_RXE ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_DMADBG_7 ; 
 int /*<<< orphan*/  AR_MACMISC ; 
 int AR_MACMISC_DMA_OBS_LINE_8 ; 
 int AR_MACMISC_DMA_OBS_S ; 
 int AR_MACMISC_MISC_OBS_BUS_1 ; 
 int AR_MACMISC_MISC_OBS_BUS_MSB_S ; 
 int /*<<< orphan*/  AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool ath9k_hw_stopdmarecv(struct ath_hw *ah, bool *reset)
{
#define AH_RX_STOP_DMA_TIMEOUT 10000   /* usec */
	struct ath_common *common = ath9k_hw_common(ah);
	u32 mac_status, last_mac_status = 0;
	int i;

	/* Enable access to the DMA observation bus */
	REG_WRITE(ah, AR_MACMISC,
		  ((AR_MACMISC_DMA_OBS_LINE_8 << AR_MACMISC_DMA_OBS_S) |
		   (AR_MACMISC_MISC_OBS_BUS_1 <<
		    AR_MACMISC_MISC_OBS_BUS_MSB_S)));

	REG_WRITE(ah, AR_CR, AR_CR_RXD);

	/* Wait for rx enable bit to go low */
	for (i = AH_RX_STOP_DMA_TIMEOUT / AH_TIME_QUANTUM; i != 0; i--) {
		if ((REG_READ(ah, AR_CR) & AR_CR_RXE) == 0)
			break;

		if (!AR_SREV_9300_20_OR_LATER(ah)) {
			mac_status = REG_READ(ah, AR_DMADBG_7) & 0x7f0;
			if (mac_status == 0x1c0 && mac_status == last_mac_status) {
				*reset = true;
				break;
			}

			last_mac_status = mac_status;
		}

		udelay(AH_TIME_QUANTUM);
	}

	if (i == 0) {
		ath_err(common,
			"DMA failed to stop in %d ms AR_CR=0x%08x AR_DIAG_SW=0x%08x DMADBG_7=0x%08x\n",
			AH_RX_STOP_DMA_TIMEOUT / 1000,
			REG_READ(ah, AR_CR),
			REG_READ(ah, AR_DIAG_SW),
			REG_READ(ah, AR_DMADBG_7));
		return false;
	} else {
		return true;
	}

#undef AH_RX_STOP_DMA_TIMEOUT
}