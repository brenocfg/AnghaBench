#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {scalar_t__ numOfElems; } ;
typedef  TYPE_3__ tFilePage ;
typedef  size_t int32_t ;
struct TYPE_13__ {TYPE_2__* pCtx; } ;
struct TYPE_15__ {scalar_t__ offset; scalar_t__ numOfGroupResultPages; scalar_t__ subgroupIdx; char* meterOutputMMapBuf; int lastPageId; int groupResultSize; TYPE_4__ runtimeEnv; TYPE_1__* pSidSet; int /*<<< orphan*/  meterIdx; } ;
struct TYPE_14__ {scalar_t__ pointsToRead; size_t numOfOutputCols; int /*<<< orphan*/  pointsRead; int /*<<< orphan*/ * sdata; } ;
struct TYPE_11__ {scalar_t__ outputBytes; } ;
struct TYPE_10__ {scalar_t__ numOfSubSet; int /*<<< orphan*/  numOfSids; } ;
typedef  TYPE_4__ SQueryRuntimeEnv ;
typedef  TYPE_5__ SQuery ;
typedef  TYPE_6__ SMeterQuerySupportObj ;

/* Variables and functions */
 int DEFAULT_INTERN_BUF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mergeMetersResultToOneGroups (TYPE_6__*) ; 

void copyResToQueryResultBuf(SMeterQuerySupportObj *pSupporter, SQuery *pQuery) {
  if (pSupporter->offset == pSupporter->numOfGroupResultPages) {
    pSupporter->numOfGroupResultPages = 0;

    // current results of group has been sent to client, try next group
    mergeMetersResultToOneGroups(pSupporter);

    // set current query completed
    if (pSupporter->numOfGroupResultPages == 0 && pSupporter->subgroupIdx == pSupporter->pSidSet->numOfSubSet) {
      pSupporter->meterIdx = pSupporter->pSidSet->numOfSids;
      return;
    }
  }

  SQueryRuntimeEnv *pRuntimeEnv = &pSupporter->runtimeEnv;
  char *            pStart = pSupporter->meterOutputMMapBuf + DEFAULT_INTERN_BUF_SIZE * (pSupporter->lastPageId + 1) +
                 pSupporter->groupResultSize * pSupporter->offset;

  uint64_t numOfElem = ((tFilePage *)pStart)->numOfElems;
  assert(numOfElem <= pQuery->pointsToRead);

  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    memcpy(pQuery->sdata[i], pStart, pRuntimeEnv->pCtx[i].outputBytes * numOfElem + sizeof(tFilePage));
    pStart += pRuntimeEnv->pCtx[i].outputBytes * pQuery->pointsToRead + sizeof(tFilePage);
  }

  pQuery->pointsRead += numOfElem;
  pSupporter->offset += 1;
}