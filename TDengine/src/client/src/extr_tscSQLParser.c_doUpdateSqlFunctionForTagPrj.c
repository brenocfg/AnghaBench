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

/* Type definitions */
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_20__ {int /*<<< orphan*/  pMeterMeta; } ;
struct TYPE_19__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_18__ {TYPE_1__ fieldsInfo; } ;
struct TYPE_15__ {scalar_t__ colId; size_t colIdx; } ;
struct TYPE_17__ {scalar_t__ functionId; int /*<<< orphan*/  interResBytes; scalar_t__ resBytes; int /*<<< orphan*/  resType; TYPE_3__* param; TYPE_2__ colInfo; } ;
struct TYPE_16__ {int /*<<< orphan*/  i64Key; } ;
typedef  TYPE_4__ SSqlExpr ;
typedef  TYPE_5__ SSqlCmd ;
typedef  TYPE_6__ SSchema ;
typedef  TYPE_7__ SMeterMetaInfo ;

/* Variables and functions */
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 scalar_t__ TSDB_FUNC_TAG_DUMMY ; 
 scalar_t__ TSDB_FUNC_TS_DUMMY ; 
 int /*<<< orphan*/  getResultDataInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 TYPE_6__* tsGetSchema (int /*<<< orphan*/ ) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* tscSqlExprGet (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static void doUpdateSqlFunctionForTagPrj(SSqlCmd* pCmd) {
  int32_t tagLength = 0;
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    if (pExpr->functionId == TSDB_FUNC_TAGPRJ || pExpr->functionId == TSDB_FUNC_TAG) {
      pExpr->functionId = TSDB_FUNC_TAG_DUMMY;
      tagLength += pExpr->resBytes;
    } else if (pExpr->functionId == TSDB_FUNC_PRJ && pExpr->colInfo.colId == PRIMARYKEY_TIMESTAMP_COL_INDEX) {
      pExpr->functionId = TSDB_FUNC_TS_DUMMY;
      tagLength += pExpr->resBytes;
    }
  }

  int16_t resType = 0;
  int16_t resBytes = 0;

  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, 0);
  SSchema*        pSchema = tsGetSchema(pMeterMetaInfo->pMeterMeta);

  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    if (pExpr->functionId != TSDB_FUNC_TAG_DUMMY && pExpr->functionId != TSDB_FUNC_TS_DUMMY) {
      SSchema* pColSchema = &pSchema[pExpr->colInfo.colIdx];
      getResultDataInfo(pColSchema->type, pColSchema->bytes, pExpr->functionId, pExpr->param[0].i64Key, &pExpr->resType,
                        &pExpr->resBytes, &pExpr->interResBytes, tagLength, true);
    }
  }
}