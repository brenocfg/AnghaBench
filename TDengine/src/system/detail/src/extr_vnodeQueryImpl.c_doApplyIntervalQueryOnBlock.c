#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
typedef  size_t (* __block_search_fn_t ) (char*,size_t,scalar_t__,int /*<<< orphan*/ ) ;
struct TYPE_23__ {size_t size; scalar_t__ keyLast; scalar_t__ keyFirst; } ;
struct TYPE_22__ {size_t lastResRows; } ;
struct TYPE_19__ {TYPE_3__* pQuery; } ;
struct TYPE_21__ {scalar_t__ rawEKey; int /*<<< orphan*/  rawSKey; TYPE_2__ runtimeEnv; } ;
struct TYPE_18__ {int /*<<< orphan*/  order; } ;
struct TYPE_20__ {size_t pos; scalar_t__ lastKey; scalar_t__ ekey; scalar_t__ skey; TYPE_1__ order; } ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SMeterQuerySupportObj ;
typedef  TYPE_5__ SMeterQueryInfo ;
typedef  int /*<<< orphan*/  SField ;
typedef  TYPE_6__ SBlockInfo ;

/* Variables and functions */
 size_t GET_FORWARD_DIRECTION_FACTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 size_t applyFunctionsOnBlock (TYPE_2__*,TYPE_6__*,scalar_t__*,char*,int /*<<< orphan*/ *,size_t (*) (char*,size_t,scalar_t__,int /*<<< orphan*/ ),size_t*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getAlignedIntervalQueryRange (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  saveIntervalQueryRange (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  saveResult (TYPE_4__*,TYPE_5__*,int) ; 

__attribute__((used)) static void doApplyIntervalQueryOnBlock(SMeterQuerySupportObj *pSupporter, SMeterQueryInfo *pInfo,
                                        SBlockInfo *pBlockInfo, int64_t *pPrimaryCol, char *sdata, SField *pFields,
                                        __block_search_fn_t searchFn) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = pRuntimeEnv->pQuery;
  int32_t           factor = GET_FORWARD_DIRECTION_FACTOR(pQuery->order.order);

  int64_t nextKey = -1;
  bool    queryCompleted = false;

  while (1) {
    int32_t numOfRes = 0;
    int32_t steps = applyFunctionsOnBlock(pRuntimeEnv, pBlockInfo, pPrimaryCol, sdata, pFields, searchFn, &numOfRes);
    assert(steps > 0);

    // NOTE: in case of stable query, only ONE(or ZERO) row of result generated for each query range
    if (pInfo->lastResRows == 0) {
      pInfo->lastResRows = numOfRes;
    } else {
      assert(pInfo->lastResRows == 1);
    }

    int32_t pos = pQuery->pos + steps * factor;

    // query does not reach the end of current block
    if ((pos < pBlockInfo->size && QUERY_IS_ASC_QUERY(pQuery)) || (pos >= 0 && !QUERY_IS_ASC_QUERY(pQuery))) {
      nextKey = pPrimaryCol[pos];
    } else {
      assert((pQuery->lastKey > pBlockInfo->keyLast && QUERY_IS_ASC_QUERY(pQuery)) ||
             (pQuery->lastKey < pBlockInfo->keyFirst && !QUERY_IS_ASC_QUERY(pQuery)));
    }

    // all data satisfy current query are checked, query completed
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      queryCompleted = (nextKey > pQuery->ekey || pQuery->ekey <= pBlockInfo->keyLast);
    } else {
      queryCompleted = (nextKey < pQuery->ekey || pQuery->ekey >= pBlockInfo->keyFirst);
    }

    /*
     * 1. there may be more date that satisfy current query interval, other than
     *    current block, we need to try next data blocks
     * 2. query completed, since reaches the upper bound of the main query range
     */
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      if (pQuery->lastKey > pBlockInfo->keyLast || pQuery->lastKey > pSupporter->rawEKey ||
          nextKey > pSupporter->rawEKey) {
        /*
         * current interval query is completed, set query result flag closed and
         * try next data block if pQuery->ekey == pSupporter->rawEKey, whole query is completed
         */
        if (pQuery->lastKey > pBlockInfo->keyLast) {
          assert(pQuery->ekey >= pBlockInfo->keyLast);
        }

        if (pQuery->lastKey > pSupporter->rawEKey || nextKey > pSupporter->rawEKey) {
          /* whole query completed, save result and abort */
          assert(queryCompleted);
          saveResult(pSupporter, pInfo, pInfo->lastResRows);

          // save the pQuery->lastKey for retrieve data in cache, actually, there will be no qualified data in cache.
          saveIntervalQueryRange(pRuntimeEnv, pInfo);
        } else if (pQuery->ekey == pBlockInfo->keyLast) {
          /* current interval query is completed, set the next query range on other data blocks if exist */
          int64_t prevEKey = pQuery->ekey;

          getAlignedIntervalQueryRange(pQuery, pQuery->lastKey, pSupporter->rawSKey, pSupporter->rawEKey);
          saveIntervalQueryRange(pRuntimeEnv, pInfo);

          assert(queryCompleted && prevEKey < pQuery->skey);
          if (pInfo->lastResRows > 0) {
            saveResult(pSupporter, pInfo, pInfo->lastResRows);
          }
        } else {
          /*
           * Data that satisfy current query range may locate in current block and blocks that are directly right
           * next to current block. Therefore, we need to keep the query range(interval) unchanged until reaching
           * the direct next data block, while only forwards the pQuery->lastKey.
           *
           * With the information of the directly next data block, whether locates in cache or disk,
           * current interval query being completed or not can be decided.
           */
          saveIntervalQueryRange(pRuntimeEnv, pInfo);
          assert(pQuery->lastKey > pBlockInfo->keyLast && pQuery->lastKey <= pQuery->ekey);

          /*
           * if current block is the last block of current file, we still close the result flag, and
           * merge with other meters in the same group
           */
          if (queryCompleted) {
            saveResult(pSupporter, pInfo, pInfo->lastResRows);
          }
        }

        break;
      }
    } else {
      if (pQuery->lastKey < pBlockInfo->keyFirst || pQuery->lastKey < pSupporter->rawEKey ||
          nextKey < pSupporter->rawEKey) {
        if (pQuery->lastKey < pBlockInfo->keyFirst) {
          assert(pQuery->ekey <= pBlockInfo->keyFirst);
        }

        if (pQuery->lastKey < pSupporter->rawEKey || (nextKey < pSupporter->rawEKey && nextKey != -1)) {
          /* whole query completed, save result and abort */
          assert(queryCompleted);
          saveResult(pSupporter, pInfo, pInfo->lastResRows);

          /*
           * save the pQuery->lastKey for retrieve data in cache, actually,
           * there will be no qualified data in cache.
           */
          saveIntervalQueryRange(pRuntimeEnv, pInfo);
        } else if (pQuery->ekey == pBlockInfo->keyFirst) {
          // current interval query is completed, set the next query range on other data blocks if exist
          int64_t prevEKey = pQuery->ekey;

          getAlignedIntervalQueryRange(pQuery, pQuery->lastKey, pSupporter->rawSKey, pSupporter->rawEKey);
          saveIntervalQueryRange(pRuntimeEnv, pInfo);

          assert(queryCompleted && prevEKey > pQuery->skey);
          if (pInfo->lastResRows > 0) {
            saveResult(pSupporter, pInfo, pInfo->lastResRows);
          }
        } else {
          /*
           * Data that satisfy current query range may locate in current block and blocks that are
           * directly right next to current block. Therefore, we need to keep the query range(interval)
           * unchanged until reaching the direct next data block, while only forwards the pQuery->lastKey.
           *
           * With the information of the directly next data block, whether locates in cache or disk,
           * current interval query being completed or not can be decided.
           */
          saveIntervalQueryRange(pRuntimeEnv, pInfo);
          assert(pQuery->lastKey < pBlockInfo->keyFirst && pQuery->lastKey >= pQuery->ekey);

          /*
           * if current block is the last block of current file, we still close the result
           * flag, and merge with other meters in the same group
           */
          if (queryCompleted) {
            saveResult(pSupporter, pInfo, pInfo->lastResRows);
          }
        }

        break;
      }
    }

    assert(queryCompleted);
    saveResult(pSupporter, pInfo, pInfo->lastResRows);

    assert((nextKey >= pQuery->lastKey && QUERY_IS_ASC_QUERY(pQuery)) ||
           (nextKey <= pQuery->lastKey && !QUERY_IS_ASC_QUERY(pQuery)));

    /* still in the same block to query */
    getAlignedIntervalQueryRange(pQuery, nextKey, pSupporter->rawSKey, pSupporter->rawEKey);
    saveIntervalQueryRange(pRuntimeEnv, pInfo);

    int32_t newPos = searchFn((char *)pPrimaryCol, pBlockInfo->size, pQuery->skey, pQuery->order.order);
    assert(newPos == pQuery->pos + steps * factor);

    pQuery->pos = newPos;
  }
}