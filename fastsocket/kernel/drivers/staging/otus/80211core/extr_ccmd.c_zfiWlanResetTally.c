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
struct TYPE_3__ {scalar_t__ rxOFDMDataFrame; scalar_t__ rx11bDataFrame; scalar_t__ Hw_RxPhyTotalCount; scalar_t__ Hw_RxPhyHTError; scalar_t__ Hw_RxPhyCCKError; scalar_t__ Hw_RxPhyOFDMError; scalar_t__ Hw_RxPhyXRError; scalar_t__ Hw_RxPhyMiscError; scalar_t__ Hw_RxDelMPDU; scalar_t__ Hw_RxDropMPDU; scalar_t__ Hw_RxMPDU; scalar_t__* txQosDropCount; scalar_t__ Hw_Tx_MPDU; scalar_t__ Hw_Tx_AMPDU; scalar_t__ BA_Fail; scalar_t__ Tx_MPDU; scalar_t__ LossAP; scalar_t__ Hw_RxTimeOut; scalar_t__ Hw_RxFIFOOverrun; scalar_t__ Hw_DecrypErr_Mul; scalar_t__ Hw_DecrypErr_UNI; scalar_t__ Hw_CRC32Cnt; scalar_t__ Hw_CRC16Cnt; scalar_t__ Hw_TotalRxFrm; scalar_t__ rxBroadcastOctets; scalar_t__ rxBroadcastFrm; scalar_t__ DriverRxMgtFrmCnt; scalar_t__ rxNeedFrgFrm; scalar_t__ DriverDiscardedFrmCauseByFrmCtrl; scalar_t__ DriverDiscardedFrmCauseByMulticastList; scalar_t__ GreaterThanMaxLen; scalar_t__ LessThanDataMinLen; scalar_t__ DriverDiscardedFrm; scalar_t__ rxMulticastOctets; scalar_t__ rxUnicastOctets; scalar_t__ NotifyNDISRxFrmCnt; scalar_t__ rxMulticastFrm; scalar_t__ rxUnicastFrm; scalar_t__ DriverRxFrmCnt; scalar_t__ Hw_UnderrunCnt; scalar_t__ Hw_RetryCnt; scalar_t__ Hw_TotalTxFrm; scalar_t__ RetryFailCnt; scalar_t__ txFrmDrvMgt; scalar_t__ txFrmUpperNDIS; scalar_t__ txMulticastOctets; scalar_t__ txUnicastOctets; scalar_t__ txMulticastFrm; scalar_t__ txUnicastFrm; } ;
struct TYPE_4__ {TYPE_1__ commTally; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanResetTally(zdev_t *dev)
{
	zmw_get_wlan_dev(dev);

	zmw_declare_for_critical_section();

	zmw_enter_critical_section(dev);

	wd->commTally.txUnicastFrm = 0;		/* txUnicastFrames */
	wd->commTally.txMulticastFrm = 0;	/* txMulticastFrames */
	wd->commTally.txUnicastOctets = 0;	/* txUniOctets  byte size */
	wd->commTally.txMulticastOctets = 0;	/* txMultiOctets  byte size */
	wd->commTally.txFrmUpperNDIS = 0;
	wd->commTally.txFrmDrvMgt = 0;
	wd->commTally.RetryFailCnt = 0;
	wd->commTally.Hw_TotalTxFrm = 0;	/* Hardware total Tx Frame */
	wd->commTally.Hw_RetryCnt = 0;		/* txMultipleRetriesFrames */
	wd->commTally.Hw_UnderrunCnt = 0;
	wd->commTally.DriverRxFrmCnt = 0;
	wd->commTally.rxUnicastFrm = 0;		/* rxUnicastFrames */
	wd->commTally.rxMulticastFrm = 0;	/* rxMulticastFrames */
	wd->commTally.NotifyNDISRxFrmCnt = 0;
	wd->commTally.rxUnicastOctets = 0;	/* rxUniOctets  byte size */
	wd->commTally.rxMulticastOctets = 0;	/* rxMultiOctets  byte size */
	wd->commTally.DriverDiscardedFrm = 0;	/* Discard by ValidateFrame */
	wd->commTally.LessThanDataMinLen = 0;
	wd->commTally.GreaterThanMaxLen = 0;
	wd->commTally.DriverDiscardedFrmCauseByMulticastList = 0;
	wd->commTally.DriverDiscardedFrmCauseByFrmCtrl = 0;
	wd->commTally.rxNeedFrgFrm = 0;		/* need more frg frm */
	wd->commTally.DriverRxMgtFrmCnt = 0;
	wd->commTally.rxBroadcastFrm = 0;/* Receive broadcast frame count */
	wd->commTally.rxBroadcastOctets = 0;/*Receive broadcast framebyte size*/
	wd->commTally.Hw_TotalRxFrm = 0;
	wd->commTally.Hw_CRC16Cnt = 0;		/* rxPLCPCRCErrCnt */
	wd->commTally.Hw_CRC32Cnt = 0;		/* rxCRC32ErrCnt */
	wd->commTally.Hw_DecrypErr_UNI = 0;
	wd->commTally.Hw_DecrypErr_Mul = 0;
	wd->commTally.Hw_RxFIFOOverrun = 0;
	wd->commTally.Hw_RxTimeOut = 0;
	wd->commTally.LossAP = 0;

	wd->commTally.Tx_MPDU = 0;
	wd->commTally.BA_Fail = 0;
	wd->commTally.Hw_Tx_AMPDU = 0;
	wd->commTally.Hw_Tx_MPDU = 0;

	wd->commTally.txQosDropCount[0] = 0;
	wd->commTally.txQosDropCount[1] = 0;
	wd->commTally.txQosDropCount[2] = 0;
	wd->commTally.txQosDropCount[3] = 0;
	wd->commTally.txQosDropCount[4] = 0;

	wd->commTally.Hw_RxMPDU = 0;
	wd->commTally.Hw_RxDropMPDU = 0;
	wd->commTally.Hw_RxDelMPDU = 0;

	wd->commTally.Hw_RxPhyMiscError = 0;
	wd->commTally.Hw_RxPhyXRError = 0;
	wd->commTally.Hw_RxPhyOFDMError = 0;
	wd->commTally.Hw_RxPhyCCKError = 0;
	wd->commTally.Hw_RxPhyHTError = 0;
	wd->commTally.Hw_RxPhyTotalCount = 0;

#if (defined(GCCK) && defined(OFDM))
	wd->commTally.rx11bDataFrame = 0;
	wd->commTally.rxOFDMDataFrame = 0;
#endif

	zmw_leave_critical_section(dev);
}