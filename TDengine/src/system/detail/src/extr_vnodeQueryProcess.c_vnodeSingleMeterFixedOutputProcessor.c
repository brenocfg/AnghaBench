#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ offset; } ;
struct TYPE_19__ {scalar_t__ slot; scalar_t__ pos; scalar_t__ pointsRead; scalar_t__ pointsToRead; int /*<<< orphan*/  pGroupbyExpr; TYPE_1__ limit; int /*<<< orphan*/  over; } ;
struct TYPE_20__ {scalar_t__ pointsRead; TYPE_2__* pMeterQuerySupporter; TYPE_4__ query; } ;
struct TYPE_18__ {int /*<<< orphan*/  pResult; } ;
struct TYPE_17__ {scalar_t__ subgroupIdx; TYPE_3__ runtimeEnv; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;
typedef  TYPE_5__ SQInfo ;

/* Variables and functions */
 int QUERY_COMPLETED ; 
 int QUERY_NO_DATA_TO_CHECK ; 
 scalar_t__ Q_STATUS_EQUAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copyFromGroupBuf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doFinalizeResult (TYPE_3__*) ; 
 int /*<<< orphan*/  doRevisedResultsByLimit (TYPE_5__*) ; 
 int /*<<< orphan*/  doSkipResults (TYPE_3__*) ; 
 scalar_t__ getNumOfResult (TYPE_3__*) ; 
 scalar_t__ isGroupbyNormalCol (int /*<<< orphan*/ ) ; 
 scalar_t__ isQueryKilled (TYPE_4__*) ; 
 int isTopBottomQuery (TYPE_4__*) ; 
 int /*<<< orphan*/  moveDescOrderResultsToFront (TYPE_3__*) ; 
 int /*<<< orphan*/  vnodeScanAllData (TYPE_3__*) ; 

__attribute__((used)) static void vnodeSingleMeterFixedOutputProcessor(SQInfo *pQInfo) {
  SQuery *          pQuery = &pQInfo->query;
  SQueryRuntimeEnv *pRuntimeEnv = &pQInfo->pMeterQuerySupporter->runtimeEnv;

  assert(pQuery->slot >= 0 && pQuery->pos >= 0);

  vnodeScanAllData(pRuntimeEnv);
  doFinalizeResult(pRuntimeEnv);

  if (isQueryKilled(pQuery)) {
    return;
  }

  // since the numOfOutputElems must be identical for all sql functions that are allowed to be executed simutanelously.
  pQuery->pointsRead = getNumOfResult(pRuntimeEnv);
  assert(pQuery->pointsRead <= pQuery->pointsToRead &&
         Q_STATUS_EQUAL(pQuery->over, QUERY_COMPLETED | QUERY_NO_DATA_TO_CHECK));

  // must be top/bottom query if offset > 0
  if (pQuery->limit.offset > 0) {
    assert(isTopBottomQuery(pQuery));
  }

  if (isGroupbyNormalCol(pQuery->pGroupbyExpr)) {
    pQInfo->pMeterQuerySupporter->subgroupIdx = 0;
    pQuery->pointsRead = 0;
    copyFromGroupBuf(pQInfo, pRuntimeEnv->pResult);
  }

  doSkipResults(pRuntimeEnv);
  doRevisedResultsByLimit(pQInfo);
  moveDescOrderResultsToFront(pRuntimeEnv);

  pQInfo->pointsRead = pQuery->pointsRead;
}