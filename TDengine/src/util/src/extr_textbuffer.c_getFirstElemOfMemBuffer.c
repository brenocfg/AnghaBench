#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_8__** pBuffer; } ;
typedef  TYPE_5__ tMemBucketSegment ;
struct TYPE_17__ {scalar_t__ numOfPages; int startPageId; } ;
typedef  TYPE_6__ tFlushoutInfo ;
struct TYPE_18__ {char* data; } ;
typedef  TYPE_7__ tFilePage ;
struct TYPE_14__ {TYPE_6__* pFlushoutInfo; } ;
struct TYPE_15__ {scalar_t__ nFileSize; TYPE_3__ flushoutData; } ;
struct TYPE_19__ {scalar_t__ numOfElemsInBuffer; int nPageSize; int /*<<< orphan*/  dataFile; TYPE_4__ fileMeta; TYPE_2__* pHead; } ;
typedef  TYPE_8__ tExtMemBuffer ;
typedef  size_t int32_t ;
struct TYPE_12__ {char* data; } ;
struct TYPE_13__ {TYPE_1__ item; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  UNUSED (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t fread (TYPE_7__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

char *getFirstElemOfMemBuffer(tMemBucketSegment *pSeg, int32_t slotIdx, tFilePage *pPage) {
  tExtMemBuffer *pMemBuffer = pSeg->pBuffer[slotIdx];
  char *         thisVal = NULL;

  if (pSeg->pBuffer[slotIdx]->numOfElemsInBuffer != 0) {
    thisVal = pSeg->pBuffer[slotIdx]->pHead->item.data;
  } else {
    /*
     * no data in memory, load one page into memory
     */
    tFlushoutInfo *pFlushInfo = &pMemBuffer->fileMeta.flushoutData.pFlushoutInfo[0];
    assert(pFlushInfo->numOfPages == pMemBuffer->fileMeta.nFileSize);

    fseek(pMemBuffer->dataFile, pFlushInfo->startPageId * pMemBuffer->nPageSize, SEEK_SET);
    size_t ret = fread(pPage, pMemBuffer->nPageSize, 1, pMemBuffer->dataFile);
    UNUSED(ret);
    thisVal = pPage->data;
  }
  return thisVal;
}