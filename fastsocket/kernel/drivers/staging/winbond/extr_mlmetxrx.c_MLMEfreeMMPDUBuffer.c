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
struct TYPE_2__ {int* TxMMPDUInUse; int /*<<< orphan*/ * TxMMPDU; } ;
struct wbsoft_priv {TYPE_1__ sMlmeFrame; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int MAX_NUM_TX_MMPDU ; 

__attribute__((used)) static void MLMEfreeMMPDUBuffer(struct wbsoft_priv *adapter, s8 *pData)
{
	int i;

	// Reclaim the data buffer
	for (i = 0; i < MAX_NUM_TX_MMPDU; i++) {
		if (pData == (s8 *)&(adapter->sMlmeFrame.TxMMPDU[i]))
			break;
	}
	if (adapter->sMlmeFrame.TxMMPDUInUse[i])
		adapter->sMlmeFrame.TxMMPDUInUse[i] = false;
	else  {
		// Something wrong
		// PD43 Add debug code here???
	}
}