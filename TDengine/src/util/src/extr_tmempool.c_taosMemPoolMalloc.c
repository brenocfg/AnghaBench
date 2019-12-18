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
struct TYPE_2__ {scalar_t__ numOfFree; char* pool; int blockSize; int* freeList; size_t first; int numOfBlock; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ pool_t ;
typedef  scalar_t__ mpool_h ;

/* Variables and functions */
 int /*<<< orphan*/  pTrace (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

char *taosMemPoolMalloc(mpool_h handle) {
  char *  pos = NULL;
  pool_t *pool_p = (pool_t *)handle;

  pthread_mutex_lock(&(pool_p->mutex));

  if (pool_p->numOfFree > 0) {
    pos = pool_p->pool + pool_p->blockSize * (pool_p->freeList[pool_p->first]);
    pool_p->first++;
    pool_p->first = pool_p->first % pool_p->numOfBlock;
    pool_p->numOfFree--;
  }

  pthread_mutex_unlock(&(pool_p->mutex));

  if (pos == NULL) pTrace("mempool: out of memory");
  return pos;
}