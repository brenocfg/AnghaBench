#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_5__ {int inputBytes; char* aOutputBuf; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 char DATA_SET_FLAG ; 
 int /*<<< orphan*/  SET_VAL (TYPE_1__*,scalar_t__,int) ; 
 scalar_t__ minmax_merge_impl (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max_func_merge(SQLFunctionCtx *pCtx) {
  int32_t numOfElems = minmax_merge_impl(pCtx, pCtx->inputBytes, pCtx->aOutputBuf, 0);

  SET_VAL(pCtx, numOfElems, 1);
  if (numOfElems > 0) {
    char *flag = pCtx->aOutputBuf + pCtx->inputBytes;
    *flag = DATA_SET_FLAG;
  }
}