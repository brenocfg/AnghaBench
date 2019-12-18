#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  offset; scalar_t__ vnode; scalar_t__ compLen; scalar_t__ numOfBlocks; } ;
struct TYPE_15__ {TYPE_1__ info; } ;
struct TYPE_14__ {int /*<<< orphan*/  f; scalar_t__ tsOrder; scalar_t__ numOfVnodes; int /*<<< orphan*/  fileSize; } ;
struct TYPE_13__ {scalar_t__ tsOrder; scalar_t__ numOfVnode; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ STSVnodeBlockInfo ;
typedef  TYPE_2__ STSBufFileHeader ;
typedef  TYPE_3__ STSBuf ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STSBufUpdateHeader (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  TSBufUpdateVnodeInfo (TYPE_3__*,scalar_t__,TYPE_1__*) ; 
 scalar_t__ TSQL_SO_ASC ; 
 scalar_t__ TSQL_SO_DESC ; 
 int /*<<< orphan*/  TS_COMP_FILE_MAGIC ; 
 TYPE_6__* addOneVnodeInfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (void*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getDataStartOffset () ; 
 TYPE_3__* tsBufCreate (int) ; 

STSBuf* tsBufCreateFromCompBlocks(const char* pData, int32_t numOfBlocks, int32_t len, int32_t order) {
  STSBuf* pTSBuf = tsBufCreate(true);

  STSVnodeBlockInfo* pBlockInfo = &(addOneVnodeInfo(pTSBuf, 0)->info);
  pBlockInfo->numOfBlocks = numOfBlocks;
  pBlockInfo->compLen = len;
  pBlockInfo->offset = getDataStartOffset();
  pBlockInfo->vnode = 0;

  // update prev vnode length info in file
  TSBufUpdateVnodeInfo(pTSBuf, pTSBuf->numOfVnodes - 1, pBlockInfo);

  fseek(pTSBuf->f, pBlockInfo->offset, SEEK_SET);
  fwrite((void*) pData, 1, len, pTSBuf->f);
  pTSBuf->fileSize += len;

  pTSBuf->tsOrder = order;
  assert(order == TSQL_SO_ASC || order == TSQL_SO_DESC);

  STSBufFileHeader header = {
      .magic = TS_COMP_FILE_MAGIC, .numOfVnode = pTSBuf->numOfVnodes, .tsOrder = pTSBuf->tsOrder};
  STSBufUpdateHeader(pTSBuf, &header);

  fsync(fileno(pTSBuf->f));

  return pTSBuf;
}