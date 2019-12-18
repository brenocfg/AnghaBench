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
typedef  size_t int32_t ;
struct TYPE_6__ {int order; } ;
struct TYPE_9__ {size_t numOfOutputCols; TYPE_1__ order; } ;
struct TYPE_8__ {TYPE_2__* pCtx; TYPE_4__* pQuery; } ;
struct TYPE_7__ {int order; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;

/* Variables and functions */

void enableFunctForMasterScan(SQueryRuntimeEnv *pRuntimeEnv, int32_t order) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    pRuntimeEnv->pCtx[i].order = (pRuntimeEnv->pCtx[i].order) ^ 1;
  }

  pQuery->order.order = (pQuery->order.order ^ 1);
}