#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tValuePair ;
typedef  int /*<<< orphan*/  __compar_fn_t ;
struct TYPE_13__ {TYPE_1__* param; } ;
struct TYPE_12__ {scalar_t__ hasResult; scalar_t__ numOfRes; TYPE_2__* interResultBuf; } ;
struct TYPE_11__ {scalar_t__ num; int /*<<< orphan*/ ** res; } ;
struct TYPE_10__ {scalar_t__ i64Key; } ;
typedef  TYPE_2__ STopBotInfo ;
typedef  TYPE_3__ SResultInfo ;
typedef  TYPE_4__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ DATA_SET_FLAG ; 
 TYPE_3__* GET_RES_INFO (TYPE_4__*) ; 
 int /*<<< orphan*/  GET_TRUE_DATA_TYPE () ; 
 int /*<<< orphan*/  POINTER_BYTES ; 
 scalar_t__ PRIMARYKEY_TIMESTAMP_COL_INDEX ; 
 scalar_t__ TSQL_SO_ASC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copyTopBotRes (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resAscComparFn ; 
 int /*<<< orphan*/  resDataAscComparFn ; 
 int /*<<< orphan*/  resDataDescComparFn ; 
 int /*<<< orphan*/  resDescComparFn ; 
 int /*<<< orphan*/  resetResultInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  type ; 

__attribute__((used)) static void top_bottom_func_finalizer(SQLFunctionCtx *pCtx) {
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  // data in temporary list is less than the required number of results, not enough qualified number of results
  STopBotInfo *pRes = pResInfo->interResultBuf;
  if (pRes->num == 0) {  // no result
    assert(pResInfo->hasResult != DATA_SET_FLAG);
    // TODO:
  }

  GET_RES_INFO(pCtx)->numOfRes = pRes->num;
  tValuePair **tvp = pRes->res;

  // user specify the order of output by sort the result according to timestamp
  if (pCtx->param[1].i64Key == PRIMARYKEY_TIMESTAMP_COL_INDEX) {
    __compar_fn_t comparator = (pCtx->param[2].i64Key == TSQL_SO_ASC) ? resAscComparFn : resDescComparFn;
    qsort(tvp, pResInfo->numOfRes, POINTER_BYTES, comparator);
  } else if (pCtx->param[1].i64Key > PRIMARYKEY_TIMESTAMP_COL_INDEX) {
    __compar_fn_t comparator = (pCtx->param[2].i64Key == TSQL_SO_ASC) ? resDataAscComparFn : resDataDescComparFn;
    qsort(tvp, pResInfo->numOfRes, POINTER_BYTES, comparator);
  }

  GET_TRUE_DATA_TYPE();
  copyTopBotRes(pCtx, type);

  resetResultInfo(pResInfo);
}