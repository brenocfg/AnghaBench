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
struct TYPE_2__ {scalar_t__ bStopBeacon; scalar_t__ bBeaconBufReady; scalar_t__ eOPMode; int /*<<< orphan*/  PortOffset; scalar_t__ bStopDataPkt; scalar_t__ bStopTx0Pkt; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  scalar_t__ CARD_PKT_TYPE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAC_REG_TCR ; 
 int /*<<< orphan*/  MACvRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OP_MODE_ADHOC ; 
 scalar_t__ PKT_TYPE_802_11_ALL ; 
 scalar_t__ PKT_TYPE_802_11_BCN ; 
 scalar_t__ PKT_TYPE_802_11_DATA ; 
 scalar_t__ PKT_TYPE_802_11_MNG ; 
 int /*<<< orphan*/  TCR_AUTOBCNTX ; 
 scalar_t__ TRUE ; 

BOOL CARDbStartTxPacket (PVOID pDeviceHandler, CARD_PKT_TYPE ePktType)
{
    PSDevice    pDevice = (PSDevice) pDeviceHandler;


    if (ePktType == PKT_TYPE_802_11_ALL) {
        pDevice->bStopBeacon = FALSE;
        pDevice->bStopTx0Pkt = FALSE;
        pDevice->bStopDataPkt = FALSE;
    } else if (ePktType == PKT_TYPE_802_11_BCN) {
        pDevice->bStopBeacon = FALSE;
    } else if (ePktType == PKT_TYPE_802_11_MNG) {
        pDevice->bStopTx0Pkt = FALSE;
    } else if (ePktType == PKT_TYPE_802_11_DATA) {
        pDevice->bStopDataPkt = FALSE;
    }

    if ((pDevice->bStopBeacon == FALSE) &&
        (pDevice->bBeaconBufReady == TRUE) &&
        (pDevice->eOPMode == OP_MODE_ADHOC)) {
        MACvRegBitsOn(pDevice->PortOffset, MAC_REG_TCR, TCR_AUTOBCNTX);
    }

    return(TRUE);
}