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
struct TYPE_2__ {int maxId; scalar_t__* freeList; scalar_t__ freeSlot; scalar_t__ numOfFree; } ;
typedef  TYPE_1__ id_pool_t ;

/* Variables and functions */

void taosIdPoolReinit(void *handle) {
  id_pool_t *pIdPool;

  pIdPool = (id_pool_t *)handle;
  pIdPool->numOfFree = 0;
  pIdPool->freeSlot = 0;

  for (int i = 0; i < pIdPool->maxId; ++i) pIdPool->freeList[i] = 0;
}