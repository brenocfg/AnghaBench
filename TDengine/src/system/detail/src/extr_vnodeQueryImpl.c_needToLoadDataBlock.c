#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_19__ {scalar_t__ (* fp ) (TYPE_8__*,char*,char*) ;} ;
struct TYPE_18__ {scalar_t__ colId; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_17__ {size_t numOfFilterCols; size_t numOfOutputCols; TYPE_4__* pSelectExpr; TYPE_5__* pFilterInfo; } ;
struct TYPE_12__ {scalar_t__ colId; scalar_t__ type; } ;
struct TYPE_13__ {size_t colIdx; TYPE_1__ data; } ;
struct TYPE_16__ {size_t numOfFilters; TYPE_8__* pFilters; TYPE_2__ info; } ;
struct TYPE_14__ {size_t functionId; } ;
struct TYPE_15__ {TYPE_3__ pBase; } ;
typedef  TYPE_5__ SSingleColumnFilterInfo ;
typedef  TYPE_6__ SQuery ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;
typedef  TYPE_7__ SField ;

/* Variables and functions */
 scalar_t__ TSDB_DATA_TYPE_FLOAT ; 
 size_t TSDB_FUNC_BOTTOM ; 
 size_t TSDB_FUNC_TOP ; 
 scalar_t__ stub1 (TYPE_8__*,char*,char*) ; 
 scalar_t__ stub2 (TYPE_8__*,char*,char*) ; 
 int top_bot_datablock_filter (int /*<<< orphan*/ *,size_t,char*,char*) ; 
 int /*<<< orphan*/  vnodeSupportPrefilter (scalar_t__) ; 

__attribute__((used)) static bool needToLoadDataBlock(SQuery *pQuery, SField *pField, SQLFunctionCtx *pCtx) {
  if (pField == NULL) {
    return false;  // no need to load data
  }

  for (int32_t k = 0; k < pQuery->numOfFilterCols; ++k) {
    SSingleColumnFilterInfo *pFilterInfo = &pQuery->pFilterInfo[k];
    int32_t                  colIndex = pFilterInfo->info.colIdx;

    // this column not valid in current data block
    if (colIndex < 0 || pField[colIndex].colId != pFilterInfo->info.data.colId) {
      continue;
    }

    // not support pre-filter operation on binary/nchar data type
    if (!vnodeSupportPrefilter(pFilterInfo->info.data.type)) {
      continue;
    }

    if (pFilterInfo->info.data.type == TSDB_DATA_TYPE_FLOAT) {
      float minval = *(double *)(&pField[colIndex].min);
      float maxval = *(double *)(&pField[colIndex].max);

      for (int32_t i = 0; i < pFilterInfo->numOfFilters; ++i) {
        if (pFilterInfo->pFilters[i].fp(&pFilterInfo->pFilters[i], (char *)&minval, (char *)&maxval)) {
          return true;
        }
      }
    } else {
      for (int32_t i = 0; i < pFilterInfo->numOfFilters; ++i) {
        if (pFilterInfo->pFilters[i].fp(&pFilterInfo->pFilters[i], (char *)&pField[colIndex].min,
                                        (char *)&pField[colIndex].max)) {
          return true;
        }
      }
    }
  }

  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    int32_t functId = pQuery->pSelectExpr[i].pBase.functionId;
    if (functId == TSDB_FUNC_TOP || functId == TSDB_FUNC_BOTTOM) {
      return top_bot_datablock_filter(&pCtx[i], functId, (char *)&pField[i].min, (char *)&pField[i].max);
    }
  }

  return true;
}