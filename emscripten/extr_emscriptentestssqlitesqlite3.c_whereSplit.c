#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_7__ {scalar_t__ op; } ;
typedef  TYPE_1__ WhereClause ;
struct TYPE_8__ {int op; struct TYPE_8__* pRight; struct TYPE_8__* pLeft; } ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  whereClauseInsert (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void whereSplit(WhereClause *pWC, Expr *pExpr, int op){
  pWC->op = (u8)op;
  if( pExpr==0 ) return;
  if( pExpr->op!=op ){
    whereClauseInsert(pWC, pExpr, 0);
  }else{
    whereSplit(pWC, pExpr->pLeft, op);
    whereSplit(pWC, pExpr->pRight, op);
  }
}