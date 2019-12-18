#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_28__ {TYPE_13__* pSchema; } ;
typedef  TYPE_5__ tOrderDescriptor ;
struct TYPE_29__ {TYPE_1__* pSegs; } ;
typedef  TYPE_6__ tMemBucket ;
struct TYPE_30__ {int startPageId; scalar_t__ numOfPages; } ;
typedef  TYPE_7__ tFlushoutInfo ;
struct TYPE_27__ {scalar_t__ numOfElems; int /*<<< orphan*/  data; } ;
struct TYPE_31__ {struct TYPE_31__* pNext; TYPE_4__ item; } ;
typedef  TYPE_8__ tFilePagesItem ;
struct TYPE_32__ {scalar_t__ numOfElems; int /*<<< orphan*/  data; } ;
typedef  TYPE_9__ tFilePage ;
struct TYPE_25__ {size_t nLength; TYPE_7__* pFlushoutInfo; } ;
struct TYPE_26__ {scalar_t__ numOfElemsInFile; TYPE_2__ flushoutData; } ;
struct TYPE_22__ {int nElemSize; int numOfAllElems; int nPageSize; TYPE_8__* pHead; TYPE_3__ fileMeta; int /*<<< orphan*/  dataFile; } ;
typedef  TYPE_10__ tExtMemBuffer ;
typedef  size_t int32_t ;
struct TYPE_24__ {TYPE_10__** pBuffer; } ;
struct TYPE_23__ {size_t maxCapacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TSQL_SO_ASC ; 
 int /*<<< orphan*/  UNUSED (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 size_t fread (TYPE_9__*,int,int,int /*<<< orphan*/ ) ; 
 size_t fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 
 TYPE_10__* releaseBucketsExceptFor (TYPE_6__*,size_t,size_t) ; 
 int /*<<< orphan*/  tColDataQSort (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tColModelAppend (TYPE_13__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tExtMemBufferIsAllDataInMem (TYPE_10__*) ; 
 int /*<<< orphan*/  tfree (TYPE_9__*) ; 

__attribute__((used)) static tFilePage *loadIntoBucketFromDisk(tMemBucket *pMemBucket, int32_t segIdx, int32_t slotIdx,
                                         tOrderDescriptor *pDesc) {
  // release all data in other slots
  tExtMemBuffer *pMemBuffer = pMemBucket->pSegs[segIdx].pBuffer[slotIdx];
  tFilePage *    buffer = (tFilePage *)calloc(1, pMemBuffer->nElemSize * pMemBuffer->numOfAllElems + sizeof(tFilePage));
  int32_t        oldCapacity = pDesc->pSchema->maxCapacity;
  pDesc->pSchema->maxCapacity = pMemBuffer->numOfAllElems;

  if (!tExtMemBufferIsAllDataInMem(pMemBuffer)) {
    pMemBuffer = releaseBucketsExceptFor(pMemBucket, segIdx, slotIdx);
    assert(pMemBuffer->numOfAllElems > 0);

    // load data in disk to memory
    tFilePage *pPage = (tFilePage *)calloc(1, pMemBuffer->nPageSize);

    for (int32_t i = 0; i < pMemBuffer->fileMeta.flushoutData.nLength; ++i) {
      tFlushoutInfo *pFlushInfo = &pMemBuffer->fileMeta.flushoutData.pFlushoutInfo[i];

      int32_t ret = fseek(pMemBuffer->dataFile, pFlushInfo->startPageId * pMemBuffer->nPageSize, SEEK_SET);
      UNUSED(ret);

      for (uint32_t j = 0; j < pFlushInfo->numOfPages; ++j) {
        ret = fread(pPage, pMemBuffer->nPageSize, 1, pMemBuffer->dataFile);
        assert(pPage->numOfElems > 0);

        tColModelAppend(pDesc->pSchema, buffer, pPage->data, 0, pPage->numOfElems, pPage->numOfElems);
        printf("id: %d  count: %d\n", j, buffer->numOfElems);
      }
    }
    tfree(pPage);

    assert(buffer->numOfElems == pMemBuffer->fileMeta.numOfElemsInFile);
  }

  // load data in pMemBuffer to buffer
  tFilePagesItem *pListItem = pMemBuffer->pHead;
  while (pListItem != NULL) {
    tColModelAppend(pDesc->pSchema, buffer, pListItem->item.data, 0, pListItem->item.numOfElems,
                    pListItem->item.numOfElems);
    pListItem = pListItem->pNext;
  }

  tColDataQSort(pDesc, buffer->numOfElems, 0, buffer->numOfElems - 1, buffer->data, TSQL_SO_ASC);

  pDesc->pSchema->maxCapacity = oldCapacity;  // restore value
  return buffer;
}