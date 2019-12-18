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
typedef  int u16 ;
struct wb35_rx {scalar_t__ EP3VM_status; size_t CurrentRxBufferId; int* RxOwner; int ByteReceived; int* RxBufferSize; void* EP3vm_state; int /*<<< orphan*/  RxFireCounter; int /*<<< orphan*/ * pDRx; int /*<<< orphan*/  Ep3ErrorCount2; scalar_t__ rx_halt; } ;
struct hw_data {scalar_t__ HwStop; scalar_t__ SurpriseRemove; struct wb35_rx Wb35Rx; } ;
struct wbsoft_priv {struct hw_data sHwData; } ;
struct urb {scalar_t__ status; scalar_t__ actual_length; struct ieee80211_hw* context; } ;
struct ieee80211_hw {struct wbsoft_priv* priv; } ;
struct TYPE_2__ {size_t R00_receive_byte_count; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ R00_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_USB_MODE_BURST (struct hw_data*) ; 
 void* VM_COMPLETED ; 
 void* VM_STOP ; 
 int /*<<< orphan*/  Wb35Rx (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  Wb35Rx_indicate (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (size_t) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void Wb35Rx_Complete(struct urb *urb)
{
	struct ieee80211_hw *hw = urb->context;
	struct wbsoft_priv *priv = hw->priv;
	struct hw_data * pHwData = &priv->sHwData;
	struct wb35_rx *pWb35Rx = &pHwData->Wb35Rx;
	u8 *		pRxBufferAddress;
	u32		SizeCheck;
	u16		BulkLength;
	u32		RxBufferId;
	R00_DESCRIPTOR 	R00;

	// Variable setting
	pWb35Rx->EP3vm_state = VM_COMPLETED;
	pWb35Rx->EP3VM_status = urb->status;//Store the last result of Irp

	RxBufferId = pWb35Rx->CurrentRxBufferId;

	pRxBufferAddress = pWb35Rx->pDRx;
	BulkLength = (u16)urb->actual_length;

	// The IRP is completed
	pWb35Rx->EP3vm_state = VM_COMPLETED;

	if (pHwData->SurpriseRemove || pHwData->HwStop) // Must be here, or RxBufferId is invalid
		goto error;

	if (pWb35Rx->rx_halt)
		goto error;

	// Start to process the data only in successful condition
	pWb35Rx->RxOwner[ RxBufferId ] = 0; // Set the owner to driver
	R00.value = le32_to_cpu(*(u32 *)pRxBufferAddress);

	// The URB is completed, check the result
	if (pWb35Rx->EP3VM_status != 0) {
		#ifdef _PE_USB_STATE_DUMP_
		printk("EP3 IoCompleteRoutine return error\n");
		#endif
		pWb35Rx->EP3vm_state = VM_STOP;
		goto error;
	}

	// 20060220 For recovering. check if operating in single USB mode
	if (!HAL_USB_MODE_BURST(pHwData)) {
		SizeCheck = R00.R00_receive_byte_count;  //20060926 anson's endian
		if ((SizeCheck & 0x03) > 0)
			SizeCheck -= 4;
		SizeCheck = (SizeCheck + 3) & ~0x03;
		SizeCheck += 12; // 8 + 4 badbeef
		if ((BulkLength > 1600) ||
			(SizeCheck > 1600) ||
			(BulkLength != SizeCheck) ||
			(BulkLength == 0)) { // Add for fail Urb
			pWb35Rx->EP3vm_state = VM_STOP;
			pWb35Rx->Ep3ErrorCount2++;
		}
	}

	// Indicating the receiving data
	pWb35Rx->ByteReceived += BulkLength;
	pWb35Rx->RxBufferSize[ RxBufferId ] = BulkLength;

	if (!pWb35Rx->RxOwner[ RxBufferId ])
		Wb35Rx_indicate(hw);

	kfree(pWb35Rx->pDRx);
	// Do the next receive
	Wb35Rx(hw);
	return;

error:
	pWb35Rx->RxOwner[ RxBufferId ] = 1; // Set the owner to hardware
	atomic_dec(&pWb35Rx->RxFireCounter);
	pWb35Rx->EP3vm_state = VM_STOP;
}