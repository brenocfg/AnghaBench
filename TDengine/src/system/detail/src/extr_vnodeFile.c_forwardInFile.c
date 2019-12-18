#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_16__ {scalar_t__ numOfPoints; } ;
struct TYPE_15__ {scalar_t__ lastKeyOnFile; } ;
struct TYPE_12__ {scalar_t__ offset; } ;
struct TYPE_14__ {size_t numOfBlocks; scalar_t__ pos; size_t slot; size_t fileId; scalar_t__ lastKey; scalar_t__ skey; TYPE_1__ limit; TYPE_5__* pBlock; } ;
struct TYPE_13__ {scalar_t__ fileId; scalar_t__ numOfFiles; } ;
typedef  TYPE_2__ SVnodeObj ;
typedef  TYPE_3__ SQuery ;
typedef  TYPE_4__ SMeterObj ;
typedef  TYPE_5__ SCompBlock ;

/* Variables and functions */
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 int vnodeGetCompBlockInfo (TYPE_4__*,TYPE_3__*) ; 

int forwardInFile(SQuery *pQuery, int32_t slotIdx, int32_t step, SVnodeObj *pVnode, SMeterObj *pObj) {
  SCompBlock *pBlock = pQuery->pBlock;

  while (slotIdx < pQuery->numOfBlocks && slotIdx >= 0 && pQuery->limit.offset >= pBlock[slotIdx].numOfPoints) {
    pQuery->limit.offset -= pBlock[slotIdx].numOfPoints;
    slotIdx += step;
  }

  if (slotIdx < pQuery->numOfBlocks && slotIdx >= 0) {
    if (QUERY_IS_ASC_QUERY(pQuery)) {
      pQuery->pos = pQuery->limit.offset;
    } else {
      pQuery->pos = pBlock[slotIdx].numOfPoints - pQuery->limit.offset - 1;
    }
    pQuery->slot = slotIdx;
    pQuery->limit.offset = 0;

    return pQuery->numOfBlocks;
  } else {  // continue in next file, forward pQuery->limit.offset points
    int ret = 0;
    pQuery->slot = -1;
    pQuery->pos = -1;

    while (1) {
      pQuery->fileId += step;
      if ((pQuery->fileId > pVnode->fileId) || (pQuery->fileId < pVnode->fileId - pVnode->numOfFiles + 1)) {
        pQuery->lastKey = pObj->lastKeyOnFile;
        pQuery->skey = pQuery->lastKey + 1;
        return 0;
      }

      ret = vnodeGetCompBlockInfo(pObj, pQuery);
      if (ret == 0) continue;
      if (ret > 0) break;  // qualified file
    }

    if (ret > 0) {
      int startSlot = QUERY_IS_ASC_QUERY(pQuery) ? 0 : pQuery->numOfBlocks - 1;
      return forwardInFile(pQuery, startSlot, step, pVnode, pObj);
    } else {
      return ret;
    }
  }
}