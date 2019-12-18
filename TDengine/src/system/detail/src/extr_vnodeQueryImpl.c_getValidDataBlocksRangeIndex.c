#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_9__ {scalar_t__ keyLast; scalar_t__ keyFirst; } ;
struct TYPE_8__ {size_t start; TYPE_1__* pMeterObj; } ;
struct TYPE_7__ {int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; int /*<<< orphan*/  vnode; } ;
typedef  scalar_t__ TSKEY ;
typedef  int /*<<< orphan*/  SQuery ;
typedef  int /*<<< orphan*/  SQInfo ;
typedef  TYPE_1__ SMeterObj ;
typedef  TYPE_2__ SMeterDataInfo ;
typedef  TYPE_3__ SCompBlock ;

/* Variables and functions */
 scalar_t__ GET_QINFO_ADDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSQL_SO_ASC ; 
 size_t binarySearchForBlockImpl (TYPE_3__*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTrace (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool getValidDataBlocksRangeIndex(SMeterDataInfo *pMeterDataInfo, SQuery *pQuery, SCompBlock *pCompBlock,
                                         int64_t numOfBlocks, TSKEY minval, TSKEY maxval, int32_t *end) {
  SMeterObj *pMeterObj = pMeterDataInfo->pMeterObj;
  SQInfo *   pQInfo = (SQInfo *)GET_QINFO_ADDR(pQuery);

  /*
   * search the possible blk that may satisfy the query condition always start from the min value, therefore,
   * the order is always ascending order
   */
  pMeterDataInfo->start = binarySearchForBlockImpl(pCompBlock, (int32_t)numOfBlocks, minval, TSQL_SO_ASC);
  if (minval > pCompBlock[pMeterDataInfo->start].keyLast || maxval < pCompBlock[pMeterDataInfo->start].keyFirst) {
    dTrace("QInfo:%p vid:%d sid:%d id:%s, no result in files", pQInfo, pMeterObj->vnode, pMeterObj->sid,
           pMeterObj->meterId);
    return false;
  }

  // incremental checks following blocks until whose time range does not overlap with the query range
  *end = pMeterDataInfo->start;
  while (*end <= (numOfBlocks - 1)) {
    if (pCompBlock[*end].keyFirst <= maxval && pCompBlock[*end].keyLast >= maxval) {
      break;
    }

    if (pCompBlock[*end].keyFirst > maxval) {
      *end -= 1;
      break;
    }

    if (*end == numOfBlocks - 1) {
      break;
    } else {
      ++(*end);
    }
  }

  return true;
}