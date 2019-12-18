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
typedef  size_t u8 ;
typedef  int u16 ;
struct TYPE_2__ {int len; } ;
struct wb35_mds {size_t TxFillIndex; int* TxOwner; size_t* pTxBuffer; size_t TxDesIndex; int* TxDesFrom; int TxToggle; scalar_t__ TxTsc; int* TxBufferSize; size_t* TxCountInBuffer; int /*<<< orphan*/  TxThreadCount; int /*<<< orphan*/  TxTsc_2; scalar_t__ TxPause; } ;
struct hw_data {int IsKeyPreSet; } ;
struct wbsoft_priv {TYPE_1__ sMlmeFrame; struct wb35_mds Mds; struct hw_data sHwData; } ;
struct wb35_descriptor {size_t Descriptor_ID; scalar_t__ EapFix; } ;

/* Variables and functions */
 int CURRENT_FRAGMENT_THRESHOLD ; 
 int DOT_11_DA_OFFSET ; 
 scalar_t__ HAL_USB_MODE_BURST (struct hw_data*) ; 
 size_t MAC_SUBTYPE_MNGMNT_PROBE_REQUEST ; 
 size_t MAX_USB_TX_BUFFER ; 
 size_t MAX_USB_TX_BUFFER_NUMBER ; 
 size_t MAX_USB_TX_DESCRIPTOR ; 
 int /*<<< orphan*/  MLME_GetNextPacket (struct wbsoft_priv*,struct wb35_descriptor*) ; 
 int /*<<< orphan*/  MLME_SendComplete (struct wbsoft_priv*,int /*<<< orphan*/ ,int) ; 
 int Mds_BodyCopy (struct wbsoft_priv*,struct wb35_descriptor*,size_t*) ; 
 int /*<<< orphan*/  Mds_DurationSet (struct wbsoft_priv*,struct wb35_descriptor*,size_t*) ; 
 int /*<<< orphan*/  Mds_HeaderCopy (struct wbsoft_priv*,struct wb35_descriptor*,size_t*) ; 
 int /*<<< orphan*/  Wb35Tx_start (struct wbsoft_priv*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hal_driver_init_OK (struct hw_data*) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void
Mds_Tx(struct wbsoft_priv * adapter)
{
	struct hw_data *	pHwData = &adapter->sHwData;
	struct wb35_mds *pMds = &adapter->Mds;
	struct wb35_descriptor	TxDes;
	struct wb35_descriptor *pTxDes = &TxDes;
	u8		*XmitBufAddress;
	u16		XmitBufSize, PacketSize, stmp, CurrentSize, FragmentThreshold;
	u8		FillIndex, TxDesIndex, FragmentCount, FillCount;
	unsigned char	BufferFilled = false;


	if (pMds->TxPause)
		return;
	if (!hal_driver_init_OK(pHwData))
		return;

	//Only one thread can be run here
	if (atomic_inc_return(&pMds->TxThreadCount) != 1)
		goto cleanup;

	// Start to fill the data
	do {
		FillIndex = pMds->TxFillIndex;
		if (pMds->TxOwner[FillIndex]) { // Is owned by software 0:Yes 1:No
#ifdef _PE_TX_DUMP_
			printk("[Mds_Tx] Tx Owner is H/W.\n");
#endif
			break;
		}

		XmitBufAddress = pMds->pTxBuffer + (MAX_USB_TX_BUFFER * FillIndex); //Get buffer
		XmitBufSize = 0;
		FillCount = 0;
		do {
			PacketSize = adapter->sMlmeFrame.len;
			if (!PacketSize)
				break;

			//For Check the buffer resource
			FragmentThreshold = CURRENT_FRAGMENT_THRESHOLD;
			//931130.5.b
			FragmentCount = PacketSize/FragmentThreshold + 1;
			stmp = PacketSize + FragmentCount*32 + 8;//931130.5.c 8:MIC
			if ((XmitBufSize + stmp) >= MAX_USB_TX_BUFFER) {
				printk("[Mds_Tx] Excess max tx buffer.\n");
				break; // buffer is not enough
			}


			//
			// Start transmitting
			//
			BufferFilled = true;

			/* Leaves first u8 intact */
			memset((u8 *)pTxDes + 1, 0, sizeof(struct wb35_descriptor) - 1);

			TxDesIndex = pMds->TxDesIndex;//Get the current ID
			pTxDes->Descriptor_ID = TxDesIndex;
			pMds->TxDesFrom[ TxDesIndex ] = 2;//Storing the information of source comming from
			pMds->TxDesIndex++;
			pMds->TxDesIndex %= MAX_USB_TX_DESCRIPTOR;

			MLME_GetNextPacket( adapter, pTxDes );

			// Copy header. 8byte USB + 24byte 802.11Hdr. Set TxRate, Preamble type
			Mds_HeaderCopy( adapter, pTxDes, XmitBufAddress );

			// For speed up Key setting
			if (pTxDes->EapFix) {
#ifdef _PE_TX_DUMP_
				printk("35: EPA 4th frame detected. Size = %d\n", PacketSize);
#endif
				pHwData->IsKeyPreSet = 1;
			}

			// Copy (fragment) frame body, and set USB, 802.11 hdr flag
			CurrentSize = Mds_BodyCopy(adapter, pTxDes, XmitBufAddress);

			// Set RTS/CTS and Normal duration field into buffer
			Mds_DurationSet(adapter, pTxDes, XmitBufAddress);

			//Shift to the next address
			XmitBufSize += CurrentSize;
			XmitBufAddress += CurrentSize;

#ifdef _IBSS_BEACON_SEQ_STICK_
			if ((XmitBufAddress[ DOT_11_DA_OFFSET+8 ] & 0xfc) != MAC_SUBTYPE_MNGMNT_PROBE_REQUEST) // +8 for USB hdr
#endif
				pMds->TxToggle = true;

			// Get packet to transmit completed, 1:TESTSTA 2:MLME 3: Ndis data
			MLME_SendComplete(adapter, 0, true);

			// Software TSC count 20060214
			pMds->TxTsc++;
			if (pMds->TxTsc == 0)
				pMds->TxTsc_2++;

			FillCount++; // 20060928
		} while (HAL_USB_MODE_BURST(pHwData)); // End of multiple MSDU copy loop. false = single true = multiple sending

		// Move to the next one, if necessary
		if (BufferFilled) {
			// size setting
			pMds->TxBufferSize[ FillIndex ] = XmitBufSize;

			// 20060928 set Tx count
			pMds->TxCountInBuffer[FillIndex] = FillCount;

			// Set owner flag
			pMds->TxOwner[FillIndex] = 1;

			pMds->TxFillIndex++;
			pMds->TxFillIndex %= MAX_USB_TX_BUFFER_NUMBER;
			BufferFilled = false;
		} else
			break;

		if (!PacketSize) // No more pk for transmitting
			break;

	} while(true);

	//
	// Start to send by lower module
	//
	if (!pHwData->IsKeyPreSet)
		Wb35Tx_start(adapter);

 cleanup:
	atomic_dec(&pMds->TxThreadCount);
}