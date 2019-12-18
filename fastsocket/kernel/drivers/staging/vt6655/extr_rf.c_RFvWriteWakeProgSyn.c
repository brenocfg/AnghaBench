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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CB_AL2230_INIT_SEQ ; 
 int CB_AL7230_INIT_SEQ ; 
 int /*<<< orphan*/  CB_MAX_CHANNEL_24G ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAC_REG_MISCFFNDEX ; 
 int /*<<< orphan*/  MACvSetMISCFifo (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAKEWORD (int,int) ; 
 int MISCFIFO_SYNDATASIZE ; 
 int /*<<< orphan*/  MISCFIFO_SYNDATA_IDX ; 
 int /*<<< orphan*/  MISCFIFO_SYNINFO_IDX ; 
#define  RF_AIROHA 131 
#define  RF_AIROHA7230 130 
#define  RF_AL2230S 129 
#define  RF_NOTHING 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dwAL2230ChannelTable0 ; 
 int /*<<< orphan*/ * dwAL2230ChannelTable1 ; 
 int /*<<< orphan*/ * dwAL2230InitTable ; 
 int /*<<< orphan*/ * dwAL7230ChannelTable0 ; 
 int /*<<< orphan*/ * dwAL7230ChannelTable1 ; 
 int /*<<< orphan*/ * dwAL7230ChannelTable2 ; 
 int /*<<< orphan*/ * dwAL7230InitTable ; 
 int /*<<< orphan*/ * dwAL7230InitTableAMode ; 

BOOL RFvWriteWakeProgSyn (DWORD_PTR dwIoBase, BYTE byRFType, UINT uChannel)
{
    int   ii;
    BYTE  byInitCount = 0;
    BYTE  bySleepCount = 0;

    VNSvOutPortW(dwIoBase + MAC_REG_MISCFFNDEX, 0);
    switch (byRFType) {
        case RF_AIROHA:
        case RF_AL2230S:

            if (uChannel > CB_MAX_CHANNEL_24G)
                return FALSE;

            byInitCount = CB_AL2230_INIT_SEQ + 2; // Init Reg + Channel Reg (2)
            bySleepCount = 0;
            if (byInitCount > (MISCFIFO_SYNDATASIZE - bySleepCount)) {
                return FALSE;
            }

            for (ii = 0; ii < CB_AL2230_INIT_SEQ; ii++ ) {
                MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL2230InitTable[ii]);
            }
            MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL2230ChannelTable0[uChannel-1]);
            ii ++;
            MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL2230ChannelTable1[uChannel-1]);
            break;

        //{{ RobertYu: 20050104
        // Need to check, PLLON need to be low for channel setting
        case RF_AIROHA7230:
            byInitCount = CB_AL7230_INIT_SEQ + 3; // Init Reg + Channel Reg (3)
            bySleepCount = 0;
            if (byInitCount > (MISCFIFO_SYNDATASIZE - bySleepCount)) {
                return FALSE;
            }

            if (uChannel <= CB_MAX_CHANNEL_24G)
            {
                for (ii = 0; ii < CB_AL7230_INIT_SEQ; ii++ ) {
                    MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230InitTable[ii]);
                }
            }
            else
            {
                for (ii = 0; ii < CB_AL7230_INIT_SEQ; ii++ ) {
                    MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230InitTableAMode[ii]);
                }
            }

            MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230ChannelTable0[uChannel-1]);
            ii ++;
            MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230ChannelTable1[uChannel-1]);
            ii ++;
            MACvSetMISCFifo(dwIoBase, (WORD)(MISCFIFO_SYNDATA_IDX + ii), dwAL7230ChannelTable2[uChannel-1]);
            break;
        //}} RobertYu

        case RF_NOTHING :
            return TRUE;
            break;

        default:
            return FALSE;
            break;
    }

    MACvSetMISCFifo(dwIoBase, MISCFIFO_SYNINFO_IDX, (DWORD)MAKEWORD(bySleepCount, byInitCount));

    return TRUE;
}