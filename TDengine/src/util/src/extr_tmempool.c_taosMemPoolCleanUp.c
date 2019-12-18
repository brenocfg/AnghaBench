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
struct TYPE_4__ {struct TYPE_4__* freeList; struct TYPE_4__* pool; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ pool_t ;
typedef  scalar_t__ mpool_h ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void taosMemPoolCleanUp(mpool_h handle) {
  pool_t *pool_p = (pool_t *)handle;

  pthread_mutex_destroy(&pool_p->mutex);
  if (pool_p->pool) free(pool_p->pool);
  if (pool_p->freeList) free(pool_p->freeList);
  memset(pool_p, 0, sizeof(*pool_p));
  free(pool_p);
}