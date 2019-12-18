#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tOrderDescriptor ;
typedef  int /*<<< orphan*/  tColModel ;
typedef  size_t int32_t ;
struct TYPE_8__ {int /*<<< orphan*/  order; } ;
struct TYPE_7__ {scalar_t__ numOfGroupCols; } ;
struct TYPE_6__ {size_t numOfOutputCols; } ;
struct TYPE_9__ {scalar_t__ nAggTimeInterval; TYPE_3__ order; TYPE_2__ groupbyExpr; TYPE_1__ fieldsInfo; } ;
typedef  TYPE_4__ SSqlCmd ;

/* Variables and functions */
 size_t PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 size_t TSDB_CODE_CLI_OUT_OF_MEMORY ; 
 size_t TSDB_CODE_SUCCESS ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/ * tOrderDesCreate (size_t*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree (size_t*) ; 

__attribute__((used)) static int32_t createOrderDescriptor(tOrderDescriptor **pOrderDesc, SSqlCmd *pCmd, tColModel *pModel) {
  int32_t numOfGroupByCols = 0;
  if (pCmd->groupbyExpr.numOfGroupCols > 0) {
    numOfGroupByCols = pCmd->groupbyExpr.numOfGroupCols;
  }

  // primary timestamp column is involved in final result
  if (pCmd->nAggTimeInterval != 0) {
    numOfGroupByCols++;
  }

  int32_t *orderIdx = (int32_t *)calloc(numOfGroupByCols, sizeof(int32_t));
  if (orderIdx == NULL) {
    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  }

  if (numOfGroupByCols > 0) {
    int32_t startCols = pCmd->fieldsInfo.numOfOutputCols - pCmd->groupbyExpr.numOfGroupCols;

    // tags value locate at the last columns
    for (int32_t i = 0; i < pCmd->groupbyExpr.numOfGroupCols; ++i) {
      orderIdx[i] = startCols++;
    }

    if (pCmd->nAggTimeInterval != 0) {
      // the first column is the timestamp, handles queries like "interval(10m) group by tags"
      orderIdx[numOfGroupByCols - 1] = PRIMARYKEY_TIMESTAMP_COL_INDEX;
    }
  }

  *pOrderDesc = tOrderDesCreate(orderIdx, numOfGroupByCols, pModel, pCmd->order.order);
  tfree(orderIdx);

  if (*pOrderDesc == NULL) {
    return TSDB_CODE_CLI_OUT_OF_MEMORY;
  } else {
    return TSDB_CODE_SUCCESS;
  }
}