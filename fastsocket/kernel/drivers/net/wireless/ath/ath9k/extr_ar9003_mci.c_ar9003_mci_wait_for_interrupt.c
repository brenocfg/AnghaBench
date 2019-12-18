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
 int AR_MCI_INTERRUPT_RAW ; 
 int AR_MCI_INTERRUPT_REMOTE_SLEEP_UPDATE ; 
 int AR_MCI_INTERRUPT_RX_MSG ; 
 int AR_MCI_INTERRUPT_RX_MSG_RAW ; 
 int AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE ; 
 int AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING ; 
 int AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING ; 
 int /*<<< orphan*/  MCI ; 
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  ar9003_mci_reset_req_wakeup (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ar9003_mci_wait_for_interrupt(struct ath_hw *ah, u32 address,
					u32 bit_position, int time_out)
{
	struct ath_common *common = ath9k_hw_common(ah);

	while (time_out) {
		if (!(REG_READ(ah, address) & bit_position)) {
			udelay(10);
			time_out -= 10;

			if (time_out < 0)
				break;
			else
				continue;
		}
		REG_WRITE(ah, address, bit_position);

		if (address != AR_MCI_INTERRUPT_RX_MSG_RAW)
			break;

		if (bit_position & AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE)
			ar9003_mci_reset_req_wakeup(ah);

		if (bit_position & (AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING |
				    AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING))
			REG_WRITE(ah, AR_MCI_INTERRUPT_RAW,
				  AR_MCI_INTERRUPT_REMOTE_SLEEP_UPDATE);

		REG_WRITE(ah, AR_MCI_INTERRUPT_RAW, AR_MCI_INTERRUPT_RX_MSG);
		break;
	}

	if (time_out <= 0) {
		ath_dbg(common, MCI,
			"MCI Wait for Reg 0x%08x = 0x%08x timeout\n",
			address, bit_position);
		ath_dbg(common, MCI,
			"MCI INT_RAW = 0x%08x, RX_MSG_RAW = 0x%08x\n",
			REG_READ(ah, AR_MCI_INTERRUPT_RAW),
			REG_READ(ah, AR_MCI_INTERRUPT_RX_MSG_RAW));
		time_out = 0;
	}

	return time_out;
}