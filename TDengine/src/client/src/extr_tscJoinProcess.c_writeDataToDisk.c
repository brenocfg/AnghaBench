#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
struct TYPE_11__ {int len; int /*<<< orphan*/  allocSize; int /*<<< orphan*/  rawBuf; } ;
struct TYPE_10__ {int numOfElem; int compLen; int* payload; int tag; } ;
struct TYPE_9__ {int numOfVnodes; TYPE_6__ tsData; TYPE_2__* pData; int /*<<< orphan*/  fileSize; int /*<<< orphan*/  f; int /*<<< orphan*/  bufSize; int /*<<< orphan*/  assistBuf; TYPE_4__ block; } ;
struct TYPE_7__ {int numOfBlocks; int /*<<< orphan*/  compLen; } ;
struct TYPE_8__ {TYPE_1__ info; } ;
typedef  TYPE_3__ STSBuf ;
typedef  TYPE_4__ STSBlock ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TSDB_KEYSIZE ; 
 int /*<<< orphan*/  TWO_STAGE_COMP ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shrinkBuffer (TYPE_6__*) ; 
 int tsCompressTimestamp (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeDataToDisk(STSBuf* pTSBuf) {
  if (pTSBuf->tsData.len == 0) {
    return;
  }

  STSBlock* pBlock = &pTSBuf->block;

  pBlock->numOfElem = pTSBuf->tsData.len / TSDB_KEYSIZE;
  pBlock->compLen =
      tsCompressTimestamp(pTSBuf->tsData.rawBuf, pTSBuf->tsData.len, pTSBuf->tsData.len / TSDB_KEYSIZE, pBlock->payload,
                          pTSBuf->tsData.allocSize, TWO_STAGE_COMP, pTSBuf->assistBuf, pTSBuf->bufSize);

  int64_t r = fseek(pTSBuf->f, pTSBuf->fileSize, SEEK_SET);
  UNUSED(r);

  /*
   * format for output data:
   * 1. tags, number of ts, size after compressed, payload, size after compressed
   * 2. tags, number of ts, size after compressed, payload, size after compressed
   *
   * both side has the compressed length is used to support load data forwards/backwords.
   */
  fwrite(&pBlock->tag, sizeof(pBlock->tag), 1, pTSBuf->f);
  fwrite(&pBlock->numOfElem, sizeof(pBlock->numOfElem), 1, pTSBuf->f);

  fwrite(&pBlock->compLen, sizeof(pBlock->compLen), 1, pTSBuf->f);

  fwrite(pBlock->payload, (size_t)pBlock->compLen, 1, pTSBuf->f);

  fwrite(&pBlock->compLen, sizeof(pBlock->compLen), 1, pTSBuf->f);

  int32_t blockSize = sizeof(pBlock->tag) + sizeof(pBlock->numOfElem) + sizeof(pBlock->compLen) * 2 + pBlock->compLen;
  pTSBuf->fileSize += blockSize;

  pTSBuf->tsData.len = 0;

  pTSBuf->pData[pTSBuf->numOfVnodes - 1].info.compLen += blockSize;
  pTSBuf->pData[pTSBuf->numOfVnodes - 1].info.numOfBlocks += 1;

  shrinkBuffer(&pTSBuf->tsData);
}