#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ pCachePool; } ;
struct TYPE_11__ {scalar_t__ blockId; int /*<<< orphan*/  index; int /*<<< orphan*/  slot; scalar_t__ notFree; TYPE_1__* pMeterObj; } ;
struct TYPE_10__ {scalar_t__ numOfBlocks; } ;
struct TYPE_9__ {int /*<<< orphan*/  notFreeSlots; } ;
struct TYPE_8__ {size_t vnode; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; scalar_t__ pCache; } ;
typedef  TYPE_1__ SMeterObj ;
typedef  TYPE_2__ SCachePool ;
typedef  TYPE_3__ SCacheInfo ;
typedef  TYPE_4__ SCacheBlock ;

/* Variables and functions */
 int /*<<< orphan*/  dError (char*,...) ; 
 int /*<<< orphan*/  dTrace (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* vnodeList ; 

int vnodeFreeCacheBlock(SCacheBlock *pCacheBlock) {
  SMeterObj * pObj;
  SCacheInfo *pInfo;

  if (pCacheBlock == NULL) return -1;

  pObj = pCacheBlock->pMeterObj;
  pInfo = (SCacheInfo *)pObj->pCache;

  if (pObj) {
    pInfo->numOfBlocks--;

    if (pInfo->numOfBlocks < 0) {
      dError("vid:%d sid:%d id:%s, numOfBlocks:%d shall never be negative", pObj->vnode, pObj->sid, pObj->meterId,
           pInfo->numOfBlocks);
    }

    if (pCacheBlock->blockId == 0) {
      dError("vid:%d sid:%d id:%s, double free", pObj->vnode, pObj->sid, pObj->meterId);
    }

    SCachePool *pPool = (SCachePool *)vnodeList[pObj->vnode].pCachePool;
    if (pCacheBlock->notFree) {
      pPool->notFreeSlots--;
      dTrace("vid:%d sid:%d id:%s, cache block is not free, slot:%d, index:%d notFreeSlots:%d",
             pObj->vnode, pObj->sid, pObj->meterId, pCacheBlock->slot, pCacheBlock->index, pPool->notFreeSlots);
    }

    dTrace("vid:%d sid:%d id:%s, free a cache block, numOfBlocks:%d, slot:%d, index:%d notFreeSlots:%d",
           pObj->vnode, pObj->sid, pObj->meterId, pInfo->numOfBlocks, pCacheBlock->slot, pCacheBlock->index,
           pPool->notFreeSlots);

    memset(pCacheBlock, 0, sizeof(SCacheBlock));

  } else {
    dError("BUG, pObj is null");
  }

  return 0;
}