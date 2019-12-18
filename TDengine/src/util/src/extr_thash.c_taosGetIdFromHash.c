#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;
struct TYPE_5__ {scalar_t__ maxSessions; int (* hashFp ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mutex; TYPE_1__** longHashList; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; struct TYPE_4__* next; int /*<<< orphan*/  cont; } ;
typedef  TYPE_1__ SLongHash ;
typedef  TYPE_2__ SHashObj ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

int32_t taosGetIdFromHash(void *handle, uint64_t cont) {
  int        hash;
  SLongHash *pNode;
  SHashObj * pObj;

  pObj = (SHashObj *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return -1;

  hash = (*pObj->hashFp)(pObj, cont);

  pthread_mutex_lock(&pObj->mutex);

  pNode = pObj->longHashList[hash];

  while (pNode) {
    if (pNode->cont == cont) {
      break;
    }

    pNode = pNode->next;
  }

  pthread_mutex_unlock(&pObj->mutex);

  if (pNode) return (int32_t)pNode->id;

  return -1;
}