#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_18__ {int /*<<< orphan*/  maxCapacity; } ;
struct TYPE_17__ {int /*<<< orphan*/  numOfElems; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_1__* pFlushoutInfo; } ;
struct TYPE_13__ {TYPE_2__ flushoutData; } ;
struct TYPE_16__ {TYPE_8__* pColModel; TYPE_3__ fileMeta; } ;
struct TYPE_15__ {int rowIdx; int pageId; size_t flushoutIdx; TYPE_6__* pMemBuffer; TYPE_7__ filePage; } ;
struct TYPE_14__ {int numOfCompleted; int /*<<< orphan*/  numOfBuffer; } ;
struct TYPE_11__ {int numOfPages; } ;
typedef  TYPE_4__ SLocalReducer ;
typedef  TYPE_5__ SLocalDataSource ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tColModelDisplay (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tExtMemBufferLoadData (TYPE_6__*,TYPE_7__*,size_t,int) ; 

int32_t loadNewDataFromDiskFor(SLocalReducer *pLocalReducer, SLocalDataSource *pOneInterDataSrc,
                               bool *needAdjustLoserTree) {
  pOneInterDataSrc->rowIdx = 0;
  pOneInterDataSrc->pageId += 1;

  if (pOneInterDataSrc->pageId <
      pOneInterDataSrc->pMemBuffer->fileMeta.flushoutData.pFlushoutInfo[pOneInterDataSrc->flushoutIdx].numOfPages) {
    tExtMemBufferLoadData(pOneInterDataSrc->pMemBuffer, &(pOneInterDataSrc->filePage), pOneInterDataSrc->flushoutIdx,
                          pOneInterDataSrc->pageId);

#if defined(_DEBUG_VIEW)
    printf("new page load to buffer\n");
    tColModelDisplay(pOneInterDataSrc->pMemBuffer->pColModel, pOneInterDataSrc->filePage.data,
                     pOneInterDataSrc->filePage.numOfElems, pOneInterDataSrc->pMemBuffer->pColModel->maxCapacity);
#endif
    *needAdjustLoserTree = true;
  } else {
    pLocalReducer->numOfCompleted += 1;

    pOneInterDataSrc->rowIdx = -1;
    pOneInterDataSrc->pageId = -1;
    *needAdjustLoserTree = true;
  }

  return pLocalReducer->numOfBuffer;
}