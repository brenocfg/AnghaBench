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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ (* __block_search_fn_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;
struct TYPE_23__ {scalar_t__ keyLast; scalar_t__ keyFirst; } ;
struct TYPE_22__ {int /*<<< orphan*/  numOfPoints; } ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_20__ {int /*<<< orphan*/  vnode; } ;
struct TYPE_17__ {int /*<<< orphan*/  order; } ;
struct TYPE_19__ {int slot; scalar_t__ lastKey; scalar_t__ fileId; scalar_t__ numOfBlocks; scalar_t__ pos; TYPE_1__ order; int /*<<< orphan*/ * pFields; TYPE_7__* pBlock; } ;
struct TYPE_18__ {int /*<<< orphan*/  blockStatus; TYPE_5__* primaryColBuffer; TYPE_3__* pQuery; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SMeterObj ;
typedef  TYPE_5__ SData ;
typedef  TYPE_6__ SCompBlock ;

/* Variables and functions */
 int /*<<< orphan*/  GET_QINFO_ADDR (TYPE_3__*) ; 
 scalar_t__ QUERY_ASC_FORWARD_STEP ; 
 scalar_t__ QUERY_DESC_FORWARD_STEP ; 
 scalar_t__ QUERY_RANGE_GREATER_EQUAL ; 
 int /*<<< orphan*/  SET_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binarySearchForBlock (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  dError (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_6__* getDiskDataBlock (TYPE_3__*,scalar_t__) ; 
 scalar_t__ getFileIdFromKey (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ getNextDataFileCompInfo (TYPE_2__*,TYPE_4__*,scalar_t__) ; 
 scalar_t__ loadDataBlockIntoMem (TYPE_7__*,int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,int,int) ; 

__attribute__((used)) static bool getQualifiedDataBlock(SMeterObj *pMeterObj, SQueryRuntimeEnv *pRuntimeEnv, int32_t type,
                                  __block_search_fn_t searchFn) {
  int32_t blkIdx = -1;
  int32_t fid = -1;
  int32_t step = (type == QUERY_RANGE_GREATER_EQUAL) ? QUERY_ASC_FORWARD_STEP : QUERY_DESC_FORWARD_STEP;

  SQuery *pQuery = pRuntimeEnv->pQuery;
  pQuery->slot = -1;

  TSKEY key = pQuery->lastKey;

  SData *primaryColBuffer = pRuntimeEnv->primaryColBuffer;
  pQuery->fileId = getFileIdFromKey(pMeterObj->vnode, key) - step;

  while (1) {
    if ((fid = getNextDataFileCompInfo(pRuntimeEnv, pMeterObj, step)) < 0) {
      break;
    }

    blkIdx = binarySearchForBlock(pQuery, key);

    if (type == QUERY_RANGE_GREATER_EQUAL) {
      if (key <= pQuery->pBlock[blkIdx].keyLast) {
        break;
      } else {
        blkIdx = -1;
      }
    } else {
      if (key >= pQuery->pBlock[blkIdx].keyFirst) {
        break;
      } else {
        blkIdx = -1;
      }
    }
  }

  /* failed to find qualified point in file, abort */
  if (blkIdx == -1) {
    return false;
  }

  assert(blkIdx >= 0 && blkIdx < pQuery->numOfBlocks);

  // load first data block into memory failed, caused by disk block error
  bool blockLoaded = false;
  while (blkIdx < pQuery->numOfBlocks) {
    pQuery->slot = blkIdx;
    if (loadDataBlockIntoMem(&pQuery->pBlock[pQuery->slot], &pQuery->pFields[pQuery->slot], pRuntimeEnv, fid, true,
                             true) == 0) {
      SET_DATA_BLOCK_LOADED(pRuntimeEnv->blockStatus);
      blockLoaded = true;
      break;
    }

    dError("QInfo:%p fileId:%d total numOfBlks:%d blockId:%d into memory failed due to error in disk files",
           GET_QINFO_ADDR(pQuery), pQuery->fileId, pQuery->numOfBlocks, blkIdx);
    blkIdx += step;
  }

  // failed to load data from disk, abort current query
  if (blockLoaded == false) {
    return false;
  }

  SCompBlock *pBlocks = getDiskDataBlock(pQuery, blkIdx);

  // search qualified points in blk, according to primary key (timestamp) column
  pQuery->pos = searchFn(primaryColBuffer->data, pBlocks->numOfPoints, key, pQuery->order.order);
  assert(pQuery->pos >= 0 && pQuery->fileId >= 0 && pQuery->slot >= 0);

  return true;
}