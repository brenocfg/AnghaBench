#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  size_t int32_t ;
struct TYPE_20__ {size_t numOfFiles; int /*<<< orphan*/ * pHeaderFiles; } ;
struct TYPE_24__ {TYPE_1__ runtimeEnv; } ;
struct TYPE_23__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int pointsRead; } ;
struct TYPE_22__ {TYPE_5__* pMeterQuerySupporter; TYPE_2__ query; } ;
typedef  TYPE_1__ SQueryRuntimeEnv ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SQInfo ;
typedef  TYPE_4__ SPointInterpoSupporter ;
typedef  TYPE_5__ SMeterQuerySupportObj ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  doFinalizeResult (TYPE_1__*) ; 
 int /*<<< orphan*/  forwardCtxOutputBuf (TYPE_1__*,int) ; 
 int getNumOfResult (TYPE_1__*) ; 
 int /*<<< orphan*/  isFirstLastRowQuery (TYPE_2__*) ; 
 int /*<<< orphan*/  multimeterMultioutputHelper (TYPE_3__*,int*,int*,size_t,size_t) ; 
 int /*<<< orphan*/  normalizedFirstQueryRange (int,int,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  pointInterpSupporterDestroy (TYPE_4__*) ; 
 int /*<<< orphan*/  pointInterpSupporterInit (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  pointInterpSupporterSetData (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  resetMMapWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnodeScanAllData (TYPE_1__*) ; 

__attribute__((used)) static int64_t doCheckMetersInGroup(SQInfo *pQInfo, int32_t index, int32_t start) {
  SQuery *               pQuery = &pQInfo->query;
  SMeterQuerySupportObj *pSupporter = pQInfo->pMeterQuerySupporter;
  SQueryRuntimeEnv *     pRuntimeEnv = &pSupporter->runtimeEnv;

  bool dataInDisk = true;
  bool dataInCache = true;
  if (!multimeterMultioutputHelper(pQInfo, &dataInDisk, &dataInCache, index, start)) {
    return 0;
  }

#if DEFAULT_IO_ENGINE == IO_ENGINE_MMAP
  for (int32_t i = 0; i < pRuntimeEnv->numOfFiles; ++i) {
    resetMMapWindow(&pRuntimeEnv->pHeaderFiles[i]);
  }
#endif

  SPointInterpoSupporter pointInterpSupporter = {0};
  pointInterpSupporterInit(pQuery, &pointInterpSupporter);

  if (!normalizedFirstQueryRange(dataInDisk, dataInCache, pSupporter, &pointInterpSupporter)) {
    pointInterpSupporterDestroy(&pointInterpSupporter);
    return 0;
  }

  /*
   * here we set the value for before and after the specified time into the
   * parameter for interpolation query
   */
  pointInterpSupporterSetData(pQInfo, &pointInterpSupporter);
  pointInterpSupporterDestroy(&pointInterpSupporter);

  vnodeScanAllData(pRuntimeEnv);

  // first/last_row query, do not invoke the finalize for super table query
  if (!isFirstLastRowQuery(pQuery)) {
    doFinalizeResult(pRuntimeEnv);
  }

  int64_t numOfRes = getNumOfResult(pRuntimeEnv);
  assert(numOfRes == 1 || numOfRes == 0);

  // accumulate the point interpolation result
  if (numOfRes > 0) {
    pQuery->pointsRead += numOfRes;
    forwardCtxOutputBuf(pRuntimeEnv, numOfRes);
  }

  return numOfRes;
}