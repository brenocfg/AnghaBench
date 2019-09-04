#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pIdxCover; } ;
struct TYPE_9__ {int eCode; TYPE_2__ u; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_10__ {scalar_t__ op; scalar_t__ iTable; int /*<<< orphan*/  iColumn; } ;
struct TYPE_7__ {scalar_t__ iCur; int /*<<< orphan*/  pIdx; } ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 scalar_t__ TK_COLUMN ; 
 int WRC_Abort ; 
 int WRC_Continue ; 
 scalar_t__ sqlite3ColumnOfIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exprIdxCover(Walker *pWalker, Expr *pExpr){
  if( pExpr->op==TK_COLUMN
   && pExpr->iTable==pWalker->u.pIdxCover->iCur
   && sqlite3ColumnOfIndex(pWalker->u.pIdxCover->pIdx, pExpr->iColumn)<0
  ){
    pWalker->eCode = 1;
    return WRC_Abort;
  }
  return WRC_Continue;
}