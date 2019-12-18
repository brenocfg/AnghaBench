#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_14__ {scalar_t__ offset; } ;
struct TYPE_16__ {scalar_t__ skey; scalar_t__ ekey; scalar_t__ numOfFilterCols; scalar_t__ interpoType; int pointsRead; int pointsToRead; int /*<<< orphan*/  over; TYPE_1__ limit; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pTSBuf; TYPE_3__* pQuery; } ;
typedef  TYPE_2__ SQueryRuntimeEnv ;
typedef  TYPE_3__ SQuery ;
typedef  int /*<<< orphan*/  SMeterQuerySupportObj ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_COMPLETED ; 
 scalar_t__ QUERY_IS_ASC_QUERY (TYPE_3__*) ; 
 int /*<<< orphan*/  QUERY_NOT_COMPLETED ; 
 int /*<<< orphan*/  QUERY_NO_DATA_TO_CHECK ; 
 int /*<<< orphan*/  QUERY_RESBUF_FULL ; 
 scalar_t__ Q_STATUS_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TSDB_INTERPO_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  doFinalizeResult (TYPE_2__*) ; 
 int /*<<< orphan*/  forwardCtxOutputBuf (TYPE_2__*,int) ; 
 int /*<<< orphan*/  forwardIntervalQueryRange (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int getNumOfResult (TYPE_2__*) ; 
 int /*<<< orphan*/  initCtxOutputBuf (TYPE_2__*) ; 
 scalar_t__ isQueryKilled (TYPE_3__*) ; 
 int /*<<< orphan*/  setQueryStatus (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnodeScanAllData (TYPE_2__*) ; 

__attribute__((used)) static void vnodeSingleMeterIntervalMainLooper(SMeterQuerySupportObj *pSupporter, SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  while (1) {
    assert((pQuery->skey <= pQuery->ekey && QUERY_IS_ASC_QUERY(pQuery)) ||
           (pQuery->skey >= pQuery->ekey && !QUERY_IS_ASC_QUERY(pQuery)));

    initCtxOutputBuf(pRuntimeEnv);

    vnodeScanAllData(pRuntimeEnv);
    if (isQueryKilled(pQuery)) {
      return;
    }

    assert(!Q_STATUS_EQUAL(pQuery->over, QUERY_NOT_COMPLETED));

    // clear tag, used to decide if the whole interval query is completed or not
    pQuery->over &= (~QUERY_COMPLETED);
    doFinalizeResult(pRuntimeEnv);

    int64_t maxOutput = getNumOfResult(pRuntimeEnv);

    // here we can ignore the records in case of no interpolation
    if ((pQuery->numOfFilterCols > 0 || pRuntimeEnv->pTSBuf != NULL) && pQuery->limit.offset > 0 &&
        pQuery->interpoType == TSDB_INTERPO_NONE) { // maxOutput <= 0, means current query does not generate any results
      // todo handle offset, in case of top/bottom interval query
      if (maxOutput > 0) {
        pQuery->limit.offset--;
      }
    } else {
      pQuery->pointsRead += maxOutput;
      forwardCtxOutputBuf(pRuntimeEnv, maxOutput);
    }

    if (Q_STATUS_EQUAL(pQuery->over, QUERY_NO_DATA_TO_CHECK)) {
      break;
    }

    forwardIntervalQueryRange(pSupporter, pRuntimeEnv);
    if (Q_STATUS_EQUAL(pQuery->over, QUERY_COMPLETED)) {
      break;
    }

    /*
     * the scan limitation mechanism is upon here,
     * 1. since there is only one(k) record is generated in one scan operation
     * 2. remain space is not sufficient for next query output, abort
     */
    if ((pQuery->pointsRead % pQuery->pointsToRead == 0 && pQuery->pointsRead != 0) ||
        ((pQuery->pointsRead + maxOutput) > pQuery->pointsToRead)) {
      setQueryStatus(pQuery, QUERY_RESBUF_FULL);
      break;
    }
  }
}