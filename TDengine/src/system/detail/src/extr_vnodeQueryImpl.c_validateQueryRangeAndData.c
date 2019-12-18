#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ keyFirst; scalar_t__ keyLast; } ;
struct TYPE_10__ {size_t pos; scalar_t__ ekey; scalar_t__ lastKey; scalar_t__ skey; } ;
struct TYPE_9__ {int /*<<< orphan*/  blockStatus; TYPE_2__* pQuery; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ IS_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ needPrimaryTimestampCol (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static void validateQueryRangeAndData(SQueryRuntimeEnv *pRuntimeEnv, const TSKEY *pPrimaryColumn,
                                      SBlockInfo *pBlockBasicInfo) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  TSKEY startKey = -1;
  // timestamp qualification check
  if (IS_DATA_BLOCK_LOADED(pRuntimeEnv->blockStatus) && needPrimaryTimestampCol(pQuery, pBlockBasicInfo)) {
    startKey = pPrimaryColumn[pQuery->pos];
  } else {
    startKey = pBlockBasicInfo->keyFirst;
    TSKEY endKey = pBlockBasicInfo->keyLast;

    assert((endKey <= pQuery->ekey && QUERY_IS_ASC_QUERY(pQuery)) ||
           (endKey >= pQuery->ekey && !QUERY_IS_ASC_QUERY(pQuery)));
  }

  assert((startKey >= pQuery->lastKey && startKey <= pQuery->ekey && pQuery->skey <= pQuery->lastKey &&
          QUERY_IS_ASC_QUERY(pQuery)) ||
         (startKey <= pQuery->lastKey && startKey >= pQuery->ekey && pQuery->skey >= pQuery->lastKey &&
          !QUERY_IS_ASC_QUERY(pQuery)));
}