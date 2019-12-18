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
struct TYPE_7__ {int i; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_9__ {int op; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 scalar_t__ ExprHasAnyProperty (TYPE_3__*,int /*<<< orphan*/ ) ; 
#define  TK_AGG_COLUMN 132 
#define  TK_AGG_FUNCTION 131 
#define  TK_COLUMN 130 
 int const TK_EXISTS ; 
#define  TK_FUNCTION 129 
#define  TK_ID 128 
 int const TK_SELECT ; 
 int WRC_Abort ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int exprNodeIsConstant(Walker *pWalker, Expr *pExpr){

  /* If pWalker->u.i is 3 then any term of the expression that comes from
  ** the ON or USING clauses of a join disqualifies the expression
  ** from being considered constant. */
  if( pWalker->u.i==3 && ExprHasAnyProperty(pExpr, EP_FromJoin) ){
    pWalker->u.i = 0;
    return WRC_Abort;
  }

  switch( pExpr->op ){
    /* Consider functions to be constant if all their arguments are constant
    ** and pWalker->u.i==2 */
    case TK_FUNCTION:
      if( pWalker->u.i==2 ) return 0;
      /* Fall through */
    case TK_ID:
    case TK_COLUMN:
    case TK_AGG_FUNCTION:
    case TK_AGG_COLUMN:
      testcase( pExpr->op==TK_ID );
      testcase( pExpr->op==TK_COLUMN );
      testcase( pExpr->op==TK_AGG_FUNCTION );
      testcase( pExpr->op==TK_AGG_COLUMN );
      pWalker->u.i = 0;
      return WRC_Abort;
    default:
      testcase( pExpr->op==TK_SELECT ); /* selectNodeIsConstant will disallow */
      testcase( pExpr->op==TK_EXISTS ); /* selectNodeIsConstant will disallow */
      return WRC_Continue;
  }
}