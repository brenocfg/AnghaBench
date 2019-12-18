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
typedef  int u8 ;
typedef  int u32 ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_GPM ; 
 int /*<<< orphan*/  MCI_GPM_COEX_AGENT ; 
 int /*<<< orphan*/  MCI_GPM_COEX_BT_UPDATE_FLAGS ; 
 int MCI_GPM_COEX_B_BT_FLAGS_OP ; 
 int MCI_GPM_COEX_W_BT_FLAGS ; 
 int /*<<< orphan*/  MCI_GPM_SET_TYPE_OPCODE (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int) ; 

__attribute__((used)) static bool ar9003_mci_send_coex_bt_flags(struct ath_hw *ah, bool wait_done,
					  u8 opcode, u32 bt_flags)
{
	u32 pld[4] = {0, 0, 0, 0};

	MCI_GPM_SET_TYPE_OPCODE(pld, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_BT_UPDATE_FLAGS);

	*(((u8 *)pld) + MCI_GPM_COEX_B_BT_FLAGS_OP)  = opcode;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 0) = bt_flags & 0xFF;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 1) = (bt_flags >> 8) & 0xFF;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 2) = (bt_flags >> 16) & 0xFF;
	*(((u8 *)pld) + MCI_GPM_COEX_W_BT_FLAGS + 3) = (bt_flags >> 24) & 0xFF;

	return ar9003_mci_send_message(ah, MCI_GPM, 0, pld, 16,
				       wait_done, true);
}