#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t WORD ;
typedef  size_t UINT ;
struct TYPE_16__ {void* wSeqCtl; scalar_t__ wDurationID; } ;
struct TYPE_15__ {scalar_t__ eCurrentPHYType; int byPreambleType; int wSeqCounter; size_t wBCNBufLen; int /*<<< orphan*/  PortOffset; int /*<<< orphan*/  tx_beacon_dma; scalar_t__ tx_beacon_bufs; } ;
struct TYPE_14__ {void* wTimeStampOff; void* wTransmitLength; int /*<<< orphan*/  bySignalField; int /*<<< orphan*/  byServiceField; void* wDuration; } ;
struct TYPE_13__ {size_t cbMPDULen; int /*<<< orphan*/  p80211Header; } ;
struct TYPE_12__ {int /*<<< orphan*/  wFIFOCtl; } ;
typedef  int /*<<< orphan*/  STxShortBufHead ;
typedef  int /*<<< orphan*/  STxDataHead_ab ;
typedef  int /*<<< orphan*/  PWORD ;
typedef  TYPE_1__* PSTxShortBufHead ;
typedef  TYPE_2__* PSTxMgmtPacket ;
typedef  TYPE_3__* PSTxDataHead_ab ;
typedef  TYPE_4__* PSDevice ;
typedef  TYPE_5__* PS802_11Header ;
typedef  size_t PBYTE ;
typedef  int /*<<< orphan*/  CMD_STATUS ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_FB_NONE ; 
 int /*<<< orphan*/  BBvCaculateParameter (TYPE_4__*,size_t,size_t,scalar_t__,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  CMD_STATUS_PENDING ; 
 int /*<<< orphan*/  DATADUR_A ; 
 int /*<<< orphan*/  DATADUR_B ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIFOCTL_11B ; 
 int /*<<< orphan*/  FIFOCTL_GENINT ; 
 int /*<<< orphan*/  MAC_REG_TCR ; 
 int /*<<< orphan*/  MACvRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSetCurrBCNLength (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MACvSetCurrBCNTxDescAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvTransmitBCN (int /*<<< orphan*/ ) ; 
 size_t MAX_RATE ; 
 scalar_t__ PHY_TYPE_11A ; 
 scalar_t__ PK_TYPE_11A ; 
 scalar_t__ PK_TYPE_11B ; 
 int PREAMBLE_LONG ; 
 size_t RATE_2M ; 
 size_t RATE_6M ; 
 int /*<<< orphan*/  TCR_AUTOBCNTX ; 
 size_t WLAN_FCS_LEN ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ s_uGetDataDuration (TYPE_4__*,int /*<<< orphan*/ ,size_t,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int** wTimeStampOff ; 

CMD_STATUS csBeacon_xmit(PSDevice pDevice, PSTxMgmtPacket pPacket) {

    BYTE             byPktType;
    PBYTE            pbyBuffer = (PBYTE)pDevice->tx_beacon_bufs;
    UINT             cbFrameSize = pPacket->cbMPDULen + WLAN_FCS_LEN;
    UINT             cbHeaderSize = 0;
    WORD             wTxBufSize = sizeof(STxShortBufHead);
    PSTxShortBufHead pTxBufHead = (PSTxShortBufHead) pbyBuffer;
    PSTxDataHead_ab  pTxDataHead = (PSTxDataHead_ab) (pbyBuffer + wTxBufSize);
    PS802_11Header   pMACHeader;
    WORD             wCurrentRate;
    WORD             wLen = 0x0000;


    memset(pTxBufHead, 0, wTxBufSize);

    if (pDevice->eCurrentPHYType == PHY_TYPE_11A) {
        wCurrentRate = RATE_6M;
        byPktType = PK_TYPE_11A;
    } else {
        wCurrentRate = RATE_2M;
        byPktType = PK_TYPE_11B;
    }

    //Set Preamble type always long
    pDevice->byPreambleType = PREAMBLE_LONG;

    //Set FIFOCTL_GENINT

    pTxBufHead->wFIFOCtl |= FIFOCTL_GENINT;


    //Set packet type & Get Duration
    if (byPktType == PK_TYPE_11A) {//0000 0000 0000 0000
        pTxDataHead->wDuration = cpu_to_le16((WORD)s_uGetDataDuration(pDevice, DATADUR_A, cbFrameSize, byPktType,
                                                          wCurrentRate, FALSE, 0, 0, 1, AUTO_FB_NONE));
    }
    else if (byPktType == PK_TYPE_11B) {//0000 0001 0000 0000
        pTxBufHead->wFIFOCtl |= FIFOCTL_11B;
        pTxDataHead->wDuration = cpu_to_le16((WORD)s_uGetDataDuration(pDevice, DATADUR_B, cbFrameSize, byPktType,
                                                          wCurrentRate, FALSE, 0, 0, 1, AUTO_FB_NONE));
    }

    BBvCaculateParameter(pDevice, cbFrameSize, wCurrentRate, byPktType,
        (PWORD)&(wLen), (PBYTE)&(pTxDataHead->byServiceField), (PBYTE)&(pTxDataHead->bySignalField)
    );
    pTxDataHead->wTransmitLength = cpu_to_le16(wLen);
    //Get TimeStampOff
    pTxDataHead->wTimeStampOff = cpu_to_le16(wTimeStampOff[pDevice->byPreambleType%2][wCurrentRate%MAX_RATE]);
    cbHeaderSize = wTxBufSize + sizeof(STxDataHead_ab);

   //Generate Beacon Header
    pMACHeader = (PS802_11Header)(pbyBuffer + cbHeaderSize);
    memcpy(pMACHeader, pPacket->p80211Header, pPacket->cbMPDULen);

    pMACHeader->wDurationID = 0;
    pMACHeader->wSeqCtl = cpu_to_le16(pDevice->wSeqCounter << 4);
    pDevice->wSeqCounter++ ;
    if (pDevice->wSeqCounter > 0x0fff)
        pDevice->wSeqCounter = 0;

    // Set Beacon buffer length
    pDevice->wBCNBufLen = pPacket->cbMPDULen + cbHeaderSize;

    MACvSetCurrBCNTxDescAddr(pDevice->PortOffset, (pDevice->tx_beacon_dma));

    MACvSetCurrBCNLength(pDevice->PortOffset, pDevice->wBCNBufLen);
    // Set auto Transmit on
    MACvRegBitsOn(pDevice->PortOffset, MAC_REG_TCR, TCR_AUTOBCNTX);
    // Poll Transmit the adapter
    MACvTransmitBCN(pDevice->PortOffset);

    return CMD_STATUS_PENDING;
}