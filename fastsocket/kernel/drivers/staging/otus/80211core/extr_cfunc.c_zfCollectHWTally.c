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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;
struct TYPE_3__ {int Hw_UnderrunCnt; int Hw_TotalRxFrm; int Hw_CRC32Cnt; int Hw_CRC16Cnt; int Hw_DecrypErr_UNI; int Hw_RxFIFOOverrun; int Hw_DecrypErr_Mul; int Hw_RetryCnt; int Hw_TotalTxFrm; int Hw_RxTimeOut; int Tx_MPDU; int BA_Fail; int Hw_Tx_AMPDU; int Hw_Tx_MPDU; int RateCtrlTxMPDU; int RateCtrlBAFail; int Hw_RxMPDU; int Hw_RxDropMPDU; int Hw_RxDelMPDU; int Hw_RxPhyMiscError; int Hw_RxPhyXRError; int Hw_RxPhyOFDMError; int Hw_RxPhyCCKError; int Hw_RxPhyHTError; int Hw_RxPhyTotalCount; } ;
struct TYPE_4__ {TYPE_1__ commTally; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_1 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zm_msg1_mm (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfCollectHWTally(zdev_t*dev, u32_t* rsp, u8_t id)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if (id == 0)
    {
        wd->commTally.Hw_UnderrunCnt += (0xFFFF & rsp[1]);
        wd->commTally.Hw_TotalRxFrm += rsp[2];
        wd->commTally.Hw_CRC32Cnt += rsp[3];
        wd->commTally.Hw_CRC16Cnt += rsp[4];
        #ifdef ZM_ENABLE_NATIVE_WIFI
        /* These code are here to satisfy Vista DTM */
        wd->commTally.Hw_DecrypErr_UNI += ((rsp[5]>50) && (rsp[5]<60))?50:rsp[5];
        #else
        wd->commTally.Hw_DecrypErr_UNI += rsp[5];
        #endif
        wd->commTally.Hw_RxFIFOOverrun += rsp[6];
        wd->commTally.Hw_DecrypErr_Mul += rsp[7];
        wd->commTally.Hw_RetryCnt += rsp[8];
        wd->commTally.Hw_TotalTxFrm += rsp[9];
        wd->commTally.Hw_RxTimeOut +=rsp[10];

        wd->commTally.Tx_MPDU += rsp[11];
        wd->commTally.BA_Fail += rsp[12];
        wd->commTally.Hw_Tx_AMPDU += rsp[13];
        wd->commTally.Hw_Tx_MPDU += rsp[14];
        wd->commTally.RateCtrlTxMPDU += rsp[11];
        wd->commTally.RateCtrlBAFail += rsp[12];
    }
    else
    {
        wd->commTally.Hw_RxMPDU += rsp[1];
        wd->commTally.Hw_RxDropMPDU += rsp[2];
        wd->commTally.Hw_RxDelMPDU += rsp[3];

        wd->commTally.Hw_RxPhyMiscError += rsp[4];
        wd->commTally.Hw_RxPhyXRError += rsp[5];
        wd->commTally.Hw_RxPhyOFDMError += rsp[6];
        wd->commTally.Hw_RxPhyCCKError += rsp[7];
        wd->commTally.Hw_RxPhyHTError += rsp[8];
        wd->commTally.Hw_RxPhyTotalCount += rsp[9];
    }

    zmw_leave_critical_section(dev);

    if (id == 0)
    {
        zm_msg1_mm(ZM_LV_1, "rsplen =", rsp[0]);
        zm_msg1_mm(ZM_LV_1, "Hw_UnderrunCnt    = ", (0xFFFF & rsp[1]));
        zm_msg1_mm(ZM_LV_1, "Hw_TotalRxFrm     = ", rsp[2]);
        zm_msg1_mm(ZM_LV_1, "Hw_CRC32Cnt       = ", rsp[3]);
        zm_msg1_mm(ZM_LV_1, "Hw_CRC16Cnt       = ", rsp[4]);
        zm_msg1_mm(ZM_LV_1, "Hw_DecrypErr_UNI  = ", rsp[5]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxFIFOOverrun  = ", rsp[6]);
        zm_msg1_mm(ZM_LV_1, "Hw_DecrypErr_Mul  = ", rsp[7]);
        zm_msg1_mm(ZM_LV_1, "Hw_RetryCnt       = ", rsp[8]);
        zm_msg1_mm(ZM_LV_1, "Hw_TotalTxFrm     = ", rsp[9]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxTimeOut      = ", rsp[10]);
        zm_msg1_mm(ZM_LV_1, "Tx_MPDU           = ", rsp[11]);
        zm_msg1_mm(ZM_LV_1, "BA_Fail           = ", rsp[12]);
        zm_msg1_mm(ZM_LV_1, "Hw_Tx_AMPDU       = ", rsp[13]);
        zm_msg1_mm(ZM_LV_1, "Hw_Tx_MPDU        = ", rsp[14]);
    }
    else
    {
        zm_msg1_mm(ZM_LV_1, "rsplen             = ", rsp[0]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxMPDU          = ", (0xFFFF & rsp[1]));
        zm_msg1_mm(ZM_LV_1, "Hw_RxDropMPDU      = ", rsp[2]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxDelMPDU       = ", rsp[3]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxPhyMiscError  = ", rsp[4]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxPhyXRError    = ", rsp[5]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxPhyOFDMError  = ", rsp[6]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxPhyCCKError   = ", rsp[7]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxPhyHTError    = ", rsp[8]);
        zm_msg1_mm(ZM_LV_1, "Hw_RxPhyTotalCount = ", rsp[9]);
    }

}