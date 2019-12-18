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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct wb35_mds {scalar_t__* TxBufferSize; scalar_t__* TxCountInBuffer; int /*<<< orphan*/ * TxOwner; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;
struct wb35_tx {size_t TxSendIndex; int TxFillCount; int /*<<< orphan*/  TxFireCounter; int /*<<< orphan*/  EP4vm_state; int /*<<< orphan*/  ByteTransfer; int /*<<< orphan*/ ** TxBuffer; scalar_t__ tx_halt; scalar_t__ Tx4Urb; } ;
struct hw_data {TYPE_1__ WbUsb; scalar_t__ HwStop; scalar_t__ SurpriseRemove; struct wb35_tx Wb35Tx; } ;
struct wbsoft_priv {struct wb35_mds Mds; struct hw_data sHwData; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VM_RUNNING ; 
 int /*<<< orphan*/  VM_STOP ; 
 int /*<<< orphan*/  Wb35Tx_EP2VM_start (struct wbsoft_priv*) ; 
 int /*<<< orphan*/  Wb35Tx_complete ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct wbsoft_priv*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Wb35Tx(struct wbsoft_priv *adapter)
{
	struct hw_data *	pHwData = &adapter->sHwData;
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;
	u8		*pTxBufferAddress;
	struct wb35_mds *pMds = &adapter->Mds;
	struct urb *	pUrb = (struct urb *)pWb35Tx->Tx4Urb;
	int         	retv;
	u32		SendIndex;


	if (pHwData->SurpriseRemove || pHwData->HwStop)
		goto cleanup;

	if (pWb35Tx->tx_halt)
		goto cleanup;

	// Ownership checking
	SendIndex = pWb35Tx->TxSendIndex;
	if (!pMds->TxOwner[SendIndex]) //No more data need to be sent, return immediately
		goto cleanup;

	pTxBufferAddress = pWb35Tx->TxBuffer[SendIndex];
	//
	// Issuing URB
	//
	usb_fill_bulk_urb(pUrb, pHwData->WbUsb.udev,
			  usb_sndbulkpipe(pHwData->WbUsb.udev, 4),
			  pTxBufferAddress, pMds->TxBufferSize[ SendIndex ],
			  Wb35Tx_complete, adapter);

	pWb35Tx->EP4vm_state = VM_RUNNING;
	retv = usb_submit_urb(pUrb, GFP_ATOMIC);
	if (retv<0) {
		printk("EP4 Tx Irp sending error\n");
		goto cleanup;
	}

	// Check if driver needs issue Irp for EP2
	pWb35Tx->TxFillCount += pMds->TxCountInBuffer[SendIndex];
	if (pWb35Tx->TxFillCount > 12)
		Wb35Tx_EP2VM_start(adapter);

	pWb35Tx->ByteTransfer += pMds->TxBufferSize[SendIndex];
	return;

 cleanup:
	pWb35Tx->EP4vm_state = VM_STOP;
	atomic_dec(&pWb35Tx->TxFireCounter);
}