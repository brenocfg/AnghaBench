#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_9__ {int numOfPoints; scalar_t__* offset; } ;
struct TYPE_8__ {int maxBlocks; TYPE_3__** cacheBlocks; } ;
struct TYPE_7__ {scalar_t__ skey; } ;
typedef  scalar_t__ TSKEY ;
typedef  TYPE_1__ SQuery ;
typedef  TYPE_2__ SCacheInfo ;
typedef  TYPE_3__ SCacheBlock ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_1__*) ; 

__attribute__((used)) static int32_t binarySearchInCacheBlk(SCacheInfo *pCacheInfo, SQuery *pQuery, int32_t keyLen, int32_t firstSlot,
                                      int32_t lastSlot) {
  int32_t midSlot = 0;

  while (1) {
    int32_t numOfBlocks = (lastSlot - firstSlot + 1 + pCacheInfo->maxBlocks) % pCacheInfo->maxBlocks;
    if (numOfBlocks == 0) {
      numOfBlocks = pCacheInfo->maxBlocks;
    }

    midSlot = (firstSlot + (numOfBlocks >> 1)) % pCacheInfo->maxBlocks;
    SCacheBlock *pBlock = pCacheInfo->cacheBlocks[midSlot];

    TSKEY keyFirst = *((TSKEY *)pBlock->offset[0]);
    TSKEY keyLast = *((TSKEY *)(pBlock->offset[0] + (pBlock->numOfPoints - 1) * keyLen));

    if (numOfBlocks == 1) {
      break;
    }

    if (pQuery->skey > keyLast) {
      if (numOfBlocks == 2) break;
      if (!QUERY_IS_ASC_QUERY(pQuery)) {
        int          nextSlot = (midSlot + 1 + pCacheInfo->maxBlocks) % pCacheInfo->maxBlocks;
        SCacheBlock *pNextBlock = pCacheInfo->cacheBlocks[nextSlot];
        TSKEY        nextKeyFirst = *((TSKEY *)(pNextBlock->offset[0]));
        if (pQuery->skey < nextKeyFirst) break;
      }
      firstSlot = (midSlot + 1) % pCacheInfo->maxBlocks;
    } else if (pQuery->skey < keyFirst) {
      if (QUERY_IS_ASC_QUERY(pQuery)) {
        int          prevSlot = (midSlot - 1 + pCacheInfo->maxBlocks) % pCacheInfo->maxBlocks;
        SCacheBlock *pPrevBlock = pCacheInfo->cacheBlocks[prevSlot];
        TSKEY        prevKeyLast = *((TSKEY *)(pPrevBlock->offset[0] + (pPrevBlock->numOfPoints - 1) * keyLen));
        if (pQuery->skey > prevKeyLast) {
          break;
        }
      }
      lastSlot = (midSlot - 1 + pCacheInfo->maxBlocks) % pCacheInfo->maxBlocks;
    } else {
      break;  // got the slot
    }
  }

  return midSlot;
}