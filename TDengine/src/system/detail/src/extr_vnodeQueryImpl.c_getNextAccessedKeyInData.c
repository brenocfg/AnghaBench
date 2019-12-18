#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {int size; scalar_t__ keyFirst; scalar_t__ keyLast; } ;
struct TYPE_6__ {int pos; scalar_t__ skey; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SQuery ;
typedef  TYPE_2__ SBlockInfo ;

/* Variables and functions */
 scalar_t__ IS_DATA_BLOCK_LOADED (int /*<<< orphan*/ ) ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

int64_t getNextAccessedKeyInData(SQuery *pQuery, int64_t *pPrimaryCol, SBlockInfo *pBlockInfo, int32_t blockStatus) {
  assert(pQuery->pos >= 0 && pQuery->pos <= pBlockInfo->size - 1);

  TSKEY key = -1;
  if (IS_DATA_BLOCK_LOADED(blockStatus)) {
    key = pPrimaryCol[pQuery->pos];
  } else {
    assert(pQuery->pos == pBlockInfo->size - 1 || pQuery->pos == 0);
    key = QUERY_IS_ASC_QUERY(pQuery) ? pBlockInfo->keyFirst : pBlockInfo->keyLast;
  }

  assert((key >= pQuery->skey && QUERY_IS_ASC_QUERY(pQuery)) || (key <= pQuery->skey && !QUERY_IS_ASC_QUERY(pQuery)));
  return key;
}