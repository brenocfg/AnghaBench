#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hw_data {size_t dto_tx_retry_count; size_t* tx_retry_count; size_t dto_tx_frag_count; int /*<<< orphan*/  tx_ETR_count; int /*<<< orphan*/  tx_Null_key_count; int /*<<< orphan*/  tx_WepOn_false_count; int /*<<< orphan*/  tx_TBTT_start_count; } ;
struct wb35_mds {size_t** TxRate; int /*<<< orphan*/ * TxResult; } ;
struct wbsoft_priv {struct hw_data sHwData; struct wb35_mds Mds; } ;
struct TYPE_3__ {int value; scalar_t__ T02_effective_transmission_rate; scalar_t__ T02_discard_due_to_null_wep_key; scalar_t__ T02_transmit_without_encryption_due_to_wep_on_false; scalar_t__ T02_transmit_abort_due_to_TBTT; scalar_t__ T02_out_of_MaxTxMSDULiftTime; scalar_t__ T02_transmit_abort; scalar_t__ T02_MPDU_Cnt; scalar_t__ T02_IsLastMpdu; scalar_t__ T02_IgnoreResult; scalar_t__ T02_Tx_PktID; } ;
typedef  TYPE_1__* PT02_DESCRIPTOR ;

/* Variables and functions */
 int FLAG_ERROR_TX_MASK ; 
 int /*<<< orphan*/  MTO_SetTxCount (struct wbsoft_priv*,size_t,size_t) ; 
 int /*<<< orphan*/  printk (char*,size_t) ; 

void
Mds_SendComplete(struct wbsoft_priv * adapter, PT02_DESCRIPTOR pT02)
{
	struct wb35_mds *pMds = &adapter->Mds;
	struct hw_data *	pHwData = &adapter->sHwData;
	u8	PacketId = (u8)pT02->T02_Tx_PktID;
	unsigned char	SendOK = true;
	u8	RetryCount, TxRate;

	if (pT02->T02_IgnoreResult) // Don't care the result
		return;
	if (pT02->T02_IsLastMpdu) {
		//TODO: DTO -- get the retry count and fragment count
		// Tx rate
		TxRate = pMds->TxRate[ PacketId ][ 0 ];
		RetryCount = (u8)pT02->T02_MPDU_Cnt;
		if (pT02->value & FLAG_ERROR_TX_MASK) {
			SendOK = false;

			if (pT02->T02_transmit_abort || pT02->T02_out_of_MaxTxMSDULiftTime) {
				//retry error
				pHwData->dto_tx_retry_count += (RetryCount+1);
				//[for tx debug]
				if (RetryCount<7)
					pHwData->tx_retry_count[RetryCount] += RetryCount;
				else
					pHwData->tx_retry_count[7] += RetryCount;
				#ifdef _PE_STATE_DUMP_
				printk("dto_tx_retry_count =%d\n", pHwData->dto_tx_retry_count);
				#endif
				MTO_SetTxCount(adapter, TxRate, RetryCount);
			}
			pHwData->dto_tx_frag_count += (RetryCount+1);

			//[for tx debug]
			if (pT02->T02_transmit_abort_due_to_TBTT)
				pHwData->tx_TBTT_start_count++;
			if (pT02->T02_transmit_without_encryption_due_to_wep_on_false)
				pHwData->tx_WepOn_false_count++;
			if (pT02->T02_discard_due_to_null_wep_key)
				pHwData->tx_Null_key_count++;
		} else {
			if (pT02->T02_effective_transmission_rate)
				pHwData->tx_ETR_count++;
			MTO_SetTxCount(adapter, TxRate, RetryCount);
		}

		// Clear send result buffer
		pMds->TxResult[ PacketId ] = 0;
	} else
		pMds->TxResult[ PacketId ] |= ((u16)(pT02->value & 0x0ffff));
}