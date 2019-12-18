#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_20__ {TYPE_3__* pTSBuf; } ;
struct TYPE_23__ {int /*<<< orphan*/  rawEKey; int /*<<< orphan*/  rawSKey; TYPE_4__ runtimeEnv; } ;
struct TYPE_17__ {int /*<<< orphan*/  order; } ;
struct TYPE_21__ {TYPE_1__ order; } ;
struct TYPE_22__ {TYPE_5__ query; TYPE_7__* pMeterQuerySupporter; } ;
struct TYPE_18__ {int order; } ;
struct TYPE_19__ {TYPE_2__ cur; } ;
typedef  TYPE_4__ SQueryRuntimeEnv ;
typedef  TYPE_5__ SQuery ;
typedef  TYPE_6__ SQInfo ;
typedef  TYPE_7__ SMeterQuerySupportObj ;

/* Variables and functions */
 int /*<<< orphan*/  SET_MASTER_SCAN_FLAG (TYPE_4__*) ; 
 int /*<<< orphan*/  SET_SUPPLEMENT_SCAN_FLAG (TYPE_4__*) ; 
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSKEY ; 
 int /*<<< orphan*/  dTrace (char*,TYPE_6__*,...) ; 
 int /*<<< orphan*/  disableFunctForSuppleScan (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doOrderedScan (TYPE_6__*) ; 
 int /*<<< orphan*/  enableFunctForMasterScan (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  needSupplementaryScan (TYPE_5__*) ; 
 int /*<<< orphan*/  setupMeterQueryInfoForSupplementQuery (TYPE_7__*) ; 
 scalar_t__ taosGetTimestampMs () ; 

__attribute__((used)) static void doMultiMeterSupplementaryScan(SQInfo *pQInfo) {
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;

  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = &pQInfo->query;

  if (!needSupplementaryScan(pQuery)) {
    dTrace("QInfo:%p no need to do supplementary scan, query completed", pQInfo);
    return;
  }

  SET_SUPPLEMENT_SCAN_FLAG(pRuntimeEnv);
  disableFunctForSuppleScan(pRuntimeEnv, pQuery->order.order);

  if (pRuntimeEnv->pTSBuf != NULL) {
    pRuntimeEnv->pTSBuf->cur.order = pRuntimeEnv->pTSBuf->cur.order ^ 1;
  }

  SWAP(pSupporter->rawSKey, pSupporter->rawEKey, TSKEY);
  setupMeterQueryInfoForSupplementQuery(pSupporter);

  int64_t st = taosGetTimestampMs();
  doOrderedScan(pQInfo);
  int64_t et = taosGetTimestampMs();
  dTrace("QInfo:%p supplementary scan completed, elapsed time: %lldms", pQInfo, et - st);

  /*
   * restore the env
   * the meter query info is not reset to the original state
   */
  SWAP(pSupporter->rawSKey, pSupporter->rawEKey, TSKEY);
  enableFunctForMasterScan(pRuntimeEnv, pQuery->order.order);

  if (pRuntimeEnv->pTSBuf != NULL) {
    pRuntimeEnv->pTSBuf->cur.order = pRuntimeEnv->pTSBuf->cur.order ^ 1;
  }

  SET_MASTER_SCAN_FLAG(pRuntimeEnv);
}