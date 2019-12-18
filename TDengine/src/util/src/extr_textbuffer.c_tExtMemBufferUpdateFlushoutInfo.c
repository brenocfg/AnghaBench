#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ numOfPages; scalar_t__ startPageId; } ;
typedef  TYPE_2__ tFlushoutInfo ;
struct TYPE_7__ {size_t nLength; size_t nAllocSize; TYPE_2__* pFlushoutInfo; } ;
struct TYPE_9__ {TYPE_1__ flushoutData; } ;
typedef  TYPE_3__ tFileMeta ;
struct TYPE_10__ {scalar_t__ flushModel; scalar_t__ numOfPagesInMem; TYPE_3__ fileMeta; } ;
typedef  TYPE_4__ tExtMemBuffer ;

/* Variables and functions */
 scalar_t__ MULTIPLE_APPEND_MODEL ; 
 int /*<<< orphan*/  allocFlushoutInfoEntries (TYPE_3__*) ; 

__attribute__((used)) static bool tExtMemBufferUpdateFlushoutInfo(tExtMemBuffer *pMemBuffer) {
  tFileMeta *pFileMeta = &pMemBuffer->fileMeta;

  if (pMemBuffer->flushModel == MULTIPLE_APPEND_MODEL) {
    if (pFileMeta->flushoutData.nLength == pFileMeta->flushoutData.nAllocSize && !allocFlushoutInfoEntries(pFileMeta)) {
      return false;
    }

    tFlushoutInfo *pFlushoutInfo = &pFileMeta->flushoutData.pFlushoutInfo[pFileMeta->flushoutData.nLength];
    if (pFileMeta->flushoutData.nLength == 0) {
      pFlushoutInfo->startPageId = 0;
    } else {
      pFlushoutInfo->startPageId =
          pFileMeta->flushoutData.pFlushoutInfo[pFileMeta->flushoutData.nLength - 1].startPageId +
          pFileMeta->flushoutData.pFlushoutInfo[pFileMeta->flushoutData.nLength - 1].numOfPages;
    }

    // only the page still in buffer is flushed out to disk
    pFlushoutInfo->numOfPages = pMemBuffer->numOfPagesInMem;
    pFileMeta->flushoutData.nLength += 1;
  } else {
    // always update the first flushout array in single_flush_model
    pFileMeta->flushoutData.nLength = 1;
    tFlushoutInfo *pFlushoutInfo = &pFileMeta->flushoutData.pFlushoutInfo[0];
    pFlushoutInfo->numOfPages += pMemBuffer->numOfPagesInMem;
  }

  return true;
}