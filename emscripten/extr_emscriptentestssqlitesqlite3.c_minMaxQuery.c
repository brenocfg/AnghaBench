#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_9__ {TYPE_5__* pList; } ;
struct TYPE_14__ {scalar_t__ op; TYPE_3__ u; TYPE_1__ x; } ;
struct TYPE_13__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_12__ {TYPE_5__* pEList; } ;
struct TYPE_10__ {TYPE_6__* pExpr; } ;
typedef  TYPE_4__ Select ;
typedef  TYPE_5__ ExprList ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_IntValue ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ NEVER (int /*<<< orphan*/ ) ; 
 scalar_t__ TK_AGG_COLUMN ; 
 scalar_t__ TK_AGG_FUNCTION ; 
 int /*<<< orphan*/  WHERE_ORDERBY_MAX ; 
 int /*<<< orphan*/  WHERE_ORDERBY_MIN ; 
 int /*<<< orphan*/  WHERE_ORDERBY_NORMAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u8 minMaxQuery(Select *p){
  Expr *pExpr;
  ExprList *pEList = p->pEList;

  if( pEList->nExpr!=1 ) return WHERE_ORDERBY_NORMAL;
  pExpr = pEList->a[0].pExpr;
  if( pExpr->op!=TK_AGG_FUNCTION ) return 0;
  if( NEVER(ExprHasProperty(pExpr, EP_xIsSelect)) ) return 0;
  pEList = pExpr->x.pList;
  if( pEList==0 || pEList->nExpr!=1 ) return 0;
  if( pEList->a[0].pExpr->op!=TK_AGG_COLUMN ) return WHERE_ORDERBY_NORMAL;
  assert( !ExprHasProperty(pExpr, EP_IntValue) );
  if( sqlite3StrICmp(pExpr->u.zToken,"min")==0 ){
    return WHERE_ORDERBY_MIN;
  }else if( sqlite3StrICmp(pExpr->u.zToken,"max")==0 ){
    return WHERE_ORDERBY_MAX;
  }
  return WHERE_ORDERBY_NORMAL;
}