#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  int /*<<< orphan*/  SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 TYPE_1__* GET_RES_INFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_VAL (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ sum_merge_impl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sum_func_second_merge(SQLFunctionCtx *pCtx) {
  int32_t notNullElems = sum_merge_impl(pCtx);

  SET_VAL(pCtx, notNullElems, 1);
  SResultInfo *pResInfo = GET_RES_INFO(pCtx);

  if (notNullElems > 0) {
    pResInfo->hasResult = DATA_SET_FLAG;
  }
}