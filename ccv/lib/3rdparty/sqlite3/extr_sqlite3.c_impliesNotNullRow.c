#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  iCur; } ;
struct TYPE_12__ {int eCode; TYPE_1__ u; } ;
typedef  TYPE_4__ Walker ;
struct TYPE_13__ {int op; TYPE_3__* pRight; TYPE_2__* pLeft; int /*<<< orphan*/  iTable; } ;
struct TYPE_11__ {int const op; int /*<<< orphan*/  pTab; } ;
struct TYPE_10__ {int const op; int /*<<< orphan*/  pTab; } ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_FromJoin ; 
 scalar_t__ ExprHasProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsVirtual (int /*<<< orphan*/ ) ; 
 int TK_AGG_COLUMN ; 
 int TK_AGG_FUNCTION ; 
#define  TK_CASE 142 
#define  TK_COLUMN 141 
#define  TK_EQ 140 
#define  TK_FUNCTION 139 
#define  TK_GE 138 
#define  TK_GT 137 
#define  TK_IN 136 
#define  TK_IS 135 
#define  TK_ISNOT 134 
#define  TK_ISNULL 133 
#define  TK_LE 132 
#define  TK_LT 131 
#define  TK_NE 130 
#define  TK_NOT 129 
#define  TK_OR 128 
 int WRC_Abort ; 
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int impliesNotNullRow(Walker *pWalker, Expr *pExpr){
  /* This routine is only called for WHERE clause expressions and so it
  ** cannot have any TK_AGG_COLUMN entries because those are only found
  ** in HAVING clauses.  We can get a TK_AGG_FUNCTION in a WHERE clause,
  ** but that is an illegal construct and the query will be rejected at
  ** a later stage of processing, so the TK_AGG_FUNCTION case does not
  ** need to be considered here. */
  assert( pExpr->op!=TK_AGG_COLUMN );
  testcase( pExpr->op==TK_AGG_FUNCTION );

  if( ExprHasProperty(pExpr, EP_FromJoin) ) return WRC_Prune;
  switch( pExpr->op ){
    case TK_ISNOT:
    case TK_NOT:
    case TK_ISNULL:
    case TK_IS:
    case TK_OR:
    case TK_CASE:
    case TK_IN:
    case TK_FUNCTION:
      testcase( pExpr->op==TK_ISNOT );
      testcase( pExpr->op==TK_NOT );
      testcase( pExpr->op==TK_ISNULL );
      testcase( pExpr->op==TK_IS );
      testcase( pExpr->op==TK_OR );
      testcase( pExpr->op==TK_CASE );
      testcase( pExpr->op==TK_IN );
      testcase( pExpr->op==TK_FUNCTION );
      return WRC_Prune;
    case TK_COLUMN:
      if( pWalker->u.iCur==pExpr->iTable ){
        pWalker->eCode = 1;
        return WRC_Abort;
      }
      return WRC_Prune;

    /* Virtual tables are allowed to use constraints like x=NULL.  So
    ** a term of the form x=y does not prove that y is not null if x
    ** is the column of a virtual table */
    case TK_EQ:
    case TK_NE:
    case TK_LT:
    case TK_LE:
    case TK_GT:
    case TK_GE:
      testcase( pExpr->op==TK_EQ );
      testcase( pExpr->op==TK_NE );
      testcase( pExpr->op==TK_LT );
      testcase( pExpr->op==TK_LE );
      testcase( pExpr->op==TK_GT );
      testcase( pExpr->op==TK_GE );
      if( (pExpr->pLeft->op==TK_COLUMN && IsVirtual(pExpr->pLeft->pTab))
       || (pExpr->pRight->op==TK_COLUMN && IsVirtual(pExpr->pRight->pTab))
      ){
       return WRC_Prune;
      }
    default:
      return WRC_Continue;
  }
}