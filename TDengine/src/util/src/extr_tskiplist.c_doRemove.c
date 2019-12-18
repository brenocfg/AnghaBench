#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t nLevel; TYPE_1__** pForward; } ;
typedef  TYPE_3__ tSkipListNode ;
struct TYPE_11__ {int nTotalMemSize; } ;
struct TYPE_13__ {int /*<<< orphan*/  nSize; TYPE_2__ state; } ;
typedef  TYPE_4__ tSkipList ;
typedef  size_t int32_t ;
struct TYPE_10__ {struct TYPE_10__** pForward; TYPE_3__** pBackward; } ;

/* Variables and functions */
 int POINTER_BYTES ; 
 int /*<<< orphan*/  removeNodeEachLevel (TYPE_4__*,int) ; 
 int /*<<< orphan*/  tfree (TYPE_3__*) ; 

__attribute__((used)) static void doRemove(tSkipList *pSkipList, tSkipListNode *pNode, tSkipListNode *forward[]) {
  int32_t level = pNode->nLevel;
  for (int32_t j = level - 1; j >= 0; --j) {
    if ((forward[j]->pForward[j] != NULL) && (forward[j]->pForward[j]->pForward[j])) {
      forward[j]->pForward[j]->pForward[j]->pBackward[j] = forward[j];
    }

    if (forward[j]->pForward[j] != NULL) {
      forward[j]->pForward[j] = forward[j]->pForward[j]->pForward[j];
    }
  }

  pSkipList->state.nTotalMemSize -= (sizeof(tSkipListNode) + POINTER_BYTES * pNode->nLevel * 2);
  removeNodeEachLevel(pSkipList, pNode->nLevel);

  tfree(pNode);
  --pSkipList->nSize;
}