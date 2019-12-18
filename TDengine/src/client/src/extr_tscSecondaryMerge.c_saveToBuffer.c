#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* pSchema; } ;
typedef  TYPE_1__ tOrderDescriptor ;
struct TYPE_11__ {scalar_t__ numOfElems; } ;
typedef  TYPE_2__ tFilePage ;
typedef  int /*<<< orphan*/  tExtMemBuffer ;
struct TYPE_12__ {scalar_t__ maxCapacity; } ;
typedef  TYPE_3__ tColModel ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tColModelAppend (TYPE_3__*,TYPE_2__*,void*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ tscFlushTmpBuffer (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,scalar_t__) ; 

int32_t saveToBuffer(tExtMemBuffer *pMemoryBuf, tOrderDescriptor *pDesc, tFilePage *pPage, void *data,
                     int32_t numOfRows, int32_t orderType) {
  if (pPage->numOfElems + numOfRows <= pDesc->pSchema->maxCapacity) {
    tColModelAppend(pDesc->pSchema, pPage, data, 0, numOfRows, numOfRows);
    return 0;
  }

  tColModel *pModel = pDesc->pSchema;

  int32_t numOfRemainEntries = pDesc->pSchema->maxCapacity - pPage->numOfElems;
  tColModelAppend(pModel, pPage, data, 0, numOfRemainEntries, numOfRows);

  /* current buffer is full, need to flushed to disk */
  assert(pPage->numOfElems == pDesc->pSchema->maxCapacity);
  int32_t ret = tscFlushTmpBuffer(pMemoryBuf, pDesc, pPage, orderType);
  if (ret != 0) {
    return -1;
  }

  int32_t remain = numOfRows - numOfRemainEntries;

  while (remain > 0) {
    int32_t numOfWriteElems = 0;
    if (remain > pModel->maxCapacity) {
      numOfWriteElems = pModel->maxCapacity;
    } else {
      numOfWriteElems = remain;
    }

    tColModelAppend(pModel, pPage, data, numOfRows - remain, numOfWriteElems, numOfRows);

    if (pPage->numOfElems == pModel->maxCapacity) {
      int32_t ret = tscFlushTmpBuffer(pMemoryBuf, pDesc, pPage, orderType);
      if (ret != 0) {
        return -1;
      }
    } else {
      pPage->numOfElems = numOfWriteElems;
    }

    remain -= numOfWriteElems;
    numOfRemainEntries += numOfWriteElems;
  }

  return 0;
}