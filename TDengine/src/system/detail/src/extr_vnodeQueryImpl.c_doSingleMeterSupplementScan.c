#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  order; } ;
struct TYPE_21__ {scalar_t__ ekey; scalar_t__ skey; TYPE_1__ order; } ;
struct TYPE_20__ {int /*<<< orphan*/  startPos; int /*<<< orphan*/  endPos; TYPE_4__* pQuery; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_2__ SQueryStatus ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_4__*) ; 
 int /*<<< orphan*/  SET_MASTER_SCAN_FLAG (TYPE_3__*) ; 
 int /*<<< orphan*/  SET_SUPPLEMENT_SCAN_FLAG (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disableFunctForSuppleScan (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doScanAllDataBlocks (TYPE_3__*) ; 
 int /*<<< orphan*/  enableFunctForMasterScan (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ loadRequiredBlockIntoMem (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  needSupplementaryScan (TYPE_4__*) ; 
 int /*<<< orphan*/  queryStatusRestore (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  queryStatusSave (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void doSingleMeterSupplementScan(SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *     pQuery = pRuntimeEnv->pQuery;
  SQueryStatus qStatus = {0};

  if (!needSupplementaryScan(pQuery)) {
    return;
  }

  SET_SUPPLEMENT_SCAN_FLAG(pRuntimeEnv);

  // usually this load operation will incure load disk block operation
  TSKEY endKey = loadRequiredBlockIntoMem(pRuntimeEnv, &pRuntimeEnv->endPos);
  assert((QUERY_IS_ASC_QUERY(pQuery) && endKey <= pQuery->ekey) ||
         (!QUERY_IS_ASC_QUERY(pQuery) && endKey >= pQuery->ekey));

  // close necessary function execution during supplementary scan
  disableFunctForSuppleScan(pRuntimeEnv, pQuery->order.order);
  queryStatusSave(pRuntimeEnv, &qStatus);

  doScanAllDataBlocks(pRuntimeEnv);

  // set the correct start position, and load the corresponding block in buffer if required.
  TSKEY actKey = loadRequiredBlockIntoMem(pRuntimeEnv, &pRuntimeEnv->startPos);
  assert((QUERY_IS_ASC_QUERY(pQuery) && actKey >= pQuery->skey) ||
         (!QUERY_IS_ASC_QUERY(pQuery) && actKey <= pQuery->skey));

  queryStatusRestore(pRuntimeEnv, &qStatus);
  enableFunctForMasterScan(pRuntimeEnv, pQuery->order.order);
  SET_MASTER_SCAN_FLAG(pRuntimeEnv);
}