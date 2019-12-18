#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_21__ {int /*<<< orphan*/  rowSize; int /*<<< orphan*/  interpolationInfo; int /*<<< orphan*/  offset; } ;
struct TYPE_20__ {TYPE_2__* pMeterMeta; } ;
struct TYPE_17__ {int /*<<< orphan*/  numOfGroupCols; } ;
struct TYPE_16__ {int /*<<< orphan*/  order; } ;
struct TYPE_14__ {int /*<<< orphan*/  offset; } ;
struct TYPE_19__ {scalar_t__ interpoType; scalar_t__ stime; scalar_t__ etime; TYPE_4__ groupbyExpr; TYPE_3__ order; int /*<<< orphan*/  intervalTimeUnit; int /*<<< orphan*/  nAggTimeInterval; TYPE_1__ limit; } ;
struct TYPE_18__ {scalar_t__ numOfTotal; scalar_t__ numOfRows; } ;
struct TYPE_15__ {int /*<<< orphan*/  precision; } ;
typedef  TYPE_5__ SSqlRes ;
typedef  TYPE_6__ SSqlCmd ;
typedef  TYPE_7__ SMeterMetaInfo ;
typedef  TYPE_8__ SLocalReducer ;

/* Variables and functions */
 scalar_t__ TSDB_INTERPO_NONE ; 
 scalar_t__ taosGetIntervalStartTimestamp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosInitInterpoInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resetEnvForNewResultset(SSqlRes *pRes, SSqlCmd *pCmd, SLocalReducer *pLocalReducer) {
  // In handling data in other groups, we need to reset the interpolation information for a new group data
  pRes->numOfRows = 0;
  pRes->numOfTotal = 0;
  pCmd->limit.offset = pLocalReducer->offset;

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  int16_t precision = pMeterMetaInfo->pMeterMeta->precision;

  // for group result interpolation, do not return if not data is generated
  if (pCmd->interpoType != TSDB_INTERPO_NONE) {
    int64_t stime = (pCmd->stime < pCmd->etime) ? pCmd->stime : pCmd->etime;
    int64_t newTime = taosGetIntervalStartTimestamp(stime, pCmd->nAggTimeInterval, pCmd->intervalTimeUnit, precision);

    taosInitInterpoInfo(&pLocalReducer->interpolationInfo, pCmd->order.order, newTime, pCmd->groupbyExpr.numOfGroupCols,
                        pLocalReducer->rowSize);
  }
}