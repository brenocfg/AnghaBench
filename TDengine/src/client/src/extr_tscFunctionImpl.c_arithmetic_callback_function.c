#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_8__ {char** data; int offset; int* elemSize; TYPE_3__* pExpr; } ;
struct TYPE_6__ {size_t numOfCols; TYPE_1__* pReqColumns; } ;
struct TYPE_7__ {TYPE_2__ pBinExprInfo; } ;
struct TYPE_5__ {size_t colId; size_t colIdxInBuf; } ;
typedef  TYPE_3__ SSqlFunctionExpr ;
typedef  TYPE_4__ SArithmeticSupport ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

char *arithmetic_callback_function(void *param, char *name, int32_t colId) {
  SArithmeticSupport *pSupport = (SArithmeticSupport *)param;

  SSqlFunctionExpr *pExpr = pSupport->pExpr;
  int32_t           colIndexInBuf = -1;

  for (int32_t i = 0; i < pExpr->pBinExprInfo.numOfCols; ++i) {
    if (colId == pExpr->pBinExprInfo.pReqColumns[i].colId) {
      colIndexInBuf = pExpr->pBinExprInfo.pReqColumns[i].colIdxInBuf;
      break;
    }
  }

  assert(colIndexInBuf >= 0 && colId >= 0);
  return pSupport->data[colIndexInBuf] + pSupport->offset * pSupport->elemSize[colIndexInBuf];
}