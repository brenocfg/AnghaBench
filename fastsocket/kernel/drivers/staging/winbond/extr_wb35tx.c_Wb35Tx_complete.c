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
struct wb35_mds {scalar_t__* TxOwner; } ;
struct wb35_tx {scalar_t__ EP4VM_status; size_t TxSendIndex; void* EP4vm_state; int /*<<< orphan*/  TxFireCounter; scalar_t__ tx_halt; } ;
struct hw_data {scalar_t__ HwStop; scalar_t__ SurpriseRemove; struct wb35_tx Wb35Tx; } ;
struct wbsoft_priv {struct wb35_mds Mds; struct hw_data sHwData; } ;
struct urb {scalar_t__ status; struct wbsoft_priv* context; } ;

/* Variables and functions */
 size_t MAX_USB_TX_BUFFER_NUMBER ; 
 int /*<<< orphan*/  Mds_Tx (struct wbsoft_priv*) ; 
 void* VM_COMPLETED ; 
 void* VM_STOP ; 
 int /*<<< orphan*/  Wb35Tx (struct wbsoft_priv*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void Wb35Tx_complete(struct urb * pUrb)
{
	struct wbsoft_priv *adapter = pUrb->context;
	struct hw_data *	pHwData = &adapter->sHwData;
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;
	struct wb35_mds *pMds = &adapter->Mds;

	printk("wb35: tx complete\n");
	// Variable setting
	pWb35Tx->EP4vm_state = VM_COMPLETED;
	pWb35Tx->EP4VM_status = pUrb->status; //Store the last result of Irp
	pMds->TxOwner[ pWb35Tx->TxSendIndex ] = 0;// Set the owner. Free the owner bit always.
	pWb35Tx->TxSendIndex++;
	pWb35Tx->TxSendIndex %= MAX_USB_TX_BUFFER_NUMBER;

	if (pHwData->SurpriseRemove || pHwData->HwStop) // Let WbWlanHalt to handle surprise remove
		goto error;

	if (pWb35Tx->tx_halt)
		goto error;

	// The URB is completed, check the result
	if (pWb35Tx->EP4VM_status != 0) {
		printk("URB submission failed\n");
		pWb35Tx->EP4vm_state = VM_STOP;
		goto error;
	}

	Mds_Tx(adapter);
	Wb35Tx(adapter);
	return;

error:
	atomic_dec(&pWb35Tx->TxFireCounter);
	pWb35Tx->EP4vm_state = VM_STOP;
}