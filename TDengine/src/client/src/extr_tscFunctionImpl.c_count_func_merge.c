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
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;
struct TYPE_5__ {size_t size; scalar_t__ aOutputBuf; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 scalar_t__ GET_INPUT_CHAR (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_VAL (TYPE_1__*,size_t,int) ; 

__attribute__((used)) static void count_func_merge(SQLFunctionCtx *pCtx) {
  int64_t *pData = (int64_t *)GET_INPUT_CHAR(pCtx);
  for (int32_t i = 0; i < pCtx->size; ++i) {
    *((int64_t *)pCtx->aOutputBuf) += pData[i];
  }

  SET_VAL(pCtx, pCtx->size, 1);
}