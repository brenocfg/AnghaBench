#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_16__ {scalar_t__ size; scalar_t__ keyLast; scalar_t__ keyFirst; } ;
struct TYPE_13__ {scalar_t__ offset; } ;
struct TYPE_15__ {scalar_t__ pos; scalar_t__ ekey; TYPE_1__ limit; int /*<<< orphan*/  slot; } ;
struct TYPE_14__ {int /*<<< orphan*/ * pMeterObj; TYPE_3__* pQuery; } ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;
typedef  int /*<<< orphan*/  SMeterObj ;
typedef  TYPE_4__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ BLK_CACHE_BLOCK ; 
 scalar_t__ BLK_FILE_BLOCK ; 
 scalar_t__ IS_DISK_DATA_BLOCK (TYPE_3__*) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 int /*<<< orphan*/  doSkipDataBlock (TYPE_2__*) ; 
 TYPE_4__ getBlockBasicInfo (void*,scalar_t__) ; 
 void* getGenericDataBlock (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updateOffsetVal (TYPE_2__*,TYPE_4__*,void*) ; 

void forwardQueryStartPosition(SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *   pQuery = pRuntimeEnv->pQuery;
  SMeterObj *pMeterObj = pRuntimeEnv->pMeterObj;

  if (pQuery->limit.offset <= 0) {
    return;
  }

  void *pBlock = getGenericDataBlock(pMeterObj, pQuery, pQuery->slot);

  int32_t    blockType = (IS_DISK_DATA_BLOCK(pQuery)) ? BLK_FILE_BLOCK : BLK_CACHE_BLOCK;
  SBlockInfo blockInfo = getBlockBasicInfo(pBlock, blockType);

  // get the qualified data that can be skipped
  int32_t maxReads = (QUERY_IS_ASC_QUERY(pQuery)) ? blockInfo.size - pQuery->pos : pQuery->pos + 1;

  if (pQuery->limit.offset < maxReads || (pQuery->ekey <= blockInfo.keyLast && QUERY_IS_ASC_QUERY(pQuery)) ||
      (pQuery->ekey >= blockInfo.keyFirst && !QUERY_IS_ASC_QUERY(pQuery))) {  // start position in current block
    updateOffsetVal(pRuntimeEnv, &blockInfo, pBlock);
  } else {
    pQuery->limit.offset -= maxReads;
    doSkipDataBlock(pRuntimeEnv);
  }
}