#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_14__ {int numOfElem; } ;
struct TYPE_13__ {int len; } ;
struct TYPE_18__ {int vnodeIndex; scalar_t__ order; int tsIndex; int blockIndex; } ;
struct TYPE_19__ {int numOfVnodes; TYPE_4__* pData; TYPE_2__ block; TYPE_1__ tsData; TYPE_6__ cur; } ;
struct TYPE_17__ {int numOfBlocks; } ;
struct TYPE_15__ {int vnode; } ;
struct TYPE_16__ {TYPE_3__ info; } ;
typedef  TYPE_5__ STSVnodeBlockInfo ;
typedef  TYPE_6__ STSCursor ;
typedef  TYPE_7__ STSBuf ;

/* Variables and functions */
 int TSDB_KEYSIZE ; 
 scalar_t__ TSQL_SO_ASC ; 
 scalar_t__ TSQL_SO_DESC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tsBufGetBlock (TYPE_7__*,int,int) ; 
 TYPE_5__* tsBufGetVnodeBlockInfo (TYPE_7__*,int) ; 
 int /*<<< orphan*/  tsBufResetPos (TYPE_7__*) ; 

bool tsBufNextPos(STSBuf* pTSBuf) {
  if (pTSBuf == NULL || pTSBuf->numOfVnodes == 0) {
    return false;
  }

  STSCursor* pCur = &pTSBuf->cur;

  // get the first/last position according to traverse order
  if (pCur->vnodeIndex == -1) {
    if (pCur->order == TSQL_SO_ASC) {
      tsBufGetBlock(pTSBuf, 0, 0);
      // list is empty
      if (pTSBuf->block.numOfElem == 0) {
        tsBufResetPos(pTSBuf);
        return false;
      } else {
        return true;
      }
    } else {
      int32_t vnodeIndex = pTSBuf->numOfVnodes - 1;

      int32_t            vnodeId = pTSBuf->pData[pCur->vnodeIndex].info.vnode;
      STSVnodeBlockInfo* pBlockInfo = tsBufGetVnodeBlockInfo(pTSBuf, vnodeId);
      int32_t            blockIndex = pBlockInfo->numOfBlocks - 1;

      tsBufGetBlock(pTSBuf, vnodeIndex, blockIndex);

      pCur->tsIndex = pTSBuf->block.numOfElem - 1;
      if (pTSBuf->block.numOfElem == 0) {
        tsBufResetPos(pTSBuf);
        return false;
      } else {
        return true;
      }
    }
  }

  int32_t step = pCur->order == TSQL_SO_ASC ? 1 : -1;

  while (1) {
    assert(pTSBuf->tsData.len == pTSBuf->block.numOfElem * TSDB_KEYSIZE);

    if ((pCur->order == TSQL_SO_ASC && pCur->tsIndex >= pTSBuf->block.numOfElem - 1) ||
        (pCur->order == TSQL_SO_DESC && pCur->tsIndex <= 0)) {
      int32_t vnodeId = pTSBuf->pData[pCur->vnodeIndex].info.vnode;

      STSVnodeBlockInfo* pBlockInfo = tsBufGetVnodeBlockInfo(pTSBuf, vnodeId);
      if (pBlockInfo == NULL || (pCur->blockIndex >= pBlockInfo->numOfBlocks - 1 && pCur->order == TSQL_SO_ASC) ||
          (pCur->blockIndex <= 0 && pCur->order == TSQL_SO_DESC)) {
        if ((pCur->vnodeIndex >= pTSBuf->numOfVnodes - 1 && pCur->order == TSQL_SO_ASC) ||
            (pCur->vnodeIndex <= 0 && pCur->order == TSQL_SO_DESC)) {
          pCur->vnodeIndex = -1;
          return false;
        }

        int32_t blockIndex = pCur->order == TSQL_SO_ASC ? 0 : pBlockInfo->numOfBlocks - 1;
        tsBufGetBlock(pTSBuf, pCur->vnodeIndex + step, blockIndex);
        break;

      } else {
        tsBufGetBlock(pTSBuf, pCur->vnodeIndex, pCur->blockIndex + step);
        break;
      }
    } else {
      pCur->tsIndex += step;
      break;
    }
  }

  return true;
}