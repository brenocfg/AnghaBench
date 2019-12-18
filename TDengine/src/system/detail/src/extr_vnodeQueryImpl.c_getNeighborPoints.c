#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  __block_search_fn_t ;
struct TYPE_34__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  slot; int /*<<< orphan*/  fileId; } ;
struct TYPE_33__ {scalar_t__ numOfPoints; } ;
struct TYPE_32__ {size_t searchAlgorithm; } ;
struct TYPE_28__ {TYPE_9__ startPos; TYPE_3__* pQuery; } ;
struct TYPE_31__ {scalar_t__ rawEKey; scalar_t__ rawSKey; TYPE_2__ runtimeEnv; } ;
struct TYPE_30__ {scalar_t__* pNextPoint; scalar_t__* pPrevPoint; } ;
struct TYPE_29__ {scalar_t__ skey; scalar_t__ ekey; scalar_t__ fileId; size_t slot; scalar_t__ pos; scalar_t__ lastKey; TYPE_1__* pBlock; int /*<<< orphan*/  over; } ;
struct TYPE_27__ {scalar_t__ numOfPoints; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SPointInterpoSupporter ;
typedef  TYPE_5__ SMeterQuerySupportObj ;
typedef  TYPE_6__ SMeterObj ;
typedef  TYPE_7__ SCacheBlock ;

/* Variables and functions */
 int /*<<< orphan*/  GET_QINFO_ADDR (TYPE_3__*) ; 
 scalar_t__ IS_DISK_DATA_BLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  QUERY_COMPLETED ; 
 int /*<<< orphan*/  QUERY_DESC_FORWARD_STEP ; 
 int QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 
 int /*<<< orphan*/  QUERY_NO_DATA_TO_CHECK ; 
 scalar_t__ Q_STATUS_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_7__* getCacheDataBlock (TYPE_6__*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  getOneRowFromCacheBlock (TYPE_2__*,TYPE_6__*,TYPE_7__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  getOneRowFromDiskBlock (TYPE_2__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  getQueryPositionForCacheInvalid (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ isFirstLastRowQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  isPointInterpoQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  moveToNextBlock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qTrace (char*,int /*<<< orphan*/ ,scalar_t__,size_t,scalar_t__,...) ; 
 int /*<<< orphan*/  savePointPosition (TYPE_9__*,scalar_t__,size_t,scalar_t__) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vnodeSearchKeyFunc ; 

__attribute__((used)) static bool getNeighborPoints(SMeterQuerySupportObj *pSupporter, SMeterObj *pMeterObj,
                              SPointInterpoSupporter *pPointInterpSupporter) {
  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  SQuery *          pQuery = pRuntimeEnv->pQuery;

  if (!isPointInterpoQuery(pQuery)) {
    return false;
  }

  /*
   * for interpolate point query, points that are directly before/after the specified point are required
   */
  if (isFirstLastRowQuery(pQuery)) {
    assert(!QUERY_IS_ASC_QUERY(pQuery));
  } else {
    assert(QUERY_IS_ASC_QUERY(pQuery));
  }
  assert(pPointInterpSupporter != NULL && pQuery->skey == pQuery->ekey);

  SCacheBlock *pBlock = NULL;

  qTrace("QInfo:%p get next data point, fileId:%d, slot:%d, pos:%d", GET_QINFO_ADDR(pQuery), pQuery->fileId,
         pQuery->slot, pQuery->pos);

  // save the point that is directly after or equals to the specified point
  if (IS_DISK_DATA_BLOCK(pQuery)) {
    getOneRowFromDiskBlock(pRuntimeEnv, pPointInterpSupporter->pNextPoint, pQuery->pos);
  } else {
    pBlock = getCacheDataBlock(pMeterObj, pQuery, pQuery->slot);
    __block_search_fn_t searchFn = vnodeSearchKeyFunc[pMeterObj->searchAlgorithm];

    while (pBlock == NULL) {
      // cache block is flushed to disk, try to find new query position again
      getQueryPositionForCacheInvalid(pRuntimeEnv, searchFn);

      // new position is located in file, load data and abort
      if (IS_DISK_DATA_BLOCK(pQuery)) {
        getOneRowFromDiskBlock(pRuntimeEnv, pPointInterpSupporter->pNextPoint, pQuery->pos);
        break;
      } else {
        pBlock = getCacheDataBlock(pMeterObj, pQuery, pQuery->slot);
      }
    }

    if (!IS_DISK_DATA_BLOCK(pQuery)) {
      getOneRowFromCacheBlock(pRuntimeEnv, pMeterObj, pBlock, pPointInterpSupporter->pNextPoint, pQuery->pos);
    }
  }

  /*
   * 1. for last_row query, return immediately.
   * 2. the specified timestamp equals to the required key, interpolation according to neighbor points is not necessary
   *    for interp query.
   */
  TSKEY actualKey = *(TSKEY *)pPointInterpSupporter->pNextPoint[0];
  if (isFirstLastRowQuery(pQuery) || actualKey == pQuery->skey) {
    setQueryStatus(pQuery, QUERY_NOT_COMPLETED);

    /*
     * the retrieved ts may not equals to pMeterObj->lastKey due to cache re-allocation
     * set the pQuery->ekey/pQuery->skey/pQuery->lastKey to be the new value.
     */
    if (pQuery->ekey != actualKey) {
      pQuery->skey = actualKey;
      pQuery->ekey = actualKey;
      pQuery->lastKey = actualKey;
      pSupporter->rawSKey = actualKey;
      pSupporter->rawEKey = actualKey;
    }
    return true;
  }

  /* the qualified point is not the first point in data block */
  if (pQuery->pos > 0) {
    int32_t prevPos = pQuery->pos - 1;

    if (IS_DISK_DATA_BLOCK(pQuery)) {
      /* save the point that is directly after the specified point */
      getOneRowFromDiskBlock(pRuntimeEnv, pPointInterpSupporter->pPrevPoint, prevPos);
    } else {
      getOneRowFromCacheBlock(pRuntimeEnv, pMeterObj, pBlock, pPointInterpSupporter->pPrevPoint, prevPos);
    }
  } else {
    __block_search_fn_t searchFn = vnodeSearchKeyFunc[pMeterObj->searchAlgorithm];

    savePointPosition(&pRuntimeEnv->startPos, pQuery->fileId, pQuery->slot, pQuery->pos);

    // backwards movement would not set the pQuery->pos correct. We need to set it manually later.
    moveToNextBlock(pRuntimeEnv, QUERY_DESC_FORWARD_STEP, searchFn, true);

    /*
     * no previous data exists reset the status and load the data block that contains the qualified point
     */
    if (Q_STATUS_EQUAL(pQuery->over, QUERY_NO_DATA_TO_CHECK)) {
      dTrace("QInfo:%p no previous data block, start fileId:%d, slot:%d, pos:%d, qrange:%lld-%lld, out of range",
             GET_QINFO_ADDR(pQuery), pRuntimeEnv->startPos.fileId, pRuntimeEnv->startPos.slot,
             pRuntimeEnv->startPos.pos, pQuery->skey, pQuery->ekey);

      // no result, return immediately
      setQueryStatus(pQuery, QUERY_COMPLETED);
      return false;
    } else {  // prev has been located
      if (pQuery->fileId >= 0) {
        pQuery->pos = pQuery->pBlock[pQuery->slot].numOfPoints - 1;
        getOneRowFromDiskBlock(pRuntimeEnv, pPointInterpSupporter->pPrevPoint, pQuery->pos);

        qTrace("QInfo:%p get prev data point, fileId:%d, slot:%d, pos:%d, pQuery->pos:%d", GET_QINFO_ADDR(pQuery),
               pQuery->fileId, pQuery->slot, pQuery->pos, pQuery->pos);
      } else {
        pBlock = getCacheDataBlock(pMeterObj, pQuery, pQuery->slot);
        if (pBlock == NULL) {
          // todo nothing, the previous block is flushed to disk
        } else {
          pQuery->pos = pBlock->numOfPoints - 1;
          getOneRowFromCacheBlock(pRuntimeEnv, pMeterObj, pBlock, pPointInterpSupporter->pPrevPoint, pQuery->pos);

          qTrace("QInfo:%p get prev data point, fileId:%d, slot:%d, pos:%d, pQuery->pos:%d", GET_QINFO_ADDR(pQuery),
                 pQuery->fileId, pQuery->slot, pBlock->numOfPoints - 1, pQuery->pos);
        }
      }
    }
  }

  pQuery->skey = *(TSKEY *)pPointInterpSupporter->pPrevPoint[0];
  pQuery->ekey = *(TSKEY *)pPointInterpSupporter->pNextPoint[0];
  pQuery->lastKey = pQuery->skey;

  return true;
}