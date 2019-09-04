#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  void* u16 ;
struct ExprList_item {void* iCol; int /*<<< orphan*/ * pExpr; } ;
struct TYPE_14__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_13__ {int /*<<< orphan*/ * pParse; } ;
struct TYPE_12__ {TYPE_10__* pEList; } ;
struct TYPE_11__ {int nExpr; } ;
typedef  TYPE_1__ Select ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_2__ NameContext ;
typedef  TYPE_3__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int resolveAsName (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolveOutOfRangeError (int /*<<< orphan*/ *,char const*,int,int) ; 
 scalar_t__ sqlite3ExprIsInteger (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ sqlite3ResolveExprNames (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int sqlite3ResolveOrderGroupBy (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*,char const*) ; 

__attribute__((used)) static int resolveOrderGroupBy(
  NameContext *pNC,     /* The name context of the SELECT statement */
  Select *pSelect,      /* The SELECT statement holding pOrderBy */
  ExprList *pOrderBy,   /* An ORDER BY or GROUP BY clause to resolve */
  const char *zType     /* Either "ORDER" or "GROUP", as appropriate */
){
  int i;                         /* Loop counter */
  int iCol;                      /* Column number */
  struct ExprList_item *pItem;   /* A term of the ORDER BY clause */
  Parse *pParse;                 /* Parsing context */
  int nResult;                   /* Number of terms in the result set */

  if( pOrderBy==0 ) return 0;
  nResult = pSelect->pEList->nExpr;
  pParse = pNC->pParse;
  for(i=0, pItem=pOrderBy->a; i<pOrderBy->nExpr; i++, pItem++){
    Expr *pE = pItem->pExpr;
    iCol = resolveAsName(pParse, pSelect->pEList, pE);
    if( iCol>0 ){
      /* If an AS-name match is found, mark this ORDER BY column as being
      ** a copy of the iCol-th result-set column.  The subsequent call to
      ** sqlite3ResolveOrderGroupBy() will convert the expression to a
      ** copy of the iCol-th result-set expression. */
      pItem->iCol = (u16)iCol;
      continue;
    }
    if( sqlite3ExprIsInteger(pE, &iCol) ){
      /* The ORDER BY term is an integer constant.  Again, set the column
      ** number so that sqlite3ResolveOrderGroupBy() will convert the
      ** order-by term to a copy of the result-set expression */
      if( iCol<1 ){
        resolveOutOfRangeError(pParse, zType, i+1, nResult);
        return 1;
      }
      pItem->iCol = (u16)iCol;
      continue;
    }

    /* Otherwise, treat the ORDER BY term as an ordinary expression */
    pItem->iCol = 0;
    if( sqlite3ResolveExprNames(pNC, pE) ){
      return 1;
    }
  }
  return sqlite3ResolveOrderGroupBy(pParse, pSelect, pOrderBy, zType);
}