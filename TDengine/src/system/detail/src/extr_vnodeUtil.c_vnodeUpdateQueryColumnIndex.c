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
typedef  size_t int32_t ;
typedef  int int16_t ;
struct TYPE_18__ {scalar_t__ flag; scalar_t__ colId; int colIdx; } ;
struct TYPE_17__ {size_t numOfColumns; TYPE_1__* schema; } ;
struct TYPE_16__ {size_t numOfCols; size_t numOfOutputCols; TYPE_4__* colList; TYPE_2__* pSelectExpr; } ;
struct TYPE_15__ {scalar_t__ functionId; TYPE_8__ colInfo; } ;
struct TYPE_13__ {scalar_t__ colId; } ;
struct TYPE_14__ {int colIdx; TYPE_3__ data; } ;
struct TYPE_12__ {TYPE_5__ pBase; } ;
struct TYPE_11__ {scalar_t__ colId; } ;
typedef  TYPE_5__ SSqlFuncExprMsg ;
typedef  TYPE_6__ SQuery ;
typedef  TYPE_7__ SMeterObj ;
typedef  TYPE_8__ SColIndexEx ;

/* Variables and functions */
 scalar_t__ TSDB_COL_TAG ; 
 scalar_t__ TSDB_FUNC_ARITHM ; 

void vnodeUpdateQueryColumnIndex(SQuery* pQuery, SMeterObj* pMeterObj) {
  if (pQuery == NULL || pMeterObj == NULL) {
    return;
  }

  int32_t i = 0, j = 0;
  while (i < pQuery->numOfCols && j < pMeterObj->numOfColumns) {
    if (pQuery->colList[i].data.colId == pMeterObj->schema[j].colId) {
      pQuery->colList[i++].colIdx = (int16_t)j++;
    } else if (pQuery->colList[i].data.colId < pMeterObj->schema[j].colId) {
      pQuery->colList[i++].colIdx = -1;
    } else if (pQuery->colList[i].data.colId > pMeterObj->schema[j].colId) {
      j++;
    }
  }

  while (i < pQuery->numOfCols) {
    pQuery->colList[i++].colIdx = -1;  // not such column in current meter
  }

  // sql expression has not been created yet
  if (pQuery->pSelectExpr == NULL) {
    return;
  }

  for(int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    SSqlFuncExprMsg* pSqlExprMsg = &pQuery->pSelectExpr[i].pBase;
    if (pSqlExprMsg->functionId == TSDB_FUNC_ARITHM || pSqlExprMsg->colInfo.flag == TSDB_COL_TAG) {
      continue;
    }

    SColIndexEx* pColIndexEx = &pSqlExprMsg->colInfo;
    for(int32_t j = 0; j < pQuery->numOfCols; ++j) {
      if (pColIndexEx->colId == pQuery->colList[j].data.colId) {
        pColIndexEx->colIdx = pQuery->colList[j].colIdx;
        break;
      }
    }
  }
}