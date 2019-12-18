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
struct TYPE_7__ {scalar_t__ nAllocSize; TYPE_2__* pFlushoutInfo; } ;
struct TYPE_9__ {TYPE_1__ flushoutData; } ;
struct TYPE_8__ {scalar_t__ dataFile; int /*<<< orphan*/  pColModel; int /*<<< orphan*/  dataFilePath; struct TYPE_8__* pNext; struct TYPE_8__* pHead; TYPE_3__ fileMeta; } ;
typedef  TYPE_2__ tFilePagesItem ;
typedef  TYPE_3__ tFileMeta ;
typedef  TYPE_2__ tExtMemBuffer ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (scalar_t__) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tColModelDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (TYPE_2__*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void tExtMemBufferDestroy(tExtMemBuffer **pMemBuffer) {
  if ((*pMemBuffer) == NULL) {
    return;
  }

  // release flush out info link
  tFileMeta *pFileMeta = &(*pMemBuffer)->fileMeta;
  if (pFileMeta->flushoutData.nAllocSize != 0 && pFileMeta->flushoutData.pFlushoutInfo != NULL) {
    tfree(pFileMeta->flushoutData.pFlushoutInfo);
  }

  // release all in-memory buffer pages
  tFilePagesItem *pFilePages = (*pMemBuffer)->pHead;
  while (pFilePages != NULL) {
    tFilePagesItem *pTmp = pFilePages;
    pFilePages = pFilePages->pNext;
    tfree(pTmp);
  }

  // close temp file
  if ((*pMemBuffer)->dataFile != 0) {
    int32_t ret = fclose((*pMemBuffer)->dataFile);
    if (ret != 0) {
      pError("failed to close file:%s, reason:%s", (*pMemBuffer)->dataFilePath, strerror(errno));
    }
    unlink((*pMemBuffer)->dataFilePath);
  }

  tColModelDestroy((*pMemBuffer)->pColModel);

  tfree(*pMemBuffer);
}