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
struct TYPE_6__ {struct TYPE_6__** pBackward; struct TYPE_6__** pForward; } ;
typedef  TYPE_1__ tSkipListNode ;
struct TYPE_7__ {TYPE_1__ pHead; } ;
typedef  TYPE_2__ tSkipList ;
typedef  size_t int32_t ;

/* Variables and functions */

void tSkipListDoInsert(tSkipList *pSkipList, tSkipListNode **forward, int32_t nLevel, tSkipListNode *pNode) {
  for (int32_t i = 0; i < nLevel; ++i) {
    tSkipListNode *x = forward[i];
    if (x != NULL) {
      pNode->pBackward[i] = x;
      if (x->pForward[i]) x->pForward[i]->pBackward[i] = pNode;

      pNode->pForward[i] = x->pForward[i];
      x->pForward[i] = pNode;
    } else {
      pSkipList->pHead.pForward[i] = pNode;
      pNode->pBackward[i] = &(pSkipList->pHead);
    }
  }
}