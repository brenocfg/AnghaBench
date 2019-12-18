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
struct TYPE_2__ {int maxId; int* freeList; scalar_t__ numOfFree; scalar_t__ freeSlot; } ;
typedef  TYPE_1__ id_pool_t ;

/* Variables and functions */

void taosIdPoolSetFreeList(void *handle) {
  id_pool_t *pIdPool;
  int        pos = 0;

  pIdPool = (id_pool_t *)handle;
  pIdPool->numOfFree = 0;
  pIdPool->freeSlot = 0;

  for (int i = 1; i < pIdPool->maxId; ++i) {
    if (pIdPool->freeList[i] == 0) {
      pIdPool->freeList[pos] = i;
      pIdPool->numOfFree++;
      pos++;
    }
  }
}