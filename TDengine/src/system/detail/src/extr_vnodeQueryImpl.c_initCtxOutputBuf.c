#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* init ) (TYPE_5__*) ;} ;
struct TYPE_12__ {scalar_t__ currentStage; } ;
struct TYPE_11__ {size_t numOfOutputCols; TYPE_2__* pSelectExpr; } ;
struct TYPE_10__ {TYPE_5__* pCtx; TYPE_4__* pQuery; } ;
struct TYPE_8__ {size_t functionId; } ;
struct TYPE_9__ {TYPE_1__ pBase; } ;
typedef  TYPE_3__ SQueryRuntimeEnv ;
typedef  TYPE_4__ SQuery ;

/* Variables and functions */
 TYPE_7__* aAggs ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

void initCtxOutputBuf(SQueryRuntimeEnv *pRuntimeEnv) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  for (int32_t j = 0; j < pQuery->numOfOutputCols; ++j) {
    int32_t functionId = pQuery->pSelectExpr[j].pBase.functionId;
    pRuntimeEnv->pCtx[j].currentStage = 0;
    aAggs[functionId].init(&pRuntimeEnv->pCtx[j]);
  }
}