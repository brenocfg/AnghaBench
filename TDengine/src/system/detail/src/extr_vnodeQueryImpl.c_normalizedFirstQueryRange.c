#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  __block_search_fn_t ;
struct TYPE_21__ {scalar_t__ numOfBlocks; int /*<<< orphan*/ * cacheBlocks; } ;
struct TYPE_20__ {size_t searchAlgorithm; scalar_t__ pCache; } ;
struct TYPE_17__ {TYPE_4__* pMeterObj; TYPE_2__* pQuery; } ;
struct TYPE_19__ {TYPE_1__ runtimeEnv; } ;
struct TYPE_18__ {scalar_t__ skey; int fileId; scalar_t__ ekey; int /*<<< orphan*/  pos; int /*<<< orphan*/  slot; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  int /*<<< orphan*/  SPointInterpoSupporter ;
typedef  TYPE_3__ SMeterQuerySupportObj ;
typedef  TYPE_4__ SMeterObj ;
typedef  TYPE_5__ SCacheInfo ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_2__*) ; 
 int /*<<< orphan*/  QUERY_RANGE_GREATER_EQUAL ; 
 int /*<<< orphan*/  QUERY_RANGE_LESS_EQUAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int doGetQueryPos (scalar_t__,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getAlignedIntervalQueryRange (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int getNeighborPoints (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ getQualifiedDataBlock (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getQueryStartPositionInCache (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ getTimestampInDiskBlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isFirstLastRowQuery (TYPE_2__*) ; 
 int /*<<< orphan*/ * vnodeSearchKeyFunc ; 

bool normalizedFirstQueryRange(bool dataInDisk, bool dataInCache, SMeterQuerySupportObj *pSupporter,
                               SPointInterpoSupporter *pPointInterpSupporter) {
  SQueryRuntimeEnv *  pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *            pQuery = pRuntimeEnv->pQuery;
  SMeterObj *         pMeterObj = pRuntimeEnv->pMeterObj;
  __block_search_fn_t searchFn = vnodeSearchKeyFunc[pMeterObj->searchAlgorithm];

  if (QUERY_IS_ASC_QUERY(pQuery)) {
    // todo: the action return as the getQueryStartPositionInCache function
    if (dataInDisk && getQualifiedDataBlock(pMeterObj, pRuntimeEnv, QUERY_RANGE_GREATER_EQUAL, searchFn)) {
      TSKEY key = getTimestampInDiskBlock(pRuntimeEnv, pQuery->pos);
      assert(key >= pQuery->skey);

      return doGetQueryPos(key, pSupporter, pPointInterpSupporter);
    }

    // set no data in file
    pQuery->fileId = -1;
    SCacheInfo *pCacheInfo = (SCacheInfo *)pMeterObj->pCache;

    /* if it is a interpolation query, the any points in cache that is greater than the query range is required */
    if (pCacheInfo == NULL || pCacheInfo->cacheBlocks == NULL || pCacheInfo->numOfBlocks == 0 || !dataInCache) {
      return false;
    }

    TSKEY nextKey = getQueryStartPositionInCache(pRuntimeEnv, &pQuery->slot, &pQuery->pos, false);
    return doGetQueryPos(nextKey, pSupporter, pPointInterpSupporter);

  } else {              // descending order
    if (dataInCache) {  // todo handle error
      TSKEY nextKey = getQueryStartPositionInCache(pRuntimeEnv, &pQuery->slot, &pQuery->pos, false);
      assert(nextKey == -1 || nextKey <= pQuery->skey);

      // valid data in cache
      if (nextKey != -1) {
        if (nextKey >= pQuery->ekey) {
          if (isFirstLastRowQuery(pQuery)) {
            return getNeighborPoints(pSupporter, pMeterObj, pPointInterpSupporter);
          } else {
            getAlignedIntervalQueryRange(pQuery, nextKey, pQuery->skey, pQuery->ekey);
            return true;
          }
        } else {
          /*
           * nextKey < pQuery->ekey && nextKey < pQuery->lastKey, query range is
           * larger than all data, abort NOTE: Interp query does not reach here, since for all interp query,
           * the query order is ascending order.
           */
          return false;
        }
      } else {  // all data in cache are greater than pQuery->lastKey, try file
      }
    }

    if (dataInDisk && getQualifiedDataBlock(pMeterObj, pRuntimeEnv, QUERY_RANGE_LESS_EQUAL, searchFn)) {
      TSKEY key = getTimestampInDiskBlock(pRuntimeEnv, pQuery->pos);
      assert(key <= pQuery->skey);

      /* key in query range. If not, no qualified in disk file */
      if (key >= pQuery->ekey) {
        if (isFirstLastRowQuery(pQuery)) { /* no qualified data in this query range */
          return getNeighborPoints(pSupporter, pMeterObj, pPointInterpSupporter);
        } else {
          getAlignedIntervalQueryRange(pQuery, key, pQuery->skey, pQuery->ekey);
          return true;
        }
      } else {  // Goes on in case of key in file less than pMeterObj->lastKey,
                // which is also the pQuery->skey
        if (isFirstLastRowQuery(pQuery)) {
          return getNeighborPoints(pSupporter, pMeterObj, pPointInterpSupporter);
        }
      }
    }
  }

  return false;
}