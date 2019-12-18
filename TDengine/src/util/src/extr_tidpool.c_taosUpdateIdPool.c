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
struct TYPE_3__ {int maxId; int* freeList; int /*<<< orphan*/  mutex; int /*<<< orphan*/  numOfFree; } ;
typedef  TYPE_1__ id_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int taosUpdateIdPool(id_pool_t *handle, int maxId) {
  id_pool_t *pIdPool = (id_pool_t*)handle;
  if (maxId <= pIdPool->maxId) {
    return -1;
  }

  int *idList, i;
  idList = (int *)malloc(sizeof(int) * (size_t)maxId);
  if (idList == NULL) {
    return -1;
  }
  for (i = 1; i < maxId; ++i) {
    idList[i - 1] = i;
  }

  if (pthread_mutex_lock(&pIdPool->mutex) != 0) perror("lock pIdPool Mutex");

  memcpy(idList, pIdPool->freeList, sizeof(int) * (size_t)pIdPool->maxId);
  pIdPool->numOfFree += (maxId - pIdPool->maxId);
  pIdPool->maxId = maxId;

  int *oldIdList = pIdPool->freeList;
  pIdPool->freeList = idList;
  free(oldIdList);

  if (pthread_mutex_unlock(&pIdPool->mutex) != 0) perror("unlock pIdPool Mutex");

  return 0;
}