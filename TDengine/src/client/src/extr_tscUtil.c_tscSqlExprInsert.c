#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
typedef  size_t int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_24__ {scalar_t__ columnIndex; int /*<<< orphan*/  tableIndex; } ;
struct TYPE_23__ {TYPE_14__* pMeterMeta; } ;
struct TYPE_22__ {scalar_t__ colId; } ;
struct TYPE_19__ {scalar_t__ numOfExprs; TYPE_3__* pExprs; } ;
struct TYPE_21__ {TYPE_2__ exprsInfo; } ;
struct TYPE_18__ {scalar_t__ colIdx; void* flag; scalar_t__ colId; } ;
struct TYPE_20__ {int /*<<< orphan*/  uid; scalar_t__ interResBytes; scalar_t__ resBytes; scalar_t__ resType; TYPE_1__ colInfo; scalar_t__ functionId; } ;
struct TYPE_17__ {scalar_t__ numOfColumns; int /*<<< orphan*/  uid; } ;
typedef  TYPE_2__ SSqlExprInfo ;
typedef  TYPE_3__ SSqlExpr ;
typedef  TYPE_4__ SSqlCmd ;
typedef  TYPE_5__ SSchema ;
typedef  TYPE_6__ SMeterMetaInfo ;
typedef  TYPE_7__ SColumnIndex ;

/* Variables and functions */
 void* TSDB_COL_NORMAL ; 
 void* TSDB_COL_TAG ; 
 scalar_t__ TSDB_TBNAME_COLUMN_INDEX ; 
 int /*<<< orphan*/  _exprCheckSpace (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  _exprEvic (TYPE_2__*,size_t) ; 
 TYPE_5__* tsGetColumnSchema (TYPE_14__*,scalar_t__) ; 
 TYPE_6__* tscGetMeterMetaInfo (TYPE_4__*,int /*<<< orphan*/ ) ; 

SSqlExpr* tscSqlExprInsert(SSqlCmd* pCmd, int32_t index, int16_t functionId, SColumnIndex* pColIndex, int16_t type,
                           int16_t size, int16_t interSize) {
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, pColIndex->tableIndex);

  SSqlExprInfo* pExprInfo = &pCmd->exprsInfo;

  _exprCheckSpace(pExprInfo, pExprInfo->numOfExprs + 1);
  _exprEvic(pExprInfo, index);

  SSqlExpr* pExpr = &pExprInfo->pExprs[index];

  pExpr->functionId = functionId;
  int16_t numOfCols = pMeterMetaInfo->pMeterMeta->numOfColumns;

  // set the correct column index
  if (pColIndex->columnIndex == TSDB_TBNAME_COLUMN_INDEX) {
    pExpr->colInfo.colId = TSDB_TBNAME_COLUMN_INDEX;
  } else {
    SSchema* pSchema = tsGetColumnSchema(pMeterMetaInfo->pMeterMeta, pColIndex->columnIndex);
    pExpr->colInfo.colId = pSchema->colId;
  }

  // tag columns require the column index revised.
  if (pColIndex->columnIndex >= numOfCols) {
    pColIndex->columnIndex -= numOfCols;
    pExpr->colInfo.flag = TSDB_COL_TAG;
  } else {
    if (pColIndex->columnIndex != TSDB_TBNAME_COLUMN_INDEX) {
      pExpr->colInfo.flag = TSDB_COL_NORMAL;
    } else {
      pExpr->colInfo.flag = TSDB_COL_TAG;
    }
  }

  pExpr->colInfo.colIdx = pColIndex->columnIndex;
  pExpr->resType = type;
  pExpr->resBytes = size;
  pExpr->interResBytes = interSize;
  pExpr->uid = pMeterMetaInfo->pMeterMeta->uid;

  pExprInfo->numOfExprs++;
  return pExpr;
}