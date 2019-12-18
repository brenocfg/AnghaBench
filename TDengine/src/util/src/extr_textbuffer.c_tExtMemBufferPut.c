#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ numOfElems; } ;
struct TYPE_6__ {TYPE_5__ item; } ;
typedef  TYPE_1__ tFilePagesItem ;
struct TYPE_7__ {int numOfPagesInMem; scalar_t__ numOfElemsPerPage; int /*<<< orphan*/  numOfElemsInBuffer; int /*<<< orphan*/  pColModel; TYPE_1__* pTail; int /*<<< orphan*/  numOfAllElems; } ;
typedef  TYPE_2__ tExtMemBuffer ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  tColModelAppend (int /*<<< orphan*/ ,TYPE_5__*,void*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tExtMemBufferAlloc (TYPE_2__*) ; 

int16_t tExtMemBufferPut(tExtMemBuffer *pMemBuffer, void *data, int32_t numOfRows) {
  if (numOfRows == 0) {
    return pMemBuffer->numOfPagesInMem;
  }

  tFilePagesItem *pLast = pMemBuffer->pTail;
  if (pLast == NULL) {
    if (!tExtMemBufferAlloc(pMemBuffer)) {
      return -1;
    }

    pLast = pMemBuffer->pTail;
  }

  if (pLast->item.numOfElems + numOfRows <= pMemBuffer->numOfElemsPerPage) {
    // enough space for records
    tColModelAppend(pMemBuffer->pColModel, &pLast->item, data, 0, numOfRows, numOfRows);
    pMemBuffer->numOfElemsInBuffer += numOfRows;
    pMemBuffer->numOfAllElems += numOfRows;
  } else {
    int32_t numOfRemainEntries = pMemBuffer->numOfElemsPerPage - pLast->item.numOfElems;
    tColModelAppend(pMemBuffer->pColModel, &pLast->item, data, 0, numOfRemainEntries, numOfRows);

    pMemBuffer->numOfElemsInBuffer += numOfRemainEntries;
    pMemBuffer->numOfAllElems += numOfRemainEntries;

    int32_t hasWritten = numOfRemainEntries;
    int32_t remain = numOfRows - numOfRemainEntries;

    while (remain > 0) {
      if (!tExtMemBufferAlloc(pMemBuffer)) {
        // failed to allocate memory buffer
        return -1;
      }

      int32_t numOfWriteElems = 0;
      if (remain > pMemBuffer->numOfElemsPerPage) {
        numOfWriteElems = pMemBuffer->numOfElemsPerPage;
      } else {
        numOfWriteElems = remain;
      }

      pMemBuffer->numOfAllElems += numOfWriteElems;

      pLast = pMemBuffer->pTail;
      tColModelAppend(pMemBuffer->pColModel, &pLast->item, data, hasWritten, numOfWriteElems, numOfRows);

      remain -= numOfWriteElems;
      pMemBuffer->numOfElemsInBuffer += numOfWriteElems;
      hasWritten += numOfWriteElems;
    }
  }

  return pMemBuffer->numOfPagesInMem;
}