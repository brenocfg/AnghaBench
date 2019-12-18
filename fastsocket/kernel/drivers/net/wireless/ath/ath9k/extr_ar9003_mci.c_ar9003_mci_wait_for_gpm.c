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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ath9k_hw_mci {scalar_t__ gpm_buf; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_MSG_GPM ; 
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_MSG_RAW ; 
 int /*<<< orphan*/  MCI ; 
 int /*<<< orphan*/  MCI_GPM ; 
 scalar_t__ MCI_GPM_BT_CAL_DONE ; 
 scalar_t__ MCI_GPM_BT_CAL_GRANT ; 
 scalar_t__ MCI_GPM_BT_CAL_REQ ; 
 scalar_t__ MCI_GPM_INVALID ; 
 scalar_t__ MCI_GPM_IS_CAL_TYPE (scalar_t__) ; 
 scalar_t__ MCI_GPM_MORE ; 
 scalar_t__ MCI_GPM_NOMORE ; 
 scalar_t__ MCI_GPM_OPCODE (scalar_t__*) ; 
 int /*<<< orphan*/  MCI_GPM_RECYCLE (scalar_t__*) ; 
 int /*<<< orphan*/  MCI_GPM_SET_CAL_TYPE (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MCI_GPM_TYPE (scalar_t__*) ; 
 int /*<<< orphan*/  MCI_GPM_WLAN_CAL_GRANT ; 
 scalar_t__ ar9003_mci_get_next_gpm_offset (struct ath_hw*,int,scalar_t__*) ; 
 int /*<<< orphan*/  ar9003_mci_process_gpm_extra (struct ath_hw*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int,int) ; 
 int ar9003_mci_wait_for_interrupt (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static u32 ar9003_mci_wait_for_gpm(struct ath_hw *ah, u8 gpm_type,
				   u8 gpm_opcode, int time_out)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 *p_gpm = NULL, mismatch = 0, more_data;
	u32 offset;
	u8 recv_type = 0, recv_opcode = 0;
	bool b_is_bt_cal_done = (gpm_type == MCI_GPM_BT_CAL_DONE);

	more_data = time_out ? MCI_GPM_NOMORE : MCI_GPM_MORE;

	while (time_out > 0) {
		if (p_gpm) {
			MCI_GPM_RECYCLE(p_gpm);
			p_gpm = NULL;
		}

		if (more_data != MCI_GPM_MORE)
			time_out = ar9003_mci_wait_for_interrupt(ah,
					AR_MCI_INTERRUPT_RX_MSG_RAW,
					AR_MCI_INTERRUPT_RX_MSG_GPM,
					time_out);

		if (!time_out)
			break;

		offset = ar9003_mci_get_next_gpm_offset(ah, false, &more_data);

		if (offset == MCI_GPM_INVALID)
			continue;

		p_gpm = (u32 *) (mci->gpm_buf + offset);
		recv_type = MCI_GPM_TYPE(p_gpm);
		recv_opcode = MCI_GPM_OPCODE(p_gpm);

		if (MCI_GPM_IS_CAL_TYPE(recv_type)) {
			if (recv_type == gpm_type) {
				if ((gpm_type == MCI_GPM_BT_CAL_DONE) &&
				    !b_is_bt_cal_done) {
					gpm_type = MCI_GPM_BT_CAL_GRANT;
					continue;
				}
				break;
			}
		} else if ((recv_type == gpm_type) &&
			   (recv_opcode == gpm_opcode))
			break;

		/*
		 * check if it's cal_grant
		 *
		 * When we're waiting for cal_grant in reset routine,
		 * it's possible that BT sends out cal_request at the
		 * same time. Since BT's calibration doesn't happen
		 * that often, we'll let BT completes calibration then
		 * we continue to wait for cal_grant from BT.
		 * Orginal: Wait BT_CAL_GRANT.
		 * New: Receive BT_CAL_REQ -> send WLAN_CAL_GRANT->wait
		 * BT_CAL_DONE -> Wait BT_CAL_GRANT.
		 */

		if ((gpm_type == MCI_GPM_BT_CAL_GRANT) &&
		    (recv_type == MCI_GPM_BT_CAL_REQ)) {

			u32 payload[4] = {0, 0, 0, 0};

			gpm_type = MCI_GPM_BT_CAL_DONE;
			MCI_GPM_SET_CAL_TYPE(payload,
					     MCI_GPM_WLAN_CAL_GRANT);
			ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16,
						false, false);
			continue;
		} else {
			ath_dbg(common, MCI, "MCI GPM subtype not match 0x%x\n",
				*(p_gpm + 1));
			mismatch++;
			ar9003_mci_process_gpm_extra(ah, recv_type,
						     recv_opcode, p_gpm);
		}
	}

	if (p_gpm) {
		MCI_GPM_RECYCLE(p_gpm);
		p_gpm = NULL;
	}

	if (time_out <= 0)
		time_out = 0;

	while (more_data == MCI_GPM_MORE) {
		offset = ar9003_mci_get_next_gpm_offset(ah, false, &more_data);
		if (offset == MCI_GPM_INVALID)
			break;

		p_gpm = (u32 *) (mci->gpm_buf + offset);
		recv_type = MCI_GPM_TYPE(p_gpm);
		recv_opcode = MCI_GPM_OPCODE(p_gpm);

		if (!MCI_GPM_IS_CAL_TYPE(recv_type))
			ar9003_mci_process_gpm_extra(ah, recv_type,
						     recv_opcode, p_gpm);

		MCI_GPM_RECYCLE(p_gpm);
	}

	return time_out;
}