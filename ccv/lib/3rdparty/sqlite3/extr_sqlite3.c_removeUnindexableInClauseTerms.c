#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_34__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_6__ sqlite3 ;
struct TYPE_35__ {int nLTerm; TYPE_1__** aLTerm; } ;
typedef  TYPE_7__ WhereLoop ;
struct TYPE_37__ {TYPE_6__* db; } ;
struct TYPE_36__ {TYPE_10__* pOrderBy; TYPE_10__* pEList; } ;
struct TYPE_31__ {scalar_t__ iOrderByCol; } ;
struct TYPE_32__ {TYPE_3__ x; } ;
struct TYPE_33__ {scalar_t__ pExpr; TYPE_4__ u; } ;
struct TYPE_30__ {TYPE_8__* pSelect; TYPE_10__* pList; } ;
struct TYPE_29__ {int iField; TYPE_11__* pExpr; } ;
struct TYPE_28__ {TYPE_2__ x; struct TYPE_28__* pLeft; } ;
struct TYPE_27__ {int nExpr; TYPE_5__* a; } ;
typedef  TYPE_8__ Select ;
typedef  TYPE_9__ Parse ;
typedef  TYPE_10__ ExprList ;
typedef  TYPE_11__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_6__*,TYPE_11__*) ; 
 TYPE_11__* sqlite3ExprDup (TYPE_6__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* sqlite3ExprListAppend (TYPE_9__*,TYPE_10__*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_6__*,TYPE_10__*) ; 
 int /*<<< orphan*/  sqlite3TreeViewExpr (int /*<<< orphan*/ ,TYPE_11__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Expr *removeUnindexableInClauseTerms(
  Parse *pParse,        /* The parsing context */
  int iEq,              /* Look at loop terms starting here */
  WhereLoop *pLoop,     /* The current loop */
  Expr *pX              /* The IN expression to be reduced */
){
  sqlite3 *db = pParse->db;
  Expr *pNew = sqlite3ExprDup(db, pX, 0);
  if( db->mallocFailed==0 ){
    ExprList *pOrigRhs = pNew->x.pSelect->pEList;  /* Original unmodified RHS */
    ExprList *pOrigLhs = pNew->pLeft->x.pList;     /* Original unmodified LHS */
    ExprList *pRhs = 0;         /* New RHS after modifications */
    ExprList *pLhs = 0;         /* New LHS after mods */
    int i;                      /* Loop counter */
    Select *pSelect;            /* Pointer to the SELECT on the RHS */

    for(i=iEq; i<pLoop->nLTerm; i++){
      if( pLoop->aLTerm[i]->pExpr==pX ){
        int iField = pLoop->aLTerm[i]->iField - 1;
        assert( pOrigRhs->a[iField].pExpr!=0 );
        pRhs = sqlite3ExprListAppend(pParse, pRhs, pOrigRhs->a[iField].pExpr);
        pOrigRhs->a[iField].pExpr = 0;
        assert( pOrigLhs->a[iField].pExpr!=0 );
        pLhs = sqlite3ExprListAppend(pParse, pLhs, pOrigLhs->a[iField].pExpr);
        pOrigLhs->a[iField].pExpr = 0;
      }
    }
    sqlite3ExprListDelete(db, pOrigRhs);
    sqlite3ExprListDelete(db, pOrigLhs);
    pNew->pLeft->x.pList = pLhs;
    pNew->x.pSelect->pEList = pRhs;
    if( pLhs && pLhs->nExpr==1 ){
      /* Take care here not to generate a TK_VECTOR containing only a
      ** single value. Since the parser never creates such a vector, some
      ** of the subroutines do not handle this case.  */
      Expr *p = pLhs->a[0].pExpr;
      pLhs->a[0].pExpr = 0;
      sqlite3ExprDelete(db, pNew->pLeft);
      pNew->pLeft = p;
    }
    pSelect = pNew->x.pSelect;
    if( pSelect->pOrderBy ){
      /* If the SELECT statement has an ORDER BY clause, zero the 
      ** iOrderByCol variables. These are set to non-zero when an 
      ** ORDER BY term exactly matches one of the terms of the 
      ** result-set. Since the result-set of the SELECT statement may
      ** have been modified or reordered, these variables are no longer 
      ** set correctly.  Since setting them is just an optimization, 
      ** it's easiest just to zero them here.  */
      ExprList *pOrderBy = pSelect->pOrderBy;
      for(i=0; i<pOrderBy->nExpr; i++){
        pOrderBy->a[i].u.x.iOrderByCol = 0;
      }
    }

#if 0
    printf("For indexing, change the IN expr:\n");
    sqlite3TreeViewExpr(0, pX, 0);
    printf("Into:\n");
    sqlite3TreeViewExpr(0, pNew, 0);
#endif
  }
  return pNew;
}