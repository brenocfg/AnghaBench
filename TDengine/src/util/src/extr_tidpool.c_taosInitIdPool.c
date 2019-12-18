#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int maxId; int numOfFree; int* freeList; int /*<<< orphan*/  mutex; scalar_t__ freeSlot; } ;
typedef  TYPE_1__ id_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pTrace (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *taosInitIdPool(int maxId) {
  id_pool_t *pIdPool;
  int *      idList, i;

  if (maxId < 3) maxId = 3;

  pIdPool = (id_pool_t *)malloc(sizeof(id_pool_t));
  if (pIdPool == NULL) return NULL;

  idList = (int *)malloc(sizeof(int) * (size_t)maxId);
  if (idList == NULL) {
    free(pIdPool);
    return NULL;
  }

  memset(pIdPool, 0, sizeof(id_pool_t));
  pIdPool->maxId = maxId;
  pIdPool->numOfFree = maxId - 1;
  pIdPool->freeSlot = 0;
  pIdPool->freeList = idList;

  pthread_mutex_init(&pIdPool->mutex, NULL);

  for (i = 1; i < maxId; ++i) idList[i - 1] = i;

  pTrace("pool:%p is setup, maxId:%d", pIdPool, pIdPool->maxId);

  return (void *)pIdPool;
}