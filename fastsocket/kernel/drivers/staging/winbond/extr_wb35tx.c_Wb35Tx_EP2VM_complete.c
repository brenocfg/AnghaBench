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
typedef  int u32 ;
typedef  int u16 ;
struct wb35_tx {scalar_t__ EP2VM_status; void* EP2vm_state; int /*<<< orphan*/  TxResultCount; scalar_t__ tx_halt; scalar_t__ EP2_buf; } ;
struct hw_data {scalar_t__ HwStop; scalar_t__ SurpriseRemove; struct wb35_tx Wb35Tx; } ;
struct wbsoft_priv {struct hw_data sHwData; } ;
struct urb {scalar_t__ status; int actual_length; struct wbsoft_priv* context; } ;
struct TYPE_3__ {int value; } ;
typedef  TYPE_1__ T02_DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  Mds_SendComplete (struct wbsoft_priv*,TYPE_1__*) ; 
 void* VM_COMPLETED ; 
 void* VM_STOP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void Wb35Tx_EP2VM_complete(struct urb * pUrb)
{
	struct wbsoft_priv *adapter = pUrb->context;
	struct hw_data *	pHwData = &adapter->sHwData;
	T02_DESCRIPTOR	T02, TSTATUS;
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;
	u32 *		pltmp = (u32 *)pWb35Tx->EP2_buf;
	u32		i;
	u16		InterruptInLength;


	// Variable setting
	pWb35Tx->EP2vm_state = VM_COMPLETED;
	pWb35Tx->EP2VM_status = pUrb->status;

	// For Linux 2.4. Interrupt will always trigger
	if (pHwData->SurpriseRemove || pHwData->HwStop) // Let WbWlanHalt to handle surprise remove
		goto error;

	if (pWb35Tx->tx_halt)
		goto error;

	//The Urb is completed, check the result
	if (pWb35Tx->EP2VM_status != 0) {
		printk("EP2 IoCompleteRoutine return error\n");
		pWb35Tx->EP2vm_state= VM_STOP;
		goto error;
	}

	// Update the Tx result
	InterruptInLength = pUrb->actual_length;
	// Modify for minimum memory access and DWORD alignment.
	T02.value = cpu_to_le32(pltmp[0]) >> 8; // [31:8] -> [24:0]
	InterruptInLength -= 1;// 20051221.1.c Modify the follow for more stable
	InterruptInLength >>= 2; // InterruptInLength/4
	for (i = 1; i <= InterruptInLength; i++) {
		T02.value |= ((cpu_to_le32(pltmp[i]) & 0xff) << 24);

		TSTATUS.value = T02.value;  //20061009 anson's endian
		Mds_SendComplete( adapter, &TSTATUS );
		T02.value = cpu_to_le32(pltmp[i]) >> 8;
	}

	return;
error:
	atomic_dec(&pWb35Tx->TxResultCount);
	pWb35Tx->EP2vm_state = VM_STOP;
}