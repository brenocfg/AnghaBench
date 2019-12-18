#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ pCachePool; } ;
struct TYPE_13__ {scalar_t__ numOfPoints; scalar_t__* offset; } ;
struct TYPE_12__ {scalar_t__ numOfBlocks; size_t currentSlot; TYPE_5__** cacheBlocks; } ;
struct TYPE_11__ {int /*<<< orphan*/  count; } ;
struct TYPE_10__ {size_t vnode; scalar_t__ pointsPerBlock; int numOfColumns; int /*<<< orphan*/  freePoints; TYPE_1__* schema; scalar_t__ pCache; } ;
struct TYPE_9__ {int bytes; } ;
typedef  TYPE_2__ SMeterObj ;
typedef  TYPE_3__ SCachePool ;
typedef  TYPE_4__ SCacheInfo ;
typedef  TYPE_5__ SCacheBlock ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetch_sub_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 scalar_t__ vnodeAllocateCacheBlock (TYPE_2__*) ; 
 TYPE_6__* vnodeList ; 

int vnodeInsertPointToCache(SMeterObj *pObj, char *pData) {
  SCacheBlock *pCacheBlock;
  SCacheInfo * pInfo;
  SCachePool * pPool;

  pInfo = (SCacheInfo *)pObj->pCache;
  pPool = (SCachePool *)vnodeList[pObj->vnode].pCachePool;

  if (pInfo->numOfBlocks == 0) {
    if (vnodeAllocateCacheBlock(pObj) < 0) {
      return -1;
    }
  }

  if (pInfo->currentSlot < 0) return -1;
  pCacheBlock = pInfo->cacheBlocks[pInfo->currentSlot];
  if (pCacheBlock->numOfPoints >= pObj->pointsPerBlock) {
    if (vnodeAllocateCacheBlock(pObj) < 0) return -1;
    pCacheBlock = pInfo->cacheBlocks[pInfo->currentSlot];
  }

  for (int col = 0; col < pObj->numOfColumns; ++col) {
    memcpy(pCacheBlock->offset[col] + pCacheBlock->numOfPoints * pObj->schema[col].bytes, pData,
           pObj->schema[col].bytes);
    pData += pObj->schema[col].bytes;
  }

  atomic_fetch_sub_32(&pObj->freePoints, 1);
  pCacheBlock->numOfPoints++;
  pPool->count++;

  return 0;
}