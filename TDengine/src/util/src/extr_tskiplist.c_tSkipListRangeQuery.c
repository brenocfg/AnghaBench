#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSkipListNode ;
struct TYPE_8__ {int /*<<< orphan*/  queryCount; } ;
struct TYPE_9__ {TYPE_1__ state; } ;
typedef  TYPE_2__ tSkipList ;
struct TYPE_10__ {int /*<<< orphan*/  upperBndRelOptr; int /*<<< orphan*/  upperBnd; int /*<<< orphan*/  lowerBndRelOptr; int /*<<< orphan*/  lowerBnd; } ;
typedef  TYPE_3__ tSKipListQueryCond ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  tSkipListEndParQuery (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/ * tSkipListParQuery (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t tSkipListRangeQuery(tSkipList *pSkipList, tSKipListQueryCond *pCond, tSkipListNode ***pRes) {
  pSkipList->state.queryCount++;
  tSkipListNode *pStart = tSkipListParQuery(pSkipList, &pCond->lowerBnd, pCond->lowerBndRelOptr);
  if (pStart == 0) {
    *pRes = NULL;
    return 0;
  }

  return tSkipListEndParQuery(pSkipList, pStart, &pCond->upperBnd, pCond->upperBndRelOptr, pRes);
}