#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_26__ {scalar_t__ hasUnprocessedRow; TYPE_3__* resColModel; int /*<<< orphan*/ ** pLocalDataSrc; int /*<<< orphan*/  hasPrevRow; int /*<<< orphan*/  discard; int /*<<< orphan*/  interpolationInfo; } ;
struct TYPE_25__ {TYPE_1__* pMeterMeta; } ;
struct TYPE_20__ {int /*<<< orphan*/  order; } ;
struct TYPE_24__ {scalar_t__ interpoType; scalar_t__ stime; scalar_t__ etime; int /*<<< orphan*/  nAggTimeInterval; int /*<<< orphan*/  intervalTimeUnit; TYPE_2__ order; } ;
struct TYPE_22__ {scalar_t__ numOfRows; TYPE_8__* pLocalReducer; } ;
struct TYPE_23__ {TYPE_4__ res; TYPE_6__ cmd; } ;
struct TYPE_21__ {int /*<<< orphan*/  maxCapacity; } ;
struct TYPE_19__ {int /*<<< orphan*/  precision; } ;
typedef  TYPE_4__ SSqlRes ;
typedef  TYPE_5__ SSqlObj ;
typedef  TYPE_6__ SSqlCmd ;
typedef  TYPE_7__ SMeterMetaInfo ;
typedef  TYPE_8__ SLocalReducer ;
typedef  int /*<<< orphan*/  SInterpolationInfo ;

/* Variables and functions */
 scalar_t__ TSDB_INTERPO_NONE ; 
 int /*<<< orphan*/  doInterpolateResult (TYPE_5__*,TYPE_8__*,int) ; 
 scalar_t__ isAllSourcesCompleted (TYPE_8__*) ; 
 int /*<<< orphan*/  resetEnvForNewResultset (TYPE_4__*,TYPE_6__*,TYPE_8__*) ; 
 scalar_t__ saveGroupResultInfo (TYPE_5__*) ; 
 scalar_t__ taosGetNumOfResultWithInterpo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ taosGetRevisedEndKey (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool doHandleLastRemainData(SSqlObj *pSql) {
  SSqlCmd *pCmd = &pSql->cmd;
  SSqlRes *pRes = &pSql->res;

  SLocalReducer *     pLocalReducer = pRes->pLocalReducer;
  SInterpolationInfo *pInterpoInfo = &pLocalReducer->interpolationInfo;

  bool prevGroupCompleted = (!pLocalReducer->discard) && pLocalReducer->hasUnprocessedRow;

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  int8_t precision = pMeterMetaInfo->pMeterMeta->precision;

  if ((isAllSourcesCompleted(pLocalReducer) && !pLocalReducer->hasPrevRow) || pLocalReducer->pLocalDataSrc[0] == NULL ||
      prevGroupCompleted) {
    // if interpoType == TSDB_INTERPO_NONE, return directly
    if (pCmd->interpoType != TSDB_INTERPO_NONE) {
      int64_t etime = (pCmd->stime < pCmd->etime) ? pCmd->etime : pCmd->stime;

      etime = taosGetRevisedEndKey(etime, pCmd->order.order, pCmd->nAggTimeInterval, pCmd->intervalTimeUnit, precision);
      int32_t rows = taosGetNumOfResultWithInterpo(pInterpoInfo, NULL, 0, pCmd->nAggTimeInterval, etime,
                                                   pLocalReducer->resColModel->maxCapacity);
      if (rows > 0) {  // do interpo
        doInterpolateResult(pSql, pLocalReducer, true);
      }
    }

    /*
     * 1. numOfRows == 0, means no interpolation results are generated.
     * 2. if all local data sources are consumed, and no un-processed rows exist.
     *
     * No results will be generated and query completed.
     */
    if (pRes->numOfRows > 0 || (isAllSourcesCompleted(pLocalReducer) && (!pLocalReducer->hasUnprocessedRow))) {
      return true;
    }

    // start to process result for a new group and save the result info of previous group
    if (saveGroupResultInfo(pSql)) {
      return true;
    }

    resetEnvForNewResultset(pRes, pCmd, pLocalReducer);
  }

  return false;
}