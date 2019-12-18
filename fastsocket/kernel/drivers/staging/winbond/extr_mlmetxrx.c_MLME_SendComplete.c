#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  IsInUsed; int /*<<< orphan*/  pMMPDU; scalar_t__ len; } ;
struct wbsoft_priv {TYPE_1__ sMlmeFrame; } ;
struct TYPE_4__ {int /*<<< orphan*/  bResult; } ;
typedef  TYPE_2__ MLME_TXCALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  MLME_SUCCESS ; 
 int /*<<< orphan*/  MLMEfreeMMPDUBuffer (struct wbsoft_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET_FREE_TO_USE ; 

void
MLME_SendComplete(struct wbsoft_priv * adapter, u8 PacketID, unsigned char SendOK)
{
	MLME_TXCALLBACK	TxCallback;

    // Reclaim the data buffer
	adapter->sMlmeFrame.len = 0;
	MLMEfreeMMPDUBuffer( adapter, adapter->sMlmeFrame.pMMPDU );


	TxCallback.bResult = MLME_SUCCESS;

	// Return resource
	adapter->sMlmeFrame.IsInUsed = PACKET_FREE_TO_USE;
}