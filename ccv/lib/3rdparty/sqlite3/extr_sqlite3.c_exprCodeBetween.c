#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_2__* pList; } ;
struct TYPE_18__ {int /*<<< orphan*/  flags; TYPE_3__ x; struct TYPE_18__* pRight; struct TYPE_18__* pLeft; int /*<<< orphan*/  op; } ;
struct TYPE_16__ {TYPE_1__* a; } ;
struct TYPE_15__ {TYPE_4__* pExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TK_AND ; 
 int /*<<< orphan*/  TK_GE ; 
 int /*<<< orphan*/  TK_LE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exprCodeVector (int /*<<< orphan*/ *,TYPE_4__*,int*) ; 
 int /*<<< orphan*/  exprToRegister (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeTarget (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 void sqlite3ExprIfFalse (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 void sqlite3ExprIfTrue (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void exprCodeBetween(
  Parse *pParse,    /* Parsing and code generating context */
  Expr *pExpr,      /* The BETWEEN expression */
  int dest,         /* Jump destination or storage location */
  void (*xJump)(Parse*,Expr*,int,int), /* Action to take */
  int jumpIfNull    /* Take the jump if the BETWEEN is NULL */
){
 Expr exprAnd;     /* The AND operator in  x>=y AND x<=z  */
  Expr compLeft;    /* The  x>=y  term */
  Expr compRight;   /* The  x<=z  term */
  Expr exprX;       /* The  x  subexpression */
  int regFree1 = 0; /* Temporary use register */


  memset(&compLeft, 0, sizeof(Expr));
  memset(&compRight, 0, sizeof(Expr));
  memset(&exprAnd, 0, sizeof(Expr));

  assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
  exprX = *pExpr->pLeft;
  exprAnd.op = TK_AND;
  exprAnd.pLeft = &compLeft;
  exprAnd.pRight = &compRight;
  compLeft.op = TK_GE;
  compLeft.pLeft = &exprX;
  compLeft.pRight = pExpr->x.pList->a[0].pExpr;
  compRight.op = TK_LE;
  compRight.pLeft = &exprX;
  compRight.pRight = pExpr->x.pList->a[1].pExpr;
  exprToRegister(&exprX, exprCodeVector(pParse, &exprX, &regFree1));
  if( xJump ){
    xJump(pParse, &exprAnd, dest, jumpIfNull);
  }else{
    /* Mark the expression is being from the ON or USING clause of a join
    ** so that the sqlite3ExprCodeTarget() routine will not attempt to move
    ** it into the Parse.pConstExpr list.  We should use a new bit for this,
    ** for clarity, but we are out of bits in the Expr.flags field so we
    ** have to reuse the EP_FromJoin bit.  Bummer. */
    exprX.flags |= EP_FromJoin;
    sqlite3ExprCodeTarget(pParse, &exprAnd, dest);
  }
  sqlite3ReleaseTempReg(pParse, regFree1);

  /* Ensure adequate test coverage */
  testcase( xJump==sqlite3ExprIfTrue  && jumpIfNull==0 && regFree1==0 );
  testcase( xJump==sqlite3ExprIfTrue  && jumpIfNull==0 && regFree1!=0 );
  testcase( xJump==sqlite3ExprIfTrue  && jumpIfNull!=0 && regFree1==0 );
  testcase( xJump==sqlite3ExprIfTrue  && jumpIfNull!=0 && regFree1!=0 );
  testcase( xJump==sqlite3ExprIfFalse && jumpIfNull==0 && regFree1==0 );
  testcase( xJump==sqlite3ExprIfFalse && jumpIfNull==0 && regFree1!=0 );
  testcase( xJump==sqlite3ExprIfFalse && jumpIfNull!=0 && regFree1==0 );
  testcase( xJump==sqlite3ExprIfFalse && jumpIfNull!=0 && regFree1!=0 );
  testcase( xJump==0 );
}