#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {TYPE_22__* pFuncArg; } ;
struct TYPE_39__ {int isCorrelated; scalar_t__ isTabFunc; } ;
struct SrcList_item {char* zName; TYPE_8__* pSelect; TYPE_1__ u1; TYPE_4__ fg; } ;
struct ExprList_item {int /*<<< orphan*/  pExpr; } ;
struct TYPE_41__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_6__ sqlite3 ;
typedef  int /*<<< orphan*/  sNC ;
struct TYPE_38__ {TYPE_10__* pNC; } ;
struct TYPE_42__ {TYPE_9__* pParse; TYPE_3__ u; } ;
typedef  TYPE_7__ Walker ;
struct TYPE_44__ {char* zAuthContext; scalar_t__ nErr; TYPE_6__* db; } ;
struct TYPE_43__ {int selFlags; scalar_t__ pOrderBy; struct TYPE_43__* pPrior; TYPE_13__* pNext; TYPE_22__* pEList; TYPE_5__* pSrc; int /*<<< orphan*/  pWhere; int /*<<< orphan*/  pHaving; TYPE_11__* pGroupBy; int /*<<< orphan*/  pLimit; } ;
struct TYPE_40__ {int nSrc; struct SrcList_item* a; } ;
struct TYPE_37__ {scalar_t__ nExpr; } ;
struct TYPE_36__ {scalar_t__ nExpr; } ;
struct TYPE_34__ {TYPE_2__* pEList; } ;
struct TYPE_33__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_32__ {int ncFlags; struct TYPE_32__* pNext; TYPE_22__* pEList; TYPE_5__* pSrcList; scalar_t__ nRef; TYPE_9__* pParse; } ;
typedef  TYPE_8__ Select ;
typedef  TYPE_9__ Parse ;
typedef  TYPE_10__ NameContext ;
typedef  TYPE_11__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Agg ; 
 scalar_t__ ExprHasProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NC_AllowAgg ; 
 int NC_HasAgg ; 
 int NC_MinMaxAgg ; 
 int SF_Aggregate ; 
 int SF_Converted ; 
 int SF_Expanded ; 
 int SF_MinMaxAgg ; 
 int SF_Resolved ; 
 int WRC_Abort ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resolveCompoundOrderBy (TYPE_9__*,TYPE_8__*) ; 
 scalar_t__ resolveOrderGroupBy (TYPE_10__*,TYPE_8__*,TYPE_11__*,char*) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_9__*,char*) ; 
 scalar_t__ sqlite3ResolveExprListNames (TYPE_10__*,TYPE_22__*) ; 
 scalar_t__ sqlite3ResolveExprNames (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ResolveSelectNames (TYPE_9__*,TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  sqlite3SelectPrep (TYPE_9__*,TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  sqlite3SelectWrongNumTermsError (TYPE_9__*,TYPE_13__*) ; 

__attribute__((used)) static int resolveSelectStep(Walker *pWalker, Select *p){
  NameContext *pOuterNC;  /* Context that contains this SELECT */
  NameContext sNC;        /* Name context of this SELECT */
  int isCompound;         /* True if p is a compound select */
  int nCompound;          /* Number of compound terms processed so far */
  Parse *pParse;          /* Parsing context */
  int i;                  /* Loop counter */
  ExprList *pGroupBy;     /* The GROUP BY clause */
  Select *pLeftmost;      /* Left-most of SELECT of a compound */
  sqlite3 *db;            /* Database connection */
  

  assert( p!=0 );
  if( p->selFlags & SF_Resolved ){
    return WRC_Prune;
  }
  pOuterNC = pWalker->u.pNC;
  pParse = pWalker->pParse;
  db = pParse->db;

  /* Normally sqlite3SelectExpand() will be called first and will have
  ** already expanded this SELECT.  However, if this is a subquery within
  ** an expression, sqlite3ResolveExprNames() will be called without a
  ** prior call to sqlite3SelectExpand().  When that happens, let
  ** sqlite3SelectPrep() do all of the processing for this SELECT.
  ** sqlite3SelectPrep() will invoke both sqlite3SelectExpand() and
  ** this routine in the correct order.
  */
  if( (p->selFlags & SF_Expanded)==0 ){
    sqlite3SelectPrep(pParse, p, pOuterNC);
    return (pParse->nErr || db->mallocFailed) ? WRC_Abort : WRC_Prune;
  }

  isCompound = p->pPrior!=0;
  nCompound = 0;
  pLeftmost = p;
  while( p ){
    assert( (p->selFlags & SF_Expanded)!=0 );
    assert( (p->selFlags & SF_Resolved)==0 );
    p->selFlags |= SF_Resolved;

    /* Resolve the expressions in the LIMIT and OFFSET clauses. These
    ** are not allowed to refer to any names, so pass an empty NameContext.
    */
    memset(&sNC, 0, sizeof(sNC));
    sNC.pParse = pParse;
    if( sqlite3ResolveExprNames(&sNC, p->pLimit) ){
      return WRC_Abort;
    }

    /* If the SF_Converted flags is set, then this Select object was
    ** was created by the convertCompoundSelectToSubquery() function.
    ** In this case the ORDER BY clause (p->pOrderBy) should be resolved
    ** as if it were part of the sub-query, not the parent. This block
    ** moves the pOrderBy down to the sub-query. It will be moved back
    ** after the names have been resolved.  */
    if( p->selFlags & SF_Converted ){
      Select *pSub = p->pSrc->a[0].pSelect;
      assert( p->pSrc->nSrc==1 && p->pOrderBy );
      assert( pSub->pPrior && pSub->pOrderBy==0 );
      pSub->pOrderBy = p->pOrderBy;
      p->pOrderBy = 0;
    }
  
    /* Recursively resolve names in all subqueries
    */
    for(i=0; i<p->pSrc->nSrc; i++){
      struct SrcList_item *pItem = &p->pSrc->a[i];
      if( pItem->pSelect ){
        NameContext *pNC;         /* Used to iterate name contexts */
        int nRef = 0;             /* Refcount for pOuterNC and outer contexts */
        const char *zSavedContext = pParse->zAuthContext;

        /* Count the total number of references to pOuterNC and all of its
        ** parent contexts. After resolving references to expressions in
        ** pItem->pSelect, check if this value has changed. If so, then
        ** SELECT statement pItem->pSelect must be correlated. Set the
        ** pItem->fg.isCorrelated flag if this is the case. */
        for(pNC=pOuterNC; pNC; pNC=pNC->pNext) nRef += pNC->nRef;

        if( pItem->zName ) pParse->zAuthContext = pItem->zName;
        sqlite3ResolveSelectNames(pParse, pItem->pSelect, pOuterNC);
        pParse->zAuthContext = zSavedContext;
        if( pParse->nErr || db->mallocFailed ) return WRC_Abort;

        for(pNC=pOuterNC; pNC; pNC=pNC->pNext) nRef -= pNC->nRef;
        assert( pItem->fg.isCorrelated==0 && nRef<=0 );
        pItem->fg.isCorrelated = (nRef!=0);
      }
    }
  
    /* Set up the local name-context to pass to sqlite3ResolveExprNames() to
    ** resolve the result-set expression list.
    */
    sNC.ncFlags = NC_AllowAgg;
    sNC.pSrcList = p->pSrc;
    sNC.pNext = pOuterNC;
  
    /* Resolve names in the result set. */
    if( sqlite3ResolveExprListNames(&sNC, p->pEList) ) return WRC_Abort;
  
    /* If there are no aggregate functions in the result-set, and no GROUP BY 
    ** expression, do not allow aggregates in any of the other expressions.
    */
    assert( (p->selFlags & SF_Aggregate)==0 );
    pGroupBy = p->pGroupBy;
    if( pGroupBy || (sNC.ncFlags & NC_HasAgg)!=0 ){
      assert( NC_MinMaxAgg==SF_MinMaxAgg );
      p->selFlags |= SF_Aggregate | (sNC.ncFlags&NC_MinMaxAgg);
    }else{
      sNC.ncFlags &= ~NC_AllowAgg;
    }
  
    /* If a HAVING clause is present, then there must be a GROUP BY clause.
    */
    if( p->pHaving && !pGroupBy ){
      sqlite3ErrorMsg(pParse, "a GROUP BY clause is required before HAVING");
      return WRC_Abort;
    }
  
    /* Add the output column list to the name-context before parsing the
    ** other expressions in the SELECT statement. This is so that
    ** expressions in the WHERE clause (etc.) can refer to expressions by
    ** aliases in the result set.
    **
    ** Minor point: If this is the case, then the expression will be
    ** re-evaluated for each reference to it.
    */
    sNC.pEList = p->pEList;
    if( sqlite3ResolveExprNames(&sNC, p->pHaving) ) return WRC_Abort;
    if( sqlite3ResolveExprNames(&sNC, p->pWhere) ) return WRC_Abort;

    /* Resolve names in table-valued-function arguments */
    for(i=0; i<p->pSrc->nSrc; i++){
      struct SrcList_item *pItem = &p->pSrc->a[i];
      if( pItem->fg.isTabFunc
       && sqlite3ResolveExprListNames(&sNC, pItem->u1.pFuncArg) 
      ){
        return WRC_Abort;
      }
    }

    /* The ORDER BY and GROUP BY clauses may not refer to terms in
    ** outer queries 
    */
    sNC.pNext = 0;
    sNC.ncFlags |= NC_AllowAgg;

    /* If this is a converted compound query, move the ORDER BY clause from 
    ** the sub-query back to the parent query. At this point each term
    ** within the ORDER BY clause has been transformed to an integer value.
    ** These integers will be replaced by copies of the corresponding result
    ** set expressions by the call to resolveOrderGroupBy() below.  */
    if( p->selFlags & SF_Converted ){
      Select *pSub = p->pSrc->a[0].pSelect;
      p->pOrderBy = pSub->pOrderBy;
      pSub->pOrderBy = 0;
    }

    /* Process the ORDER BY clause for singleton SELECT statements.
    ** The ORDER BY clause for compounds SELECT statements is handled
    ** below, after all of the result-sets for all of the elements of
    ** the compound have been resolved.
    **
    ** If there is an ORDER BY clause on a term of a compound-select other
    ** than the right-most term, then that is a syntax error.  But the error
    ** is not detected until much later, and so we need to go ahead and
    ** resolve those symbols on the incorrect ORDER BY for consistency.
    */
    if( isCompound<=nCompound  /* Defer right-most ORDER BY of a compound */
     && resolveOrderGroupBy(&sNC, p, p->pOrderBy, "ORDER")
    ){
      return WRC_Abort;
    }
    if( db->mallocFailed ){
      return WRC_Abort;
    }
  
    /* Resolve the GROUP BY clause.  At the same time, make sure 
    ** the GROUP BY clause does not contain aggregate functions.
    */
    if( pGroupBy ){
      struct ExprList_item *pItem;
    
      if( resolveOrderGroupBy(&sNC, p, pGroupBy, "GROUP") || db->mallocFailed ){
        return WRC_Abort;
      }
      for(i=0, pItem=pGroupBy->a; i<pGroupBy->nExpr; i++, pItem++){
        if( ExprHasProperty(pItem->pExpr, EP_Agg) ){
          sqlite3ErrorMsg(pParse, "aggregate functions are not allowed in "
              "the GROUP BY clause");
          return WRC_Abort;
        }
      }
    }

    /* If this is part of a compound SELECT, check that it has the right
    ** number of expressions in the select list. */
    if( p->pNext && p->pEList->nExpr!=p->pNext->pEList->nExpr ){
      sqlite3SelectWrongNumTermsError(pParse, p->pNext);
      return WRC_Abort;
    }

    /* Advance to the next term of the compound
    */
    p = p->pPrior;
    nCompound++;
  }

  /* Resolve the ORDER BY on a compound SELECT after all terms of
  ** the compound have been resolved.
  */
  if( isCompound && resolveCompoundOrderBy(pParse, pLeftmost) ){
    return WRC_Abort;
  }

  return WRC_Prune;
}