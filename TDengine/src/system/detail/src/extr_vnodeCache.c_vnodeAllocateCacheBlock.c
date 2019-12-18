#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int64_t ;
struct TYPE_21__ {scalar_t__ blockId; int notFree; int index; char** offset; int slot; TYPE_5__* pMeterObj; } ;
struct TYPE_20__ {int unCommittedBlocks; int maxBlocks; int currentSlot; int numOfBlocks; scalar_t__ blocks; TYPE_8__** cacheBlocks; } ;
struct TYPE_19__ {int count; int freeSlot; int threshold; int notFreeSlots; int /*<<< orphan*/  vmutex; scalar_t__* pMem; } ;
struct TYPE_18__ {int vnode; int numOfColumns; int pointsPerBlock; int /*<<< orphan*/  meterId; int /*<<< orphan*/  sid; TYPE_1__* schema; scalar_t__ pCache; } ;
struct TYPE_15__ {int totalBlocks; } ;
struct TYPE_17__ {int commitTime; TYPE_2__ cacheNumOfBlocks; } ;
struct TYPE_16__ {int /*<<< orphan*/ * commitTimer; TYPE_4__ cfg; scalar_t__ pCachePool; } ;
struct TYPE_14__ {int bytes; } ;
typedef  TYPE_3__ SVnodeObj ;
typedef  TYPE_4__ SVnodeCfg ;
typedef  TYPE_5__ SMeterObj ;
typedef  TYPE_6__ SCachePool ;
typedef  TYPE_7__ SCacheInfo ;
typedef  TYPE_8__ SCacheBlock ;

/* Variables and functions */
 int /*<<< orphan*/  dError (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dTrace (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taosTmrStart (int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeCreateCommitThread (TYPE_3__*) ; 
 int /*<<< orphan*/  vnodeFreeCacheBlock (TYPE_8__*) ; 
 TYPE_3__* vnodeList ; 
 int /*<<< orphan*/  vnodeProcessCommitTimer ; 
 int /*<<< orphan*/  vnodeTmrCtrl ; 

int vnodeAllocateCacheBlock(SMeterObj *pObj) {
  int          index;
  SCachePool * pPool;
  SCacheBlock *pCacheBlock;
  SCacheInfo * pInfo;
  SVnodeObj *  pVnode;
  int          skipped = 0, commit = 0;

  pVnode = vnodeList + pObj->vnode;
  pPool = (SCachePool *)pVnode->pCachePool;
  pInfo = (SCacheInfo *)pObj->pCache;
  SVnodeCfg *pCfg = &(vnodeList[pObj->vnode].cfg);

  if (pPool == NULL) return -1;
  pthread_mutex_lock(&pPool->vmutex);

  if (pInfo == NULL || pInfo->cacheBlocks == NULL) {
    pthread_mutex_unlock(&pPool->vmutex);
    dError("vid:%d sid:%d id:%s, meter is not there", pObj->vnode, pObj->sid, pObj->meterId);
    return -1;
  }

  if (pPool->count <= 1) {
    if (pVnode->commitTimer == NULL)
      pVnode->commitTimer = taosTmrStart(vnodeProcessCommitTimer, pCfg->commitTime * 1000, pVnode, vnodeTmrCtrl);
  }

  if (pInfo->unCommittedBlocks >= pInfo->maxBlocks-1) {
    vnodeCreateCommitThread(pVnode);
    pthread_mutex_unlock(&pPool->vmutex);
    dError("vid:%d sid:%d id:%s, all blocks are not committed yet....", pObj->vnode, pObj->sid, pObj->meterId);
    return -1;
  }

  while (1) {
    pCacheBlock = (SCacheBlock *)(pPool->pMem[((int64_t)pPool->freeSlot)]);
    if (pCacheBlock->blockId == 0) break;

    if (pCacheBlock->notFree) {
      pPool->freeSlot++;
      pPool->freeSlot = pPool->freeSlot % pCfg->cacheNumOfBlocks.totalBlocks;
      skipped++;
      if (skipped > pPool->threshold) {
        vnodeCreateCommitThread(pVnode);
        pthread_mutex_unlock(&pPool->vmutex);
        dError("vid:%d sid:%d id:%s, committing process is too slow, notFreeSlots:%d....",
               pObj->vnode, pObj->sid, pObj->meterId, pPool->notFreeSlots);
        return -1;
      }
    } else {
      SMeterObj  *pRelObj = pCacheBlock->pMeterObj;
      SCacheInfo *pRelInfo = (SCacheInfo *)pRelObj->pCache;
      int firstSlot = (pRelInfo->currentSlot - pRelInfo->numOfBlocks + 1 + pRelInfo->maxBlocks) % pRelInfo->maxBlocks;
      pCacheBlock = pRelInfo->cacheBlocks[firstSlot];
      if (pCacheBlock) {
        pPool->freeSlot = pCacheBlock->index;
        vnodeFreeCacheBlock(pCacheBlock);
        break;
      } else {
        pPool->freeSlot = (pPool->freeSlot + 1) % pCfg->cacheNumOfBlocks.totalBlocks;
        skipped++;
      }
    }
  }

  index = pPool->freeSlot;
  pPool->freeSlot++;
  pPool->freeSlot = pPool->freeSlot % pCfg->cacheNumOfBlocks.totalBlocks;
  pPool->notFreeSlots++;

  pCacheBlock->pMeterObj = pObj;
  pCacheBlock->notFree = 1;
  pCacheBlock->index = index;

  pCacheBlock->offset[0] = ((char *)(pCacheBlock)) + sizeof(SCacheBlock) + pObj->numOfColumns * sizeof(char *);
  for (int col = 1; col < pObj->numOfColumns; ++col)
    pCacheBlock->offset[col] = pCacheBlock->offset[col - 1] + pObj->schema[col - 1].bytes * pObj->pointsPerBlock;

  pInfo->numOfBlocks++;
  pInfo->blocks++;
  pInfo->unCommittedBlocks++;
  pInfo->currentSlot = (pInfo->currentSlot + 1) % pInfo->maxBlocks;
  pCacheBlock->blockId = pInfo->blocks;
  pCacheBlock->slot = pInfo->currentSlot;
  if (pInfo->numOfBlocks > pInfo->maxBlocks) {
    pCacheBlock = pInfo->cacheBlocks[pInfo->currentSlot];
    vnodeFreeCacheBlock(pCacheBlock);
  }

  pInfo->cacheBlocks[pInfo->currentSlot] = (SCacheBlock *)(pPool->pMem[(int64_t)index]);
  dTrace("vid:%d sid:%d id:%s, allocate a cache block, numOfBlocks:%d, slot:%d, index:%d notFreeSlots:%d blocks:%d",
         pObj->vnode, pObj->sid, pObj->meterId, pInfo->numOfBlocks, pInfo->currentSlot, index, pPool->notFreeSlots,
         pInfo->blocks);

  if (((pPool->notFreeSlots > pPool->threshold) || (pInfo->unCommittedBlocks >= pInfo->maxBlocks / 2))) {
    dTrace("vid:%d sid:%d id:%s, too many unCommitted slots, unCommitted:%d notFreeSlots:%d",
           pObj->vnode, pObj->sid, pObj->meterId, pInfo->unCommittedBlocks, pPool->notFreeSlots);
    vnodeCreateCommitThread(pVnode);
    commit = 1;
  }

  pthread_mutex_unlock(&pPool->vmutex);

  return commit;
}