#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  size_t int32_t ;
typedef  int (* __block_search_fn_t ) (scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ;
struct TYPE_32__ {int numOfPoints; scalar_t__ keyFirst; scalar_t__ keyLast; } ;
struct TYPE_31__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
struct TYPE_28__ {int /*<<< orphan*/  order; } ;
struct TYPE_30__ {size_t slot; int pos; scalar_t__ lastKey; scalar_t__ ekey; scalar_t__ numOfFilterCols; size_t numOfOutputCols; TYPE_5__ order; int /*<<< orphan*/  fileId; TYPE_3__* pSelectExpr; } ;
struct TYPE_29__ {scalar_t__ pTSBuf; TYPE_4__* primaryColBuffer; int /*<<< orphan*/ * pCtx; int /*<<< orphan*/ * pHeaderFiles; TYPE_8__* pMeterObj; TYPE_7__* pQuery; } ;
struct TYPE_27__ {scalar_t__ data; } ;
struct TYPE_24__ {int /*<<< orphan*/  colId; } ;
struct TYPE_25__ {size_t functionId; TYPE_1__ colInfo; } ;
struct TYPE_26__ {TYPE_2__ pBase; } ;
struct TYPE_23__ {size_t (* dataReqFunc ) (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_6__ SQueryRuntimeEnv ;
typedef  int /*<<< orphan*/  SQueryFileInfo ;
typedef  TYPE_7__ SQuery ;
typedef  TYPE_8__ SMeterObj ;
typedef  int /*<<< orphan*/  SField ;
typedef  TYPE_9__ SCompBlock ;
typedef  int /*<<< orphan*/  SBlockInfo ;

/* Variables and functions */
 size_t BLK_DATA_ALL_NEEDED ; 
 size_t BLK_DATA_FILEDS_NEEDED ; 
 size_t BLK_DATA_NO_NEEDED ; 
 int /*<<< orphan*/  BLK_FILE_BLOCK ; 
 size_t DISK_DATA_DISCARDED ; 
 size_t DISK_DATA_LOADED ; 
 size_t DISK_DATA_LOAD_FAILED ; 
 int /*<<< orphan*/  GET_QINFO_ADDR (TYPE_7__*) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_7__*) ; 
 int /*<<< orphan*/  SET_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DATA_BLOCK_NOT_LOADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FILE_BLOCK_FLAG (int /*<<< orphan*/ ) ; 
 TYPE_18__* aAggs ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  getBlockBasicInfo (TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ loadDataBlockFieldsInfo (TYPE_6__*,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ **) ; 
 size_t loadDataBlockIntoMem (TYPE_9__*,int /*<<< orphan*/ **,TYPE_6__*,size_t,int,int) ; 
 int needPrimaryTimestampCol (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  needToLoadDataBlock (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qTrace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,scalar_t__,scalar_t__,int,...) ; 
 int /*<<< orphan*/  setTimestampRange (TYPE_6__*,scalar_t__,scalar_t__) ; 
 size_t stub1 (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t LoadDatablockOnDemand(SCompBlock *pBlock, SField **pFields, int8_t *blkStatus, SQueryRuntimeEnv *pRuntimeEnv,
                              int32_t fileIdx, int32_t slotIdx, __block_search_fn_t searchFn, bool onDemand) {
  SQuery *        pQuery = pRuntimeEnv->pQuery;
  SMeterObj *     pMeterObj = pRuntimeEnv->pMeterObj;
  SQueryFileInfo *pQueryFileInfo = &pRuntimeEnv->pHeaderFiles[fileIdx];

  TSKEY *primaryKeys = (TSKEY *)pRuntimeEnv->primaryColBuffer->data;

  pQuery->slot = slotIdx;
  pQuery->pos = QUERY_IS_ASC_QUERY(pQuery) ? 0 : pBlock->numOfPoints - 1;

  SET_FILE_BLOCK_FLAG(*blkStatus);
  SET_DATA_BLOCK_NOT_LOADED(*blkStatus);

  if (((pQuery->lastKey <= pBlock->keyFirst && pQuery->ekey >= pBlock->keyLast && QUERY_IS_ASC_QUERY(pQuery)) ||
       (pQuery->ekey <= pBlock->keyFirst && pQuery->lastKey >= pBlock->keyLast && !QUERY_IS_ASC_QUERY(pQuery))) &&
      onDemand) {
    int32_t req = 0;
    if (pQuery->numOfFilterCols > 0) {
      req = BLK_DATA_ALL_NEEDED;
    } else {
      for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
        int32_t functID = pQuery->pSelectExpr[i].pBase.functionId;
        req |= aAggs[functID].dataReqFunc(&pRuntimeEnv->pCtx[i], pBlock->keyFirst, pBlock->keyLast,
                                          pQuery->pSelectExpr[i].pBase.colInfo.colId, *blkStatus);
      }

      if (pRuntimeEnv->pTSBuf > 0) {
        req |= BLK_DATA_ALL_NEEDED;
      }
    }

    if (req == BLK_DATA_NO_NEEDED) {
      qTrace("QInfo:%p vid:%d sid:%d id:%s, slot:%d, data block ignored, brange:%lld-%lld, rows:%d",
             GET_QINFO_ADDR(pQuery), pMeterObj->vnode, pMeterObj->sid, pMeterObj->meterId, pQuery->slot,
             pBlock->keyFirst, pBlock->keyLast, pBlock->numOfPoints);

      setTimestampRange(pRuntimeEnv, pBlock->keyFirst, pBlock->keyLast);
    } else if (req == BLK_DATA_FILEDS_NEEDED) {
      if (loadDataBlockFieldsInfo(pRuntimeEnv, pQueryFileInfo, pBlock, pFields) < 0) {
        return DISK_DATA_LOAD_FAILED;
      }
    } else {
      assert(req == BLK_DATA_ALL_NEEDED);
      goto _load_all;
    }
  } else {
  _load_all:
    if (loadDataBlockFieldsInfo(pRuntimeEnv, pQueryFileInfo, pBlock, pFields) < 0) {
      return DISK_DATA_LOAD_FAILED;
    }

    if ((pQuery->lastKey <= pBlock->keyFirst && pQuery->ekey >= pBlock->keyLast && QUERY_IS_ASC_QUERY(pQuery)) ||
        (pQuery->lastKey >= pBlock->keyLast && pQuery->ekey <= pBlock->keyFirst && !QUERY_IS_ASC_QUERY(pQuery))) {
      /*
       * if this block is completed included in the query range, do more filter operation
       * filter the data block according to the value filter condition.
       * no need to load the data block, continue for next block
       */
      if (!needToLoadDataBlock(pQuery, *pFields, pRuntimeEnv->pCtx)) {
#if defined(_DEBUG_VIEW)
        dTrace("QInfo:%p fileId:%d, slot:%d, block discarded by per-filter, ", GET_QINFO_ADDR(pQuery), pQuery->fileId,
               pQuery->slot);
#endif
        qTrace("QInfo:%p id:%s slot:%d, data block ignored by pre-filter, fields loaded, brange:%lld-%lld, rows:%d",
               GET_QINFO_ADDR(pQuery), pMeterObj->meterId, pQuery->slot, pBlock->keyFirst, pBlock->keyLast,
               pBlock->numOfPoints);
        return DISK_DATA_DISCARDED;
      }
    }

    SBlockInfo binfo = getBlockBasicInfo(pBlock, BLK_FILE_BLOCK);
    bool       loadTS = needPrimaryTimestampCol(pQuery, &binfo);

    /*
     * the pRuntimeEnv->pMeterObj is not updated during loop, since which meter this block is belonged to is not matter
     * in order to enforce to load the data block, we HACK the load check procedure,
     * by changing pQuery->slot each time to IGNORE the pLoadInfo data check. It is NOT a normal way.
     */
    int32_t ret = loadDataBlockIntoMem(pBlock, pFields, pRuntimeEnv, fileIdx, loadTS, false);
    SET_DATA_BLOCK_LOADED(*blkStatus);

    if (ret < 0) {
      return DISK_DATA_LOAD_FAILED;
    }

    /* find first qualified record position in this block */
    if (loadTS) {
      /* find first qualified record position in this block */
      pQuery->pos =
          searchFn(pRuntimeEnv->primaryColBuffer->data, pBlock->numOfPoints, pQuery->lastKey, pQuery->order.order);
      /* boundary timestamp check */
      assert(pBlock->keyFirst == primaryKeys[0] && pBlock->keyLast == primaryKeys[pBlock->numOfPoints - 1]);
    }

    /*
     * NOTE:
     * if the query of current timestamp window is COMPLETED, the query range condition may not be satisfied
     * such as:
     * pQuery->lastKey + 1 == pQuery->ekey for descending order interval query
     * pQuery->lastKey - 1 == pQuery->ekey for ascending query
     */
    assert(((pQuery->ekey >= pQuery->lastKey || pQuery->ekey == pQuery->lastKey - 1) && QUERY_IS_ASC_QUERY(pQuery)) ||
           ((pQuery->ekey <= pQuery->lastKey || pQuery->ekey == pQuery->lastKey + 1) && !QUERY_IS_ASC_QUERY(pQuery)));
  }

  return DISK_DATA_LOADED;
}