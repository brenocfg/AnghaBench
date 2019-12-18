#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_18__ {scalar_t__ keyLast; scalar_t__ keyFirst; size_t size; } ;
struct TYPE_17__ {scalar_t__* offset; } ;
struct TYPE_14__ {scalar_t__ offset; } ;
struct TYPE_16__ {scalar_t__ ekey; size_t pos; TYPE_2__ limit; int /*<<< orphan*/  skey; int /*<<< orphan*/  lastKey; } ;
struct TYPE_15__ {TYPE_1__* primaryColBuffer; TYPE_4__* pQuery; } ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SCacheBlock ;
typedef  TYPE_6__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ IS_DISK_DATA_BLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  QUERY_COMPLETED ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getTimestampInCacheBlock (void*,int) ; 
 int /*<<< orphan*/  getTimestampInDiskBlock (TYPE_3__*,int) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void updateOffsetVal(SQueryRuntimeEnv *pRuntimeEnv, SBlockInfo *pBlockInfo, void *pBlock) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  /*
   *  The actually qualified points that can be skipped needs to be calculated if query is
   *  done in current data block
   */
  if ((pQuery->ekey <= pBlockInfo->keyLast && QUERY_IS_ASC_QUERY(pQuery)) ||
      (pQuery->ekey >= pBlockInfo->keyFirst && !QUERY_IS_ASC_QUERY(pQuery))) {
    // force load timestamp data blocks
    if (IS_DISK_DATA_BLOCK(pQuery)) {
      getTimestampInDiskBlock(pRuntimeEnv, 0);
    }

    // update the pQuery->limit.offset value, and pQuery->pos value
    TSKEY *keys = NULL;
    if (IS_DISK_DATA_BLOCK(pQuery)) {
      keys = (TSKEY *)pRuntimeEnv->primaryColBuffer->data;
    } else {
      keys = (TSKEY *)(((SCacheBlock *)pBlock)->offset[0]);
    }

    int32_t i = 0;
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      for (i = pQuery->pos; i < pBlockInfo->size && pQuery->limit.offset > 0; ++i) {
        if (keys[i] <= pQuery->ekey) {
          pQuery->limit.offset -= 1;
        } else {
          break;
        }
      }

    } else {
      for (i = pQuery->pos; i >= 0 && pQuery->limit.offset > 0; --i) {
        if (keys[i] >= pQuery->ekey) {
          pQuery->limit.offset -= 1;
        } else {
          break;
        }
      }
    }

    if (((i == pBlockInfo->size || keys[i] > pQuery->ekey) && QUERY_IS_ASC_QUERY(pQuery)) ||
        ((i < 0 || keys[i] < pQuery->ekey) && !QUERY_IS_ASC_QUERY(pQuery))) {
      setQueryStatus(pQuery, QUERY_COMPLETED);
      pQuery->pos = -1;
    } else {
      pQuery->pos = i;
    }
  } else {
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      pQuery->pos += pQuery->limit.offset;
    } else {
      pQuery->pos -= pQuery->limit.offset;
    }

    assert(pQuery->pos >= 0 && pQuery->pos <= pBlockInfo->size - 1);

    if (IS_DISK_DATA_BLOCK(pQuery)) {
      pQuery->skey = getTimestampInDiskBlock(pRuntimeEnv, pQuery->pos);
    } else {
      pQuery->skey = getTimestampInCacheBlock(pBlock, pQuery->pos);
    }

    // update the offset value
    pQuery->lastKey = pQuery->skey;
    pQuery->limit.offset = 0;
  }
}