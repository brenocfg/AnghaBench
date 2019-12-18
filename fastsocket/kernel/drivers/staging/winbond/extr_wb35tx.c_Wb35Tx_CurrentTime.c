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
typedef  scalar_t__ u32 ;
struct wb35_tx {scalar_t__ TxTimer; } ;
struct hw_data {struct wb35_tx Wb35Tx; } ;
struct wbsoft_priv {struct hw_data sHwData; } ;

/* Variables and functions */
 int /*<<< orphan*/  Wb35Tx_EP2VM_start (struct wbsoft_priv*) ; 

void Wb35Tx_CurrentTime(struct wbsoft_priv *adapter, u32 TimeCount)
{
	struct hw_data * pHwData = &adapter->sHwData;
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;
	unsigned char Trigger = false;

	if (pWb35Tx->TxTimer > TimeCount)
		Trigger = true;
	else if (TimeCount > (pWb35Tx->TxTimer+500))
		Trigger = true;

	if (Trigger) {
		pWb35Tx->TxTimer = TimeCount;
		Wb35Tx_EP2VM_start(adapter);
	}
}