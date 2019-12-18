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
struct TYPE_8__ {struct TYPE_8__* pNext; } ;
typedef  TYPE_2__ tFilePagesItem ;
struct TYPE_7__ {scalar_t__ nFileSize; scalar_t__ numOfElemsInFile; } ;
struct TYPE_9__ {scalar_t__ numOfAllElems; int /*<<< orphan*/ * dataFile; int /*<<< orphan*/ * pTail; TYPE_2__* pHead; scalar_t__ numOfPagesInMem; scalar_t__ numOfElemsInBuffer; TYPE_1__ fileMeta; } ;
typedef  TYPE_3__ tExtMemBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tExtMemBufferClearFlushoutInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 

void tExtMemBufferClear(tExtMemBuffer *pMemBuffer) {
  if (pMemBuffer == NULL || pMemBuffer->numOfAllElems == 0) return;

  /*
   * release all data in memory buffer
   */
  tFilePagesItem *first = pMemBuffer->pHead;
  while (first != NULL) {
    tFilePagesItem *ptmp = first;
    first = first->pNext;
    tfree(ptmp);
  }

  pMemBuffer->fileMeta.numOfElemsInFile = 0;
  pMemBuffer->fileMeta.nFileSize = 0;

  pMemBuffer->numOfElemsInBuffer = 0;
  pMemBuffer->numOfPagesInMem = 0;
  pMemBuffer->pHead = NULL;
  pMemBuffer->pTail = NULL;

  tExtMemBufferClearFlushoutInfo(pMemBuffer);

  if (pMemBuffer->dataFile != NULL) {
    // reset the write pointer to the header
    fseek(pMemBuffer->dataFile, 0, SEEK_SET);
  }
}