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
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {scalar_t__* payload; scalar_t__ padding; scalar_t__ compLen; scalar_t__ tag; scalar_t__ numOfElem; } ;
struct TYPE_7__ {int /*<<< orphan*/  allocSize; int /*<<< orphan*/  rawBuf; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {int /*<<< orphan*/  f; int /*<<< orphan*/  bufSize; int /*<<< orphan*/  assistBuf; TYPE_1__ tsData; TYPE_3__ block; } ;
typedef  TYPE_2__ STSBuf ;
typedef  TYPE_3__ STSBlock ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ TSQL_SO_DESC ; 
 int /*<<< orphan*/  TWO_STAGE_COMP ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fread (scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsDecompressTimestamp (scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

STSBlock* readDataFromDisk(STSBuf* pTSBuf, int32_t order, bool decomp) {
  STSBlock* pBlock = &pTSBuf->block;

  // clear the memory buffer
  void* tmp = pBlock->payload;
  memset(pBlock, 0, sizeof(STSBlock));
  pBlock->payload = tmp;

  if (order == TSQL_SO_DESC) {
    /*
     * set the right position for the reversed traverse, the reversed traverse is started from
     * the end of each comp data block
     */
    fseek(pTSBuf->f, -sizeof(pBlock->padding), SEEK_CUR);
    fread(&pBlock->padding, sizeof(pBlock->padding), 1, pTSBuf->f);

    pBlock->compLen = pBlock->padding;
    int32_t offset = pBlock->compLen + sizeof(pBlock->compLen) * 2 + sizeof(pBlock->numOfElem) + sizeof(pBlock->tag);
    fseek(pTSBuf->f, -offset, SEEK_CUR);
  }

  fread(&pBlock->tag, sizeof(pBlock->tag), 1, pTSBuf->f);
  fread(&pBlock->numOfElem, sizeof(pBlock->numOfElem), 1, pTSBuf->f);

  fread(&pBlock->compLen, sizeof(pBlock->compLen), 1, pTSBuf->f);
  fread(pBlock->payload, (size_t)pBlock->compLen, 1, pTSBuf->f);

  if (decomp) {
    pTSBuf->tsData.len =
        tsDecompressTimestamp(pBlock->payload, pBlock->compLen, pBlock->numOfElem, pTSBuf->tsData.rawBuf,
                              pTSBuf->tsData.allocSize, TWO_STAGE_COMP, pTSBuf->assistBuf, pTSBuf->bufSize);
  }

  // read the comp length at the length of comp block
  fread(&pBlock->padding, sizeof(pBlock->padding), 1, pTSBuf->f);

  // for backwards traverse, set the start position at the end of previous block
  if (order == TSQL_SO_DESC) {
    int32_t offset = pBlock->compLen + sizeof(pBlock->compLen) * 2 + sizeof(pBlock->numOfElem) + sizeof(pBlock->tag);
    int64_t r = fseek(pTSBuf->f, -offset, SEEK_CUR);
    UNUSED(r);
  }

  return pBlock;
}