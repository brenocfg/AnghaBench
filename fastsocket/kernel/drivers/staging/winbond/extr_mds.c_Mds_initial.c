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
struct wb35_mds {int TxPause; int /*<<< orphan*/  pTxBuffer; int /*<<< orphan*/  TxFragmentThreshold; int /*<<< orphan*/  TxRTSThreshold; } ;
struct wbsoft_priv {int /*<<< orphan*/  sHwData; struct wb35_mds Mds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_FRAGMENT_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_RTSThreshold ; 
 unsigned char hal_get_tx_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

unsigned char
Mds_initial(struct wbsoft_priv * adapter)
{
	struct wb35_mds *pMds = &adapter->Mds;

	pMds->TxPause = false;
	pMds->TxRTSThreshold = DEFAULT_RTSThreshold;
	pMds->TxFragmentThreshold = DEFAULT_FRAGMENT_THRESHOLD;

	return hal_get_tx_buffer( &adapter->sHwData, &pMds->pTxBuffer );
}