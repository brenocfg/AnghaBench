#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_16__ {int numOfElem; int /*<<< orphan*/  compLen; int /*<<< orphan*/  payload; } ;
struct TYPE_12__ {int len; int /*<<< orphan*/  allocSize; int /*<<< orphan*/  rawBuf; } ;
struct TYPE_14__ {size_t vnodeIndex; size_t blockIndex; scalar_t__ order; int tsIndex; } ;
struct TYPE_15__ {TYPE_2__ tsData; int /*<<< orphan*/  bufSize; int /*<<< orphan*/  assistBuf; TYPE_6__ block; TYPE_4__ cur; TYPE_1__* pData; } ;
struct TYPE_13__ {size_t numOfBlocks; } ;
struct TYPE_11__ {TYPE_3__ info; } ;
typedef  TYPE_3__ STSVnodeBlockInfo ;
typedef  TYPE_4__ STSCursor ;
typedef  TYPE_5__ STSBuf ;
typedef  TYPE_6__ STSBlock ;

/* Variables and functions */
 int TSDB_KEYSIZE ; 
 scalar_t__ TSQL_SO_ASC ; 
 scalar_t__ TSQL_SO_DESC ; 
 int /*<<< orphan*/  TWO_STAGE_COMP ; 
 size_t abs (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * readDataFromDisk (TYPE_5__*,scalar_t__,int) ; 
 int tsBufFindBlock (TYPE_5__*,TYPE_3__*,size_t) ; 
 int tsDecompressTimestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsBufGetBlock(STSBuf* pTSBuf, int32_t vnodeIndex, int32_t blockIndex) {
  STSVnodeBlockInfo* pBlockInfo = &pTSBuf->pData[vnodeIndex].info;
  if (pBlockInfo->numOfBlocks <= blockIndex) {
    assert(false);
  }

  STSCursor* pCur = &pTSBuf->cur;
  if (pCur->vnodeIndex == vnodeIndex && ((pCur->blockIndex <= blockIndex && pCur->order == TSQL_SO_ASC) ||
                                         (pCur->blockIndex >= blockIndex && pCur->order == TSQL_SO_DESC))) {
    int32_t i = 0;
    bool    decomp = false;
    int32_t step = abs(blockIndex - pCur->blockIndex);

    while ((++i) <= step) {
      if (readDataFromDisk(pTSBuf, pCur->order, decomp) == NULL) {
        return;
      }
    }
  } else {
    if (tsBufFindBlock(pTSBuf, pBlockInfo, blockIndex) == -1) {
      assert(false);
    }
  }

  STSBlock* pBlock = &pTSBuf->block;
  pTSBuf->tsData.len =
      tsDecompressTimestamp(pBlock->payload, pBlock->compLen, pBlock->numOfElem, pTSBuf->tsData.rawBuf,
                            pTSBuf->tsData.allocSize, TWO_STAGE_COMP, pTSBuf->assistBuf, pTSBuf->bufSize);

  assert(pTSBuf->tsData.len / TSDB_KEYSIZE == pBlock->numOfElem);

  pCur->vnodeIndex = vnodeIndex;
  pCur->blockIndex = blockIndex;

  pCur->tsIndex = (pCur->order == TSQL_SO_ASC) ? 0 : pBlock->numOfElem - 1;
}