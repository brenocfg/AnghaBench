#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
typedef  size_t int32_t ;
struct TYPE_13__ {size_t numOfOutputCols; TYPE_2__* pSelectExpr; } ;
struct TYPE_12__ {TYPE_4__* pCtx; TYPE_6__* pQuery; } ;
struct TYPE_11__ {TYPE_3__* param; } ;
struct TYPE_10__ {void* nType; void* dKey; } ;
struct TYPE_8__ {size_t functionId; } ;
struct TYPE_9__ {TYPE_1__ pBase; } ;
typedef  TYPE_5__ SQueryRuntimeEnv ;
typedef  TYPE_6__ SQuery ;

/* Variables and functions */
 void* TSDB_DATA_TYPE_DOUBLE ; 
 size_t TSDB_FUNC_SPREAD ; 

__attribute__((used)) static void setTimestampRange(SQueryRuntimeEnv *pRuntimeEnv, int64_t stime, int64_t etime) {
  SQuery *pQuery = pRuntimeEnv->pQuery;

  for (int32_t i = 0; i < pQuery->numOfOutputCols; ++i) {
    int32_t functionId = pQuery->pSelectExpr[i].pBase.functionId;

    if (functionId == TSDB_FUNC_SPREAD) {
      pRuntimeEnv->pCtx[i].param[1].dKey = stime;
      pRuntimeEnv->pCtx[i].param[2].dKey = etime;

      pRuntimeEnv->pCtx[i].param[1].nType = TSDB_DATA_TYPE_DOUBLE;
      pRuntimeEnv->pCtx[i].param[2].nType = TSDB_DATA_TYPE_DOUBLE;
    }
  }
}