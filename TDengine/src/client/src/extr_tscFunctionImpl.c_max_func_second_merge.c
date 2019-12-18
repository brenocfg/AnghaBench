#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  aOutputBuf; int /*<<< orphan*/  outputBytes; } ;
struct TYPE_8__ {int /*<<< orphan*/  hasResult; } ;
typedef  TYPE_1__ SResultInfo ;
typedef  TYPE_2__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_SET_FLAG ; 
 TYPE_1__* GET_RES_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ minmax_merge_impl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max_func_second_merge(SQLFunctionCtx *pCtx) {
  int32_t numOfElem = minmax_merge_impl(pCtx, pCtx->outputBytes, pCtx->aOutputBuf, 0);

  SET_VAL(pCtx, numOfElem, 1);

  SResultInfo *pResInfo = GET_RES_INFO(pCtx);
  if (numOfElem > 0) {
    pResInfo->hasResult = DATA_SET_FLAG;
  }
}