#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  nSize; } ;
typedef  TYPE_1__ tSkipList ;
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  num; int /*<<< orphan*/ * cur; TYPE_1__* pSkipList; } ;
typedef  TYPE_2__ SSkipListIterator ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 

int32_t tSkipListIteratorReset(tSkipList *pSkipList, SSkipListIterator* iter) {
  if (pSkipList == NULL) {
    return -1;
  }

  iter->pSkipList = pSkipList;

  pthread_rwlock_rdlock(&pSkipList->lock);
  iter->cur = NULL;//pSkipList->pHead.pForward[0];
  iter->num = pSkipList->nSize;
  pthread_rwlock_unlock(&pSkipList->lock);

  return 0;
}