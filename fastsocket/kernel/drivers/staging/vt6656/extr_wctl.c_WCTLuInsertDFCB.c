#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_8__ {int wSeqCtl; int /*<<< orphan*/ * abyAddr2; } ;
struct TYPE_7__ {scalar_t__ cbFreeDFCB; size_t cbDFCB; TYPE_1__* sRxDFCB; int /*<<< orphan*/  dwMaxReceiveLifetime; } ;
struct TYPE_6__ {scalar_t__ bInUse; int wSequence; int wFragNum; int /*<<< orphan*/ * abyAddr2; int /*<<< orphan*/  uLifetime; } ;
typedef  TYPE_2__* PSDevice ;
typedef  TYPE_3__* PS802_11Header ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  U_ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT WCTLuInsertDFCB (PSDevice pDevice, PS802_11Header pMACHeader)
{
UINT ii;

    if (pDevice->cbFreeDFCB == 0)
        return(pDevice->cbDFCB);
    for(ii=0;ii<pDevice->cbDFCB;ii++) {
        if (pDevice->sRxDFCB[ii].bInUse == FALSE) {
            pDevice->cbFreeDFCB--;
            pDevice->sRxDFCB[ii].uLifetime = pDevice->dwMaxReceiveLifetime;
            pDevice->sRxDFCB[ii].bInUse = TRUE;
            pDevice->sRxDFCB[ii].wSequence = (pMACHeader->wSeqCtl >> 4);
            pDevice->sRxDFCB[ii].wFragNum = (pMACHeader->wSeqCtl & 0x000F);
            memcpy(&(pDevice->sRxDFCB[ii].abyAddr2[0]), &(pMACHeader->abyAddr2[0]), U_ETHER_ADDR_LEN);
            return(ii);
        }
    }
    return(pDevice->cbDFCB);
}