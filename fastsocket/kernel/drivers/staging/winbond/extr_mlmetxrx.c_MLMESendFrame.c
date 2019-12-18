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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ IsInUsed; int* pMMPDU; int DataType; int /*<<< orphan*/  wNumTxMMPDU; int /*<<< orphan*/  len; int /*<<< orphan*/  wNumTxMMPDUDiscarded; } ;
struct wbsoft_priv {TYPE_1__ sMlmeFrame; } ;

/* Variables and functions */
 int /*<<< orphan*/  Mds_Tx (struct wbsoft_priv*) ; 
 scalar_t__ PACKET_COME_FROM_MLME ; 
 scalar_t__ PACKET_FREE_TO_USE ; 

u8 MLMESendFrame(struct wbsoft_priv * adapter, u8 *pMMPDU, u16 len, u8 DataType)
/*	DataType : FRAME_TYPE_802_11_MANAGEMENT, FRAME_TYPE_802_11_MANAGEMENT_CHALLENGE,
				FRAME_TYPE_802_11_DATA */
{
	if (adapter->sMlmeFrame.IsInUsed != PACKET_FREE_TO_USE) {
		adapter->sMlmeFrame.wNumTxMMPDUDiscarded++;
		return false;
	}
	adapter->sMlmeFrame.IsInUsed = PACKET_COME_FROM_MLME;

	// Keep information for sending
	adapter->sMlmeFrame.pMMPDU = pMMPDU;
	adapter->sMlmeFrame.DataType = DataType;
	// len must be the last setting due to QUERY_SIZE_SECOND of Mds
	adapter->sMlmeFrame.len = len;
	adapter->sMlmeFrame.wNumTxMMPDU++;

	// H/W will enter power save by set the register. S/W don't send null frame
	//with PWRMgt bit enbled to enter power save now.

	// Transmit NDIS packet
	Mds_Tx(adapter);
	return true;
}