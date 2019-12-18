#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int maxId; scalar_t__ numOfFree; int* freeList; size_t freeSlot; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ id_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  pError (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int taosAllocateId(void *handle) {
  id_pool_t *pIdPool;
  int        id = -1;
  if (handle == NULL) return id;

  pIdPool = (id_pool_t *)handle;

  if (pIdPool->maxId < 3) pError("pool:%p is messed up, maxId:%d", pIdPool, pIdPool->maxId);

  if (pthread_mutex_lock(&pIdPool->mutex) != 0) perror("lock pIdPool Mutex");

  if (pIdPool->numOfFree > 0) {
    id = pIdPool->freeList[pIdPool->freeSlot];
    pIdPool->freeSlot = (pIdPool->freeSlot + 1) % pIdPool->maxId;
    pIdPool->numOfFree--;
  }

  if (pthread_mutex_unlock(&pIdPool->mutex) != 0) perror("unlock pIdPool Mutex");

  return id;
}