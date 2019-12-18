#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_7__ {scalar_t__ numOfOutputCols; } ;
struct TYPE_9__ {TYPE_1__ fieldsInfo; } ;
struct TYPE_8__ {scalar_t__ functionId; } ;
typedef  TYPE_2__ SSqlExpr ;
typedef  TYPE_3__ SSqlCmd ;

/* Variables and functions */
 scalar_t__ TSDB_FUNC_TAG ; 
 scalar_t__ TSDB_FUNC_TAGPRJ ; 
 TYPE_2__* tscSqlExprGet (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static void updateTagPrjFunction(SSqlCmd* pCmd) {
  for (int32_t i = 0; i < pCmd->fieldsInfo.numOfOutputCols; ++i) {
    SSqlExpr* pExpr = tscSqlExprGet(pCmd, i);
    if (pExpr->functionId == TSDB_FUNC_TAGPRJ) {
      pExpr->functionId = TSDB_FUNC_TAG;
    }
  }
}