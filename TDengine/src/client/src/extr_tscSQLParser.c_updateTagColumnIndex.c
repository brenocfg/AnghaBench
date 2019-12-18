#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_19__ {size_t numOfTags; size_t* tagColumnIndex; } ;
struct TYPE_15__ {size_t numOfExprs; } ;
struct TYPE_14__ {size_t numOfGroupCols; TYPE_1__* columnInfo; } ;
struct TYPE_18__ {TYPE_3__ exprsInfo; TYPE_2__ groupbyExpr; } ;
struct TYPE_16__ {size_t colIdx; int /*<<< orphan*/  flag; } ;
struct TYPE_17__ {TYPE_4__ colInfo; } ;
struct TYPE_13__ {size_t colIdx; } ;
typedef  TYPE_5__ SSqlExpr ;
typedef  TYPE_6__ SSqlCmd ;
typedef  TYPE_7__ SMeterMetaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TSDB_COL_IS_TAG (int /*<<< orphan*/ ) ; 
 TYPE_7__* tscGetMeterMetaInfo (TYPE_6__*,size_t) ; 
 TYPE_5__* tscSqlExprGet (TYPE_6__*,size_t) ; 

void updateTagColumnIndex(SSqlCmd* pCmd, int32_t tableIndex) {
  SMeterMetaInfo* pMeterMetaInfo = tscGetMeterMetaInfo(pCmd, tableIndex);

  // update tags column index for group by tags
  for (int32_t i = 0; i < pCmd->groupbyExpr.numOfGroupCols; ++i) {
    int32_t index = pCmd->groupbyExpr.columnInfo[i].colIdx;

    for (int32_t j = 0; j < pMeterMetaInfo->numOfTags; ++j) {
      int32_t tagColIndex = pMeterMetaInfo->tagColumnIndex[j];
      if (tagColIndex == index) {
        pCmd->groupbyExpr.columnInfo[i].colIdx = j;
        break;
      }
    }
  }

  // update tags column index for expression
  for (int32_t i = 0; i < pCmd->exprsInfo.numOfExprs; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    if (!TSDB_COL_IS_TAG(pExpr->colInfo.flag)) {  // not tags, continue
      continue;
    }

    for (int32_t j = 0; j < pMeterMetaInfo->numOfTags; ++j) {
      if (pExpr->colInfo.colIdx == pMeterMetaInfo->tagColumnIndex[j]) {
        pExpr->colInfo.colIdx = j;
        break;
      }
    }
  }
}