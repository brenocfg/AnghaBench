#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {scalar_t__ scanFlag; int /*<<< orphan*/  nStartQueryTimestamp; scalar_t__ aOutputBuf; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ SQLFunctionCtx ;

/* Variables and functions */
 int /*<<< orphan*/  SET_VAL (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUPPLEMENTARY_SCAN ; 

__attribute__((used)) static void date_col_output_function(SQLFunctionCtx *pCtx) {
  if (pCtx->scanFlag == SUPPLEMENTARY_SCAN) {
    return;
  }

  SET_VAL(pCtx, pCtx->size, 1);
  *(int64_t *)(pCtx->aOutputBuf) = pCtx->nStartQueryTimestamp;
}