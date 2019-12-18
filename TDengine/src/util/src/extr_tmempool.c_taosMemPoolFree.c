#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* pool; int blockSize; int numOfBlock; int* freeList; size_t first; size_t numOfFree; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ pool_t ;
typedef  scalar_t__ mpool_h ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pError (char*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void taosMemPoolFree(mpool_h handle, char *pMem) {
  int     index;
  pool_t *pool_p = (pool_t *)handle;

  if (pMem == NULL) return;

  index = (int)(pMem - pool_p->pool) % pool_p->blockSize;
  if (index != 0) {
    pError("invalid free address:%p\n", pMem);
    return;
  }

  index = (int)((pMem - pool_p->pool) / pool_p->blockSize);
  if (index < 0 || index >= pool_p->numOfBlock) {
    pError("mempool: error, invalid address:%p\n", pMem);
    return;
  }

  memset(pMem, 0, (size_t)pool_p->blockSize);

  pthread_mutex_lock(&pool_p->mutex);

  pool_p->freeList[(pool_p->first + pool_p->numOfFree) % pool_p->numOfBlock] = index;
  pool_p->numOfFree++;

  pthread_mutex_unlock(&pool_p->mutex);
}