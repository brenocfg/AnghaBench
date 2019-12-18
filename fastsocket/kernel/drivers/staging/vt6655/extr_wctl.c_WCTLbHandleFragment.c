#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pMACHeader ;
typedef  int UINT ;
struct TYPE_19__ {int wSeqCtl; } ;
struct TYPE_18__ {size_t uCurrentDFCBIdx; size_t cbDFCB; TYPE_2__* sRxDFCB; int /*<<< orphan*/  cbFreeDFCB; int /*<<< orphan*/  dwMaxReceiveLifetime; } ;
struct TYPE_17__ {int wSequence; int wFragNum; int cbFrameLength; scalar_t__ bInUse; TYPE_4__* pbyRxBuffer; TYPE_1__* skb; int /*<<< orphan*/  uLifetime; } ;
struct TYPE_16__ {scalar_t__ data; } ;
typedef  TYPE_3__* PSDevice ;
typedef  TYPE_4__* PS802_11Header ;
typedef  TYPE_4__* PBYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IS_FIRST_FRAGMENT_PKT (TYPE_4__*) ; 
 scalar_t__ IS_LAST_FRAGMENT_PKT (TYPE_4__*) ; 
 scalar_t__ TRUE ; 
 size_t WCTLuInsertDFCB (TYPE_3__*,TYPE_4__*) ; 
 void* WCTLuSearchDFCB (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 

BOOL WCTLbHandleFragment (PSDevice pDevice, PS802_11Header pMACHeader, UINT cbFrameLength, BOOL bWEP, BOOL bExtIV)
{
UINT            uHeaderSize;


    if (bWEP == TRUE) {
        uHeaderSize = 28;
        if (bExtIV)
        // ExtIV
            uHeaderSize +=4;
    }
    else {
        uHeaderSize = 24;
    }

    if (IS_FIRST_FRAGMENT_PKT(pMACHeader)) {
        pDevice->uCurrentDFCBIdx = WCTLuSearchDFCB(pDevice, pMACHeader);
        if (pDevice->uCurrentDFCBIdx < pDevice->cbDFCB) {
            // duplicate, we must flush previous DCB
            pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].uLifetime = pDevice->dwMaxReceiveLifetime;
            pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].wSequence = (pMACHeader->wSeqCtl >> 4);
            pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].wFragNum = (pMACHeader->wSeqCtl & 0x000F);
        }
        else {
            pDevice->uCurrentDFCBIdx = WCTLuInsertDFCB(pDevice, pMACHeader);
            if (pDevice->uCurrentDFCBIdx == pDevice->cbDFCB) {
                return(FALSE);
            }
        }
        // reserve 4 byte to match MAC RX Buffer
        pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].pbyRxBuffer = (PBYTE) (pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].skb->data + 4);
        memcpy(pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].pbyRxBuffer, pMACHeader, cbFrameLength);
        pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].cbFrameLength = cbFrameLength;
        pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].pbyRxBuffer += cbFrameLength;
        pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].wFragNum++;
        //DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO "First pDevice->uCurrentDFCBIdx= %d\n", pDevice->uCurrentDFCBIdx);
        return(FALSE);
    }
    else {
        pDevice->uCurrentDFCBIdx = WCTLuSearchDFCB(pDevice, pMACHeader);
        if (pDevice->uCurrentDFCBIdx != pDevice->cbDFCB) {
            if ((pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].wSequence == (pMACHeader->wSeqCtl >> 4)) &&
                (pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].wFragNum == (pMACHeader->wSeqCtl & 0x000F)) &&
                ((pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].cbFrameLength + cbFrameLength - uHeaderSize) < 2346)) {

                memcpy(pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].pbyRxBuffer, ((PBYTE) (pMACHeader) + uHeaderSize), (cbFrameLength - uHeaderSize));
                pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].cbFrameLength += (cbFrameLength - uHeaderSize);
                pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].pbyRxBuffer += (cbFrameLength - uHeaderSize);
                pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].wFragNum++;
                //DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO "Second pDevice->uCurrentDFCBIdx= %d\n", pDevice->uCurrentDFCBIdx);
            }
            else {
                // seq error or frag # error flush DFCB
                pDevice->cbFreeDFCB++;
                pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].bInUse = FALSE;
                return(FALSE);
            }
        }
        else {
            return(FALSE);
        }
        if (IS_LAST_FRAGMENT_PKT(pMACHeader)) {
            //enq defragcontrolblock
            pDevice->cbFreeDFCB++;
            pDevice->sRxDFCB[pDevice->uCurrentDFCBIdx].bInUse = FALSE;
            //DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO "Last pDevice->uCurrentDFCBIdx= %d\n", pDevice->uCurrentDFCBIdx);
            return(TRUE);
        }
        return(FALSE);
    }
}