#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ numOfOrderedCols; } ;
struct TYPE_11__ {scalar_t__ tsOrder; TYPE_1__ orderIdx; } ;
typedef  TYPE_2__ tOrderDescriptor ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ tFilePage ;
typedef  int int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_14__ {scalar_t__ functionId; } ;
struct TYPE_13__ {int /*<<< orphan*/  prevRowOfInput; TYPE_2__* pDesc; } ;
typedef  int /*<<< orphan*/  SSqlCmd ;
typedef  TYPE_4__ SLocalReducer ;

/* Variables and functions */
 scalar_t__ TSDB_FUNC_ARITHM ; 
 scalar_t__ TSDB_FUNC_PRJ ; 
 scalar_t__ TSQL_SO_ASC ; 
 int compare_a (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int compare_d (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* tscSqlExprGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool needToMerge(SSqlCmd *pCmd, SLocalReducer *pLocalReducer, tFilePage *tmpBuffer) {
  int32_t ret = 0;  // merge all result by default
  int16_t functionId = tscSqlExprGet(pCmd, 0)->functionId;

  if (functionId == TSDB_FUNC_PRJ || functionId == TSDB_FUNC_ARITHM) {  // column projection query
    ret = 1;                                                            // disable merge procedure
  } else {
    tOrderDescriptor *pDesc = pLocalReducer->pDesc;
    if (pDesc->orderIdx.numOfOrderedCols > 0) {
      if (pDesc->tsOrder == TSQL_SO_ASC) {  // asc
        // todo refactor comparator
        ret = compare_a(pLocalReducer->pDesc, 1, 0, pLocalReducer->prevRowOfInput, 1, 0, tmpBuffer->data);
      } else {  // desc
        ret = compare_d(pLocalReducer->pDesc, 1, 0, pLocalReducer->prevRowOfInput, 1, 0, tmpBuffer->data);
      }
    }
  }

  /* if ret == 0, means the result belongs to the same group */
  return (ret == 0);
}