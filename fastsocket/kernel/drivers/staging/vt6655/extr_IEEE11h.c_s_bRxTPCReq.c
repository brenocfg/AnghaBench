#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WLAN_FRAME_TPCREP ;
struct TYPE_20__ {int /*<<< orphan*/  pAdapter; scalar_t__ abyCurrentMSRReq; int /*<<< orphan*/  abyCurrBSSID; scalar_t__ pbyMgmtPacketPool; } ;
struct TYPE_19__ {int cbMPDULen; scalar_t__ cbPayloadLen; scalar_t__ p80211Header; } ;
struct TYPE_18__ {int /*<<< orphan*/  byDialogToken; } ;
struct TYPE_15__ {int len; int /*<<< orphan*/  byLinkMargin; int /*<<< orphan*/  byTxPower; int /*<<< orphan*/  byElementID; } ;
struct TYPE_14__ {int wFrameCtl; int /*<<< orphan*/  abyAddr3; int /*<<< orphan*/  abyAddr2; int /*<<< orphan*/  abyAddr1; } ;
struct TYPE_17__ {int byAction; TYPE_3__ sTPCRepEIDs; int /*<<< orphan*/  byDialogToken; scalar_t__ byCategory; TYPE_2__ Header; } ;
struct TYPE_13__ {int /*<<< orphan*/  abyAddr2; } ;
struct TYPE_16__ {TYPE_1__ Header; } ;
typedef  int /*<<< orphan*/  STxMgmtPacket ;
typedef  TYPE_4__* PWLAN_FRAME_TPCREQ ;
typedef  TYPE_5__* PWLAN_FRAME_TPCREP ;
typedef  TYPE_6__* PWLAN_FRAME_MSRREQ ;
typedef  scalar_t__ PUWLAN_80211HDR ;
typedef  TYPE_7__* PSTxMgmtPacket ;
typedef  TYPE_8__* PSMgmtObject ;
typedef  scalar_t__ PBYTE ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbyGetTransmitPower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDpGetCurrentAddress (int /*<<< orphan*/ ) ; 
 scalar_t__ CMD_STATUS_PENDING ; 
 int /*<<< orphan*/  FALSE ; 
#define  RATE_12M 135 
#define  RATE_18M 134 
#define  RATE_24M 133 
#define  RATE_36M 132 
#define  RATE_48M 131 
#define  RATE_54M 130 
#define  RATE_6M 129 
#define  RATE_9M 128 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WLAN_A3FR_MAXLEN ; 
 int /*<<< orphan*/  WLAN_ADDR_LEN ; 
 int /*<<< orphan*/  WLAN_BSSID_LEN ; 
 int /*<<< orphan*/  WLAN_EID_TPC_REP ; 
 int /*<<< orphan*/  WLAN_FSTYPE_ACTION ; 
 int /*<<< orphan*/  WLAN_FTYPE_MGMT ; 
 scalar_t__ WLAN_HDR_ADDR3_LEN ; 
 int WLAN_SET_FC_FSTYPE (int /*<<< orphan*/ ) ; 
 int WLAN_SET_FC_FTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ csMgmt_xmit (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL s_bRxTPCReq(PSMgmtObject pMgmt, PWLAN_FRAME_TPCREQ pTPCReq, BYTE byRate, BYTE byRSSI)
{
    PWLAN_FRAME_TPCREP  pFrame;
    PSTxMgmtPacket      pTxPacket = NULL;


    pTxPacket = (PSTxMgmtPacket)pMgmt->pbyMgmtPacketPool;
    memset(pTxPacket, 0, sizeof(STxMgmtPacket) + WLAN_A3FR_MAXLEN);
    pTxPacket->p80211Header = (PUWLAN_80211HDR)((PBYTE)pTxPacket + sizeof(STxMgmtPacket));

    pFrame = (PWLAN_FRAME_TPCREP)((PBYTE)pTxPacket + sizeof(STxMgmtPacket));

    pFrame->Header.wFrameCtl = (   WLAN_SET_FC_FTYPE(WLAN_FTYPE_MGMT) |
                                    WLAN_SET_FC_FSTYPE(WLAN_FSTYPE_ACTION)
                                );

    memcpy( pFrame->Header.abyAddr1, pTPCReq->Header.abyAddr2, WLAN_ADDR_LEN);
    memcpy( pFrame->Header.abyAddr2, CARDpGetCurrentAddress(pMgmt->pAdapter), WLAN_ADDR_LEN);
    memcpy( pFrame->Header.abyAddr3, pMgmt->abyCurrBSSID, WLAN_BSSID_LEN);

    pFrame->byCategory = 0;
    pFrame->byAction = 3;
    pFrame->byDialogToken = ((PWLAN_FRAME_MSRREQ) (pMgmt->abyCurrentMSRReq))->byDialogToken;

    pFrame->sTPCRepEIDs.byElementID = WLAN_EID_TPC_REP;
    pFrame->sTPCRepEIDs.len = 2;
    pFrame->sTPCRepEIDs.byTxPower = CARDbyGetTransmitPower(pMgmt->pAdapter);
    switch (byRate) {
        case RATE_54M:
            pFrame->sTPCRepEIDs.byLinkMargin = 65 - byRSSI;
            break;
        case RATE_48M:
            pFrame->sTPCRepEIDs.byLinkMargin = 66 - byRSSI;
            break;
        case RATE_36M:
            pFrame->sTPCRepEIDs.byLinkMargin = 70 - byRSSI;
            break;
        case RATE_24M:
            pFrame->sTPCRepEIDs.byLinkMargin = 74 - byRSSI;
            break;
        case RATE_18M:
            pFrame->sTPCRepEIDs.byLinkMargin = 77 - byRSSI;
            break;
        case RATE_12M:
            pFrame->sTPCRepEIDs.byLinkMargin = 79 - byRSSI;
            break;
        case RATE_9M:
            pFrame->sTPCRepEIDs.byLinkMargin = 81 - byRSSI;
            break;
        case RATE_6M:
        default:
            pFrame->sTPCRepEIDs.byLinkMargin = 82 - byRSSI;
            break;
    }

    pTxPacket->cbMPDULen = sizeof(WLAN_FRAME_TPCREP);
    pTxPacket->cbPayloadLen = sizeof(WLAN_FRAME_TPCREP) - WLAN_HDR_ADDR3_LEN;
    if (csMgmt_xmit(pMgmt->pAdapter, pTxPacket) != CMD_STATUS_PENDING)
        return (FALSE);
    return (TRUE);
//    return (CARDbSendPacket(pMgmt->pAdapter, pFrame, PKT_TYPE_802_11_MNG, sizeof(WLAN_FRAME_TPCREP)));

}