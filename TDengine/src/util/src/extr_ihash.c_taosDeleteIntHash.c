#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t int32_t ;
struct TYPE_8__ {TYPE_1__* prev; struct TYPE_8__* next; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {scalar_t__ maxSessions; size_t (* hashFp ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mutex; TYPE_3__** hashList; } ;
struct TYPE_6__ {TYPE_3__* next; } ;
typedef  TYPE_2__ IHashObj ;
typedef  TYPE_3__ IHashNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void taosDeleteIntHash(void *handle, uint64_t key) {
  int32_t    hash;
  IHashNode *pNode;
  IHashObj * pObj;

  pObj = (IHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return;

  hash = (*(pObj->hashFp))(pObj, key);

  pthread_mutex_lock(&pObj->mutex);

  pNode = pObj->hashList[hash];
  while (pNode) {
    if (pNode->key == key) break;

    pNode = pNode->next;
  }

  if (pNode) {
    if (pNode->prev) {
      pNode->prev->next = pNode->next;
    } else {
      pObj->hashList[hash] = pNode->next;
    }

    if (pNode->next) {
      pNode->next->prev = pNode->prev;
    }

    free(pNode);
  }

  pthread_mutex_unlock(&pObj->mutex);
}