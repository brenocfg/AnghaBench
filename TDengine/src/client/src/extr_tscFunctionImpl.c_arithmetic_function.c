#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int numOfRes; } ;
struct TYPE_14__ {TYPE_2__* pExpr; } ;
struct TYPE_13__ {int size; int aOutputBuf; int outputBytes; int /*<<< orphan*/  order; TYPE_3__* param; } ;
struct TYPE_12__ {scalar_t__ pz; } ;
struct TYPE_10__ {int /*<<< orphan*/  pBinExpr; } ;
struct TYPE_11__ {TYPE_1__ pBinExprInfo; } ;
typedef  TYPE_4__ SQLFunctionCtx ;
typedef  TYPE_5__ SArithmeticSupport ;

/* Variables and functions */
 int GET_FORWARD_DIRECTION_FACTOR (int /*<<< orphan*/ ) ; 
 TYPE_8__* GET_RES_INFO (TYPE_4__*) ; 
 int /*<<< orphan*/  arithmetic_callback_function ; 
 int /*<<< orphan*/  tSQLBinaryExprCalcTraverse (int /*<<< orphan*/ ,int,int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arithmetic_function(SQLFunctionCtx *pCtx) {
  GET_RES_INFO(pCtx)->numOfRes += pCtx->size;
  SArithmeticSupport *sas = (SArithmeticSupport *)pCtx->param[0].pz;

  tSQLBinaryExprCalcTraverse(sas->pExpr->pBinExprInfo.pBinExpr, pCtx->size, pCtx->aOutputBuf, sas, pCtx->order,
                             arithmetic_callback_function);

  pCtx->aOutputBuf += pCtx->outputBytes * pCtx->size * GET_FORWARD_DIRECTION_FACTOR(pCtx->order);
}