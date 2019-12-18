#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {int size; scalar_t__ startOffset; scalar_t__ outputBytes; scalar_t__ aOutputBuf; } ;
struct TYPE_7__ {size_t numOfOutputCols; TYPE_1__** sdata; } ;
struct TYPE_6__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_2__ SQuery ;
typedef  TYPE_3__ SQLFunctionCtx ;

/* Variables and functions */

void resetMergeResultBuf(SQuery *pQuery, SQLFunctionCtx *pCtx) {
  for (int32_t k = 0; k < pQuery->numOfOutputCols; ++k) {
    pCtx[k].aOutputBuf = pQuery->sdata[k]->data - pCtx[k].outputBytes;
    pCtx[k].size = 1;
    pCtx[k].startOffset = 0;
    pQuery->sdata[k]->len = 0;
  }
}