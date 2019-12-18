#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_18__ {int nFunc; TYPE_1__* aFunc; } ;
struct TYPE_15__ {char* zToken; } ;
struct TYPE_12__ {TYPE_6__* pList; } ;
struct TYPE_17__ {scalar_t__ op; TYPE_5__ u; TYPE_2__ x; } ;
struct TYPE_16__ {int nExpr; TYPE_4__* a; } ;
struct TYPE_14__ {TYPE_3__* pExpr; } ;
struct TYPE_13__ {scalar_t__ op; } ;
struct TYPE_11__ {TYPE_7__* pExpr; } ;
typedef  TYPE_6__ ExprList ;
typedef  TYPE_7__ Expr ;
typedef  TYPE_8__ AggInfo ;

/* Variables and functions */
 scalar_t__ TK_AGG_COLUMN ; 
 scalar_t__ TK_AGG_FUNCTION ; 
 int WHERE_ORDERBY_MAX ; 
 int WHERE_ORDERBY_MIN ; 
 int WHERE_ORDERBY_NORMAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3StrICmp (char const*,char*) ; 

__attribute__((used)) static u8 minMaxQuery(AggInfo *pAggInfo, ExprList **ppMinMax){
  int eRet = WHERE_ORDERBY_NORMAL;          /* Return value */

  *ppMinMax = 0;
  if( pAggInfo->nFunc==1 ){
    Expr *pExpr = pAggInfo->aFunc[0].pExpr; /* Aggregate function */
    ExprList *pEList = pExpr->x.pList;      /* Arguments to agg function */

    assert( pExpr->op==TK_AGG_FUNCTION );
    if( pEList && pEList->nExpr==1 && pEList->a[0].pExpr->op==TK_AGG_COLUMN ){
      const char *zFunc = pExpr->u.zToken;
      if( sqlite3StrICmp(zFunc, "min")==0 ){
        eRet = WHERE_ORDERBY_MIN;
        *ppMinMax = pEList;
      }else if( sqlite3StrICmp(zFunc, "max")==0 ){
        eRet = WHERE_ORDERBY_MAX;
        *ppMinMax = pEList;
      }
    }
  }

  assert( *ppMinMax==0 || (*ppMinMax)->nExpr==1 );
  return eRet;
}