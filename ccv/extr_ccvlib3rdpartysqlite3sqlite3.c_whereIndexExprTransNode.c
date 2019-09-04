#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* pIdxTrans; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_11__ {scalar_t__ pTab; int /*<<< orphan*/  iColumn; int /*<<< orphan*/  iTable; int /*<<< orphan*/  op; } ;
struct TYPE_10__ {int /*<<< orphan*/  iIdxCol; int /*<<< orphan*/  iIdxCur; int /*<<< orphan*/  iTabCur; int /*<<< orphan*/  pIdxExpr; } ;
typedef  TYPE_3__ IdxExprTrans ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  TK_COLUMN ; 
 int WRC_Continue ; 
 int WRC_Prune ; 
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int whereIndexExprTransNode(Walker *p, Expr *pExpr){
  IdxExprTrans *pX = p->u.pIdxTrans;
  if( sqlite3ExprCompare(0, pExpr, pX->pIdxExpr, pX->iTabCur)==0 ){
    pExpr->op = TK_COLUMN;
    pExpr->iTable = pX->iIdxCur;
    pExpr->iColumn = pX->iIdxCol;
    pExpr->pTab = 0;
    return WRC_Prune;
  }else{
    return WRC_Continue;
  }
}