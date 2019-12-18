#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_13__ {scalar_t__ pCachePool; } ;
struct TYPE_12__ {size_t numOfBlocks; size_t currentSlot; TYPE_1__** cacheBlocks; } ;
struct TYPE_11__ {int /*<<< orphan*/  vmutex; } ;
struct TYPE_10__ {size_t currentSlot; size_t numOfBlocks; int /*<<< orphan*/  blockId; int /*<<< orphan*/  firstSlot; } ;
struct TYPE_9__ {int /*<<< orphan*/  blockId; } ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SCachePool ;
typedef  TYPE_4__ SCacheInfo ;

/* Variables and functions */
 int /*<<< orphan*/  getFirstCacheSlot (size_t,size_t,TYPE_4__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__* vnodeList ; 

void getBasicCacheInfoSnapshot(SQuery *pQuery, SCacheInfo *pCacheInfo, int32_t vid) {
  // commitSlot here denotes the first uncommitted block in cache
  int32_t numOfBlocks = 0;
  int32_t lastSlot = 0;

  SCachePool *pPool = (SCachePool *)vnodeList[vid].pCachePool;
  pthread_mutex_lock(&pPool->vmutex);
  numOfBlocks = pCacheInfo->numOfBlocks;
  lastSlot = pCacheInfo->currentSlot;
  pthread_mutex_unlock(&pPool->vmutex);

  // make sure it is there, otherwise, return right away
  pQuery->currentSlot = lastSlot;
  pQuery->numOfBlocks = numOfBlocks;
  pQuery->firstSlot = getFirstCacheSlot(numOfBlocks, lastSlot, pCacheInfo);
  ;

  /*
   * Note: the block id is continuous increasing, never becomes smaller.
   *
   * blockId is the maximum block id in cache of current meter during query.
   * If any blocks' id are greater than this value, those blocks may be reallocated to other meters,
   * or assigned new data of this meter, on which the query is performed should be ignored.
   */
  if (pQuery->numOfBlocks > 0) {
    pQuery->blockId = pCacheInfo->cacheBlocks[pQuery->currentSlot]->blockId;
  }
}