#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  __block_search_fn_t ;
struct TYPE_27__ {scalar_t__ keyLast; scalar_t__ keyFirst; } ;
struct TYPE_26__ {TYPE_4__* pMeterQInfo; } ;
struct TYPE_25__ {int lastResRows; } ;
struct TYPE_22__ {TYPE_2__* pQuery; } ;
struct TYPE_24__ {TYPE_1__ runtimeEnv; } ;
struct TYPE_23__ {scalar_t__ skey; scalar_t__ ekey; } ;
typedef  int /*<<< orphan*/  TSKEY ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SMeterQuerySupportObj ;
typedef  TYPE_4__ SMeterQueryInfo ;
typedef  TYPE_5__ SMeterDataInfo ;
typedef  int /*<<< orphan*/  SField ;
typedef  TYPE_6__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_2__*) ; 
 int applyFunctionsOnBlock (TYPE_1__*,TYPE_6__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  doApplyIntervalQueryOnBlock (TYPE_3__*,TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getNextAccessedKeyInData (TYPE_2__*,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  saveIntervalQueryRange (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  setIntervalQueryRange (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void applyIntervalQueryOnBlock(SMeterQuerySupportObj *pSupporter, SMeterDataInfo *pInfoEx, char *data,
                                      int64_t *pPrimaryData, SBlockInfo *pBlockInfo, int32_t blockStatus,
                                      SField *pFields, __block_search_fn_t searchFn) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = pRuntimeEnv->pQuery;
  SMeterQueryInfo * pInfo = pInfoEx->pMeterQInfo;

  /*
   * for each block, we need to handle the previous query, since the determination of previous query being completed
   * or not is based on the start key of current block.
   */
  TSKEY key = getNextAccessedKeyInData(pQuery, pPrimaryData, pBlockInfo, blockStatus);
  setIntervalQueryRange(pInfoEx->pMeterQInfo, pSupporter, key);

  if (((pQuery->skey > pQuery->ekey) && QUERY_IS_ASC_QUERY(pQuery)) ||
      ((pQuery->skey < pQuery->ekey) && !QUERY_IS_ASC_QUERY(pQuery))) {
    return;
  }

  if (((pBlockInfo->keyLast < pQuery->ekey) && QUERY_IS_ASC_QUERY(pQuery)) ||
      ((pBlockInfo->keyFirst > pQuery->ekey) && !QUERY_IS_ASC_QUERY(pQuery))) {
    int32_t numOfRes = 0;
    /* current block is included in this interval */
    int32_t steps = applyFunctionsOnBlock(pRuntimeEnv, pBlockInfo, pPrimaryData, data, pFields, searchFn, &numOfRes);
    assert(numOfRes <= 1 && numOfRes >= 0 && steps > 0);

    if (pInfo->lastResRows == 0) {
      pInfo->lastResRows = numOfRes;
    } else {
      assert(pInfo->lastResRows == 1);
    }

    saveIntervalQueryRange(pRuntimeEnv, pInfo);
  } else {
    doApplyIntervalQueryOnBlock(pSupporter, pInfo, pBlockInfo, pPrimaryData, data, pFields, searchFn);
  }
}