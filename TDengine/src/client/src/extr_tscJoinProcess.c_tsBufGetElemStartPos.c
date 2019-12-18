#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  info; } ;
struct TYPE_12__ {int vnodeIndex; int blockIndex; } ;
struct TYPE_13__ {TYPE_9__* pData; TYPE_2__ cur; int /*<<< orphan*/  numOfVnodes; } ;
struct TYPE_11__ {int vnode; } ;
typedef  int /*<<< orphan*/  STSVnodeBlockInfo ;
typedef  TYPE_1__ STSElem ;
typedef  TYPE_2__ STSCursor ;
typedef  TYPE_3__ STSBuf ;

/* Variables and functions */
 int tsBufFindBlockByTag (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tsBufFindVnodeIndexFromId (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsBufGetBlock (TYPE_3__*,int,int) ; 
 TYPE_1__ tsBufGetElem (TYPE_3__*) ; 

STSElem tsBufGetElemStartPos(STSBuf* pTSBuf, int32_t vnodeId, int64_t tag) {
  STSElem elem = {.vnode = -1};

  if (pTSBuf == NULL) {
    return elem;
  }

  int32_t j = tsBufFindVnodeIndexFromId(pTSBuf->pData, pTSBuf->numOfVnodes, vnodeId);
  if (j == -1) {
    return elem;
  }

  // for debug purpose
  //  tsBufDisplay(pTSBuf);

  STSCursor*         pCur = &pTSBuf->cur;
  STSVnodeBlockInfo* pBlockInfo = &pTSBuf->pData[j].info;

  int32_t blockIndex = tsBufFindBlockByTag(pTSBuf, pBlockInfo, tag);
  if (blockIndex < 0) {
    return elem;
  }

  pCur->vnodeIndex = j;
  pCur->blockIndex = blockIndex;
  tsBufGetBlock(pTSBuf, j, blockIndex);

  return tsBufGetElem(pTSBuf);
}