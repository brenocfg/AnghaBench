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
struct ipath_devdata {int ipath_flags; int /*<<< orphan*/  ipath_lli_errors; int /*<<< orphan*/  ipath_lli_errs; int /*<<< orphan*/  ipath_overrun_thresh_errs; } ;
struct infinipath_counters {scalar_t__ RxDlidFltrCnt; scalar_t__ RxVlErrCnt; int /*<<< orphan*/  LocalLinkIntegrityErrCnt; int /*<<< orphan*/  ExcessBufferOvflCnt; scalar_t__ PcieRetryBufDiagQwordCnt; scalar_t__ RxOtherLocalPhyErrCnt; scalar_t__ RxVL15DroppedPktCnt; void* IBSymbolErrCnt; void* IBLinkDownedCnt; void* IBLinkErrRecoveryCnt; void* IBStatusChangeCnt; scalar_t__ RxP16HdrEgrOvflCnt; scalar_t__ RxP15HdrEgrOvflCnt; scalar_t__ RxP14HdrEgrOvflCnt; scalar_t__ RxP13HdrEgrOvflCnt; scalar_t__ RxP12HdrEgrOvflCnt; scalar_t__ RxP11HdrEgrOvflCnt; scalar_t__ RxP10HdrEgrOvflCnt; scalar_t__ RxP9HdrEgrOvflCnt; void* RxP8HdrEgrOvflCnt; void* RxP7HdrEgrOvflCnt; void* RxP6HdrEgrOvflCnt; void* RxP5HdrEgrOvflCnt; void* RxP4HdrEgrOvflCnt; void* RxP3HdrEgrOvflCnt; void* RxP2HdrEgrOvflCnt; void* RxP1HdrEgrOvflCnt; void* RxP0HdrEgrOvflCnt; void* RxPKeyMismatchCnt; void* RxTIDValidErrCnt; void* RxTIDFullErrCnt; void* RxBufOvflCnt; void* RxLPCRCErrCnt; void* RxEBPCnt; void* RxLinkProblemCnt; void* RxBadFormatCnt; void* RxFlowCtrlErrCnt; void* RxVCRCErrCnt; void* RxICRCErrCnt; void* RxMaxMinLenErrCnt; void* RxLenErrCnt; void* RxDwordCnt; void* RxFlowPktCnt; void* RxDataPktCnt; void* RxDroppedPktCnt; void* TxDroppedPktCnt; void* TxFlowStallCnt; void* TxUnderrunCnt; void* TxMaxMinLenErrCnt; void* TxLenErrCnt; void* TxDwordCnt; void* TxFlowPktCnt; void* TxDataPktCnt; void* TxUnsupVLErrCnt; scalar_t__ TxSDmaDescCnt; void* LBFlowStallCnt; void* LBIntCnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBLinkDownedCnt ; 
 int /*<<< orphan*/  IBLinkErrRecoveryCnt ; 
 int /*<<< orphan*/  IBStatusChangeCnt ; 
 int /*<<< orphan*/  IBSymbolErrCnt ; 
 int /*<<< orphan*/  IPATH_CREG_OFFSET (int /*<<< orphan*/ ) ; 
 int IPATH_GPIO_ERRINTRS ; 
 int /*<<< orphan*/  LBFlowStallCnt ; 
 int /*<<< orphan*/  LBIntCnt ; 
 int /*<<< orphan*/  RxBadFormatCnt ; 
 int /*<<< orphan*/  RxBufOvflCnt ; 
 int /*<<< orphan*/  RxDataPktCnt ; 
 int /*<<< orphan*/  RxDroppedPktCnt ; 
 int /*<<< orphan*/  RxDwordCnt ; 
 int /*<<< orphan*/  RxEBPCnt ; 
 int /*<<< orphan*/  RxFlowCtrlErrCnt ; 
 int /*<<< orphan*/  RxFlowPktCnt ; 
 int /*<<< orphan*/  RxICRCErrCnt ; 
 int /*<<< orphan*/  RxLPCRCErrCnt ; 
 int /*<<< orphan*/  RxLenErrCnt ; 
 int /*<<< orphan*/  RxLinkProblemCnt ; 
 int /*<<< orphan*/  RxMaxMinLenErrCnt ; 
 int /*<<< orphan*/  RxP0HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP1HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP2HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP3HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP4HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP5HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP6HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP7HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxP8HdrEgrOvflCnt ; 
 int /*<<< orphan*/  RxPKeyMismatchCnt ; 
 int /*<<< orphan*/  RxTIDFullErrCnt ; 
 int /*<<< orphan*/  RxTIDValidErrCnt ; 
 int /*<<< orphan*/  RxVCRCErrCnt ; 
 int /*<<< orphan*/  TxDataPktCnt ; 
 int /*<<< orphan*/  TxDroppedPktCnt ; 
 int /*<<< orphan*/  TxDwordCnt ; 
 int /*<<< orphan*/  TxFlowPktCnt ; 
 int /*<<< orphan*/  TxFlowStallCnt ; 
 int /*<<< orphan*/  TxLenErrCnt ; 
 int /*<<< orphan*/  TxMaxMinLenErrCnt ; 
 int /*<<< orphan*/  TxUnderrunCnt ; 
 int /*<<< orphan*/  TxUnsupVLErrCnt ; 
 void* ipath_snap_cntr (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipath_ht_read_counters(struct ipath_devdata *dd,
				   struct infinipath_counters *cntrs)
{
	cntrs->LBIntCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(LBIntCnt));
	cntrs->LBFlowStallCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(LBFlowStallCnt));
	cntrs->TxSDmaDescCnt = 0;
	cntrs->TxUnsupVLErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxUnsupVLErrCnt));
	cntrs->TxDataPktCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxDataPktCnt));
	cntrs->TxFlowPktCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxFlowPktCnt));
	cntrs->TxDwordCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxDwordCnt));
	cntrs->TxLenErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxLenErrCnt));
	cntrs->TxMaxMinLenErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxMaxMinLenErrCnt));
	cntrs->TxUnderrunCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxUnderrunCnt));
	cntrs->TxFlowStallCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxFlowStallCnt));
	cntrs->TxDroppedPktCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(TxDroppedPktCnt));
	cntrs->RxDroppedPktCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxDroppedPktCnt));
	cntrs->RxDataPktCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxDataPktCnt));
	cntrs->RxFlowPktCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxFlowPktCnt));
	cntrs->RxDwordCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxDwordCnt));
	cntrs->RxLenErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxLenErrCnt));
	cntrs->RxMaxMinLenErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxMaxMinLenErrCnt));
	cntrs->RxICRCErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxICRCErrCnt));
	cntrs->RxVCRCErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxVCRCErrCnt));
	cntrs->RxFlowCtrlErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxFlowCtrlErrCnt));
	cntrs->RxBadFormatCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxBadFormatCnt));
	cntrs->RxLinkProblemCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxLinkProblemCnt));
	cntrs->RxEBPCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxEBPCnt));
	cntrs->RxLPCRCErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxLPCRCErrCnt));
	cntrs->RxBufOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxBufOvflCnt));
	cntrs->RxTIDFullErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxTIDFullErrCnt));
	cntrs->RxTIDValidErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxTIDValidErrCnt));
	cntrs->RxPKeyMismatchCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxPKeyMismatchCnt));
	cntrs->RxP0HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP0HdrEgrOvflCnt));
	cntrs->RxP1HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP1HdrEgrOvflCnt));
	cntrs->RxP2HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP2HdrEgrOvflCnt));
	cntrs->RxP3HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP3HdrEgrOvflCnt));
	cntrs->RxP4HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP4HdrEgrOvflCnt));
	cntrs->RxP5HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP5HdrEgrOvflCnt));
	cntrs->RxP6HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP6HdrEgrOvflCnt));
	cntrs->RxP7HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP7HdrEgrOvflCnt));
	cntrs->RxP8HdrEgrOvflCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(RxP8HdrEgrOvflCnt));
	cntrs->RxP9HdrEgrOvflCnt = 0;
	cntrs->RxP10HdrEgrOvflCnt = 0;
	cntrs->RxP11HdrEgrOvflCnt = 0;
	cntrs->RxP12HdrEgrOvflCnt = 0;
	cntrs->RxP13HdrEgrOvflCnt = 0;
	cntrs->RxP14HdrEgrOvflCnt = 0;
	cntrs->RxP15HdrEgrOvflCnt = 0;
	cntrs->RxP16HdrEgrOvflCnt = 0;
	cntrs->IBStatusChangeCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(IBStatusChangeCnt));
	cntrs->IBLinkErrRecoveryCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(IBLinkErrRecoveryCnt));
	cntrs->IBLinkDownedCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(IBLinkDownedCnt));
	cntrs->IBSymbolErrCnt =
		ipath_snap_cntr(dd, IPATH_CREG_OFFSET(IBSymbolErrCnt));
	cntrs->RxVL15DroppedPktCnt = 0;
	cntrs->RxOtherLocalPhyErrCnt = 0;
	cntrs->PcieRetryBufDiagQwordCnt = 0;
	cntrs->ExcessBufferOvflCnt = dd->ipath_overrun_thresh_errs;
	cntrs->LocalLinkIntegrityErrCnt =
		(dd->ipath_flags & IPATH_GPIO_ERRINTRS) ?
		dd->ipath_lli_errs : dd->ipath_lli_errors;
	cntrs->RxVlErrCnt = 0;
	cntrs->RxDlidFltrCnt = 0;
}