#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tColModel ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_20__ {int discard; int /*<<< orphan*/  prevRowOfInput; TYPE_10__* discardData; TYPE_4__* pDesc; int /*<<< orphan*/  rowSize; } ;
struct TYPE_19__ {TYPE_1__* pMeterMeta; } ;
struct TYPE_16__ {int /*<<< orphan*/  numOfGroupCols; } ;
struct TYPE_15__ {int /*<<< orphan*/  order; } ;
struct TYPE_18__ {scalar_t__ stime; scalar_t__ etime; TYPE_3__ groupbyExpr; TYPE_2__ order; int /*<<< orphan*/  intervalTimeUnit; int /*<<< orphan*/  nAggTimeInterval; } ;
struct TYPE_17__ {int /*<<< orphan*/ * pSchema; } ;
struct TYPE_14__ {int /*<<< orphan*/  precision; } ;
struct TYPE_13__ {scalar_t__ numOfElems; } ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SMeterMetaInfo ;
typedef  TYPE_7__ SLocalReducer ;
typedef  int /*<<< orphan*/  SInterpolationInfo ;

/* Variables and functions */
 int /*<<< orphan*/  tColModelAppend (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ taosGetIntervalStartTimestamp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosInitInterpoInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_5__*,int /*<<< orphan*/ ) ; 

void savePrevRecordAndSetupInterpoInfo(SLocalReducer *pLocalReducer, SSqlCmd *pCmd, SInterpolationInfo *pInterpoInfo) {
  // discard following dataset in the same group and reset the interpolation information
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  int16_t prec = pMeterMetaInfo->pMeterMeta->precision;

  int64_t stime = (pCmd->stime < pCmd->etime) ? pCmd->stime : pCmd->etime;
  int64_t revisedSTime = taosGetIntervalStartTimestamp(stime, pCmd->nAggTimeInterval, pCmd->intervalTimeUnit, prec);

  taosInitInterpoInfo(pInterpoInfo, pCmd->order.order, revisedSTime, pCmd->groupbyExpr.numOfGroupCols,
                      pLocalReducer->rowSize);

  pLocalReducer->discard = true;
  pLocalReducer->discardData->numOfElems = 0;

  tColModel *pModel = pLocalReducer->pDesc->pSchema;
  tColModelAppend(pModel, pLocalReducer->discardData, pLocalReducer->prevRowOfInput, 0, 1, 1);
}