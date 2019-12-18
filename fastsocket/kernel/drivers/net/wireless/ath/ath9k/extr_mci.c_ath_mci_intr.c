#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int* bf_addr; } ;
struct ath_mci_coex {TYPE_2__ gpm_buf; } ;
struct ath_softc {int /*<<< orphan*/  sc_flags; struct ath_hw* sc_ah; struct ath_mci_coex mci_coex; } ;
struct ath9k_hw_mci {scalar_t__ bt_state; int /*<<< orphan*/  cont_status; } ;
struct TYPE_3__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_CONT_PRIORITY ; 
 int /*<<< orphan*/  AR_MCI_CONT_RSSI_POWER ; 
 int /*<<< orphan*/  AR_MCI_CONT_TXRX ; 
 int AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT ; 
 int AR_MCI_INTERRUPT_RX_HW_MSG_MASK ; 
 int AR_MCI_INTERRUPT_RX_INVALID_HDR ; 
 int AR_MCI_INTERRUPT_RX_MSG_CONT_INFO ; 
 int AR_MCI_INTERRUPT_RX_MSG_CONT_NACK ; 
 int AR_MCI_INTERRUPT_RX_MSG_CONT_RST ; 
 int AR_MCI_INTERRUPT_RX_MSG_GPM ; 
 int AR_MCI_INTERRUPT_RX_MSG_LNA_CONTROL ; 
 int AR_MCI_INTERRUPT_RX_MSG_LNA_INFO ; 
 int AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE ; 
 int AR_MCI_INTERRUPT_RX_MSG_SCHD_INFO ; 
 int AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING ; 
 int AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING ; 
 int /*<<< orphan*/  MCI ; 
 scalar_t__ MCI_BT_AWAKE ; 
 scalar_t__ MCI_BT_SLEEP ; 
#define  MCI_GPM_COEX_AGENT 128 
 int MCI_GPM_COEX_NOOP ; 
 int MCI_GPM_INVALID ; 
 scalar_t__ MCI_GPM_IS_CAL_TYPE (int) ; 
 int MCI_GPM_MORE ; 
 int MCI_GPM_OPCODE (int*) ; 
 int /*<<< orphan*/  MCI_GPM_RECYCLE (int*) ; 
 int MCI_GPM_TYPE (int*) ; 
 int /*<<< orphan*/  MCI_REMOTE_RESET ; 
 int /*<<< orphan*/  MCI_STATE_ENABLE ; 
 int /*<<< orphan*/  MCI_STATE_LAST_SCHD_MSG_OFFSET ; 
 int /*<<< orphan*/  MCI_STATE_RECOVER_RX ; 
 int /*<<< orphan*/  MCI_STATE_REMOTE_SLEEP ; 
 int /*<<< orphan*/  MCI_STATE_RESET_REQ_WAKE ; 
 int /*<<< orphan*/  MCI_STATE_SET_BT_AWAKE ; 
 int /*<<< orphan*/  MCI_SYS_WAKING ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_OP_HW_RESET ; 
 int /*<<< orphan*/  ar9003_mci_get_interrupt (struct ath_hw*,int*,int*) ; 
 int ar9003_mci_get_next_gpm_offset (struct ath_hw*,int,int*) ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int) ; 
 scalar_t__ ar9003_mci_state (struct ath_hw*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  ath_mci_cal_msg (struct ath_softc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_mci_msg (struct ath_softc*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath_mci_intr(struct ath_softc *sc)
{
	struct ath_mci_coex *mci = &sc->mci_coex;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 mci_int, mci_int_rxmsg;
	u32 offset, subtype, opcode;
	u32 *pgpm;
	u32 more_data = MCI_GPM_MORE;
	bool skip_gpm = false;

	ar9003_mci_get_interrupt(sc->sc_ah, &mci_int, &mci_int_rxmsg);

	if (ar9003_mci_state(ah, MCI_STATE_ENABLE) == 0) {
		ar9003_mci_get_next_gpm_offset(ah, true, NULL);
		return;
	}

	if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE) {
		u32 payload[4] = { 0xffffffff, 0xffffffff,
				   0xffffffff, 0xffffff00};

		/*
		 * The following REMOTE_RESET and SYS_WAKING used to sent
		 * only when BT wake up. Now they are always sent, as a
		 * recovery method to reset BT MCI's RX alignment.
		 */
		ar9003_mci_send_message(ah, MCI_REMOTE_RESET, 0,
					payload, 16, true, false);
		ar9003_mci_send_message(ah, MCI_SYS_WAKING, 0,
					NULL, 0, true, false);

		mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_REQ_WAKE;
		ar9003_mci_state(ah, MCI_STATE_RESET_REQ_WAKE);

		/*
		 * always do this for recovery and 2G/5G toggling and LNA_TRANS
		 */
		ar9003_mci_state(ah, MCI_STATE_SET_BT_AWAKE);
	}

	if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING) {
		mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_SYS_WAKING;

		if ((mci_hw->bt_state == MCI_BT_SLEEP) &&
		    (ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP) !=
		     MCI_BT_SLEEP))
			ar9003_mci_state(ah, MCI_STATE_SET_BT_AWAKE);
	}

	if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING) {
		mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_SYS_SLEEPING;

		if ((mci_hw->bt_state == MCI_BT_AWAKE) &&
		    (ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP) !=
		     MCI_BT_AWAKE))
			mci_hw->bt_state = MCI_BT_SLEEP;
	}

	if ((mci_int & AR_MCI_INTERRUPT_RX_INVALID_HDR) ||
	    (mci_int & AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT)) {
		ar9003_mci_state(ah, MCI_STATE_RECOVER_RX);
		skip_gpm = true;
	}

	if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_SCHD_INFO) {
		mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_SCHD_INFO;
		offset = ar9003_mci_state(ah, MCI_STATE_LAST_SCHD_MSG_OFFSET);
	}

	if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_GPM) {
		mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_GPM;

		while (more_data == MCI_GPM_MORE) {
			if (test_bit(SC_OP_HW_RESET, &sc->sc_flags))
				return;

			pgpm = mci->gpm_buf.bf_addr;
			offset = ar9003_mci_get_next_gpm_offset(ah, false,
								&more_data);

			if (offset == MCI_GPM_INVALID)
				break;

			pgpm += (offset >> 2);

			/*
			 * The first dword is timer.
			 * The real data starts from 2nd dword.
			 */
			subtype = MCI_GPM_TYPE(pgpm);
			opcode = MCI_GPM_OPCODE(pgpm);

			if (skip_gpm)
				goto recycle;

			if (MCI_GPM_IS_CAL_TYPE(subtype)) {
				ath_mci_cal_msg(sc, subtype, (u8 *)pgpm);
			} else {
				switch (subtype) {
				case MCI_GPM_COEX_AGENT:
					ath_mci_msg(sc, opcode, (u8 *)pgpm);
					break;
				default:
					break;
				}
			}
		recycle:
			MCI_GPM_RECYCLE(pgpm);
		}
	}

	if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_HW_MSG_MASK) {
		if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_LNA_CONTROL)
			mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_LNA_CONTROL;

		if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_LNA_INFO)
			mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_LNA_INFO;

		if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_CONT_INFO) {
			int value_dbm = MS(mci_hw->cont_status,
					   AR_MCI_CONT_RSSI_POWER);

			mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_CONT_INFO;

			ath_dbg(common, MCI,
				"MCI CONT_INFO: (%s) pri = %d pwr = %d dBm\n",
				MS(mci_hw->cont_status, AR_MCI_CONT_TXRX) ?
				"tx" : "rx",
				MS(mci_hw->cont_status, AR_MCI_CONT_PRIORITY),
				value_dbm);
		}

		if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_CONT_NACK)
			mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_CONT_NACK;

		if (mci_int_rxmsg & AR_MCI_INTERRUPT_RX_MSG_CONT_RST)
			mci_int_rxmsg &= ~AR_MCI_INTERRUPT_RX_MSG_CONT_RST;
	}

	if ((mci_int & AR_MCI_INTERRUPT_RX_INVALID_HDR) ||
	    (mci_int & AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT)) {
		mci_int &= ~(AR_MCI_INTERRUPT_RX_INVALID_HDR |
			     AR_MCI_INTERRUPT_CONT_INFO_TIMEOUT);
		ath_mci_msg(sc, MCI_GPM_COEX_NOOP, NULL);
	}
}