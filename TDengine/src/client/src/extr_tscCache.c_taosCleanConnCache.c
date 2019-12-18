#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int maxSessions; void* pTimer; int keepTimer; int /*<<< orphan*/  tmrCtrl; int /*<<< orphan*/  mutex; int /*<<< orphan*/ ** connHashList; } ;
typedef  int /*<<< orphan*/  SConnHash ;
typedef  TYPE_1__ SConnCache ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosGetTimestampMs () ; 
 int /*<<< orphan*/  taosRemoveExpiredNodes (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosTmrReset (void (*) (void*,void*),int,TYPE_1__*,int /*<<< orphan*/ ,void**) ; 

void taosCleanConnCache(void *handle, void *tmrId) {
  int         hash;
  SConnHash * pNode;
  SConnCache *pObj;

  pObj = (SConnCache *)handle;
  if (pObj == NULL || pObj->maxSessions == 0) return;
  if (pObj->pTimer != tmrId) return;

  uint64_t time = taosGetTimestampMs();

  for (hash = 0; hash < pObj->maxSessions; ++hash) {
    pthread_mutex_lock(&pObj->mutex);
    pNode = pObj->connHashList[hash];
    taosRemoveExpiredNodes(pObj, pNode, hash, time);
    pthread_mutex_unlock(&pObj->mutex);
  }

  // tscTrace("timer, total connections in cache:%d", pObj->total);
  taosTmrReset(taosCleanConnCache, pObj->keepTimer * 2, pObj, pObj->tmrCtrl, &pObj->pTimer);
}