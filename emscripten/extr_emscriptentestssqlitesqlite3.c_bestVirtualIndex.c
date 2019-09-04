#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* pVtabIdx; } ;
struct TYPE_21__ {scalar_t__ nEq; int /*<<< orphan*/  wsFlags; TYPE_1__ u; } ;
struct sqlite3_index_constraint_usage {scalar_t__ argvIndex; int used; double rCost; TYPE_2__ plan; } ;
struct sqlite3_index_constraint {int iTermOffset; int usable; } ;
struct SrcList_item {TYPE_6__* pTab; } ;
struct TYPE_22__ {int nConstraint; scalar_t__ orderByConsumed; double estimatedCost; int nOrderBy; int /*<<< orphan*/  aConstraint; scalar_t__ needToFreeIdxStr; scalar_t__ idxNum; scalar_t__ idxStr; struct sqlite3_index_constraint_usage* aConstraintUsage; } ;
typedef  TYPE_3__ sqlite3_index_info ;
typedef  int /*<<< orphan*/  pUsage ;
struct TYPE_23__ {int prereqRight; } ;
typedef  TYPE_4__ WhereTerm ;
typedef  struct sqlite3_index_constraint_usage WhereCost ;
struct TYPE_24__ {TYPE_4__* a; } ;
typedef  TYPE_5__ WhereClause ;
struct TYPE_25__ {scalar_t__* azModuleArg; } ;
typedef  TYPE_6__ Table ;
struct TYPE_26__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_7__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;
typedef  int Bitmask ;

/* Variables and functions */
 double SQLITE_BIG_DBL ; 
 int /*<<< orphan*/  WHERE_ORDERBY ; 
 int /*<<< orphan*/  WHERE_VIRTUALTABLE ; 
 TYPE_3__* allocateIndexInfo (TYPE_7__*,TYPE_5__*,struct SrcList_item*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bestOrClauseIndex (TYPE_7__*,TYPE_5__*,struct SrcList_item*,int,int,int /*<<< orphan*/ *,struct sqlite3_index_constraint_usage*) ; 
 double estLog (double) ; 
 int /*<<< orphan*/  memset (struct sqlite3_index_constraint_usage*,int /*<<< orphan*/ ,int) ; 
 int sqlite3GetVTable (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 scalar_t__ vtabBestIndex (TYPE_7__*,TYPE_6__*,TYPE_3__*) ; 

__attribute__((used)) static void bestVirtualIndex(
  Parse *pParse,                  /* The parsing context */
  WhereClause *pWC,               /* The WHERE clause */
  struct SrcList_item *pSrc,      /* The FROM clause term to search */
  Bitmask notReady,               /* Mask of cursors not available for index */
  Bitmask notValid,               /* Cursors not valid for any purpose */
  ExprList *pOrderBy,             /* The order by clause */
  WhereCost *pCost,               /* Lowest cost query plan */
  sqlite3_index_info **ppIdxInfo  /* Index information passed to xBestIndex */
){
  Table *pTab = pSrc->pTab;
  sqlite3_index_info *pIdxInfo;
  struct sqlite3_index_constraint *pIdxCons;
  struct sqlite3_index_constraint_usage *pUsage;
  WhereTerm *pTerm;
  int i, j;
  int nOrderBy;
  double rCost;

  /* Make sure wsFlags is initialized to some sane value. Otherwise, if the 
  ** malloc in allocateIndexInfo() fails and this function returns leaving
  ** wsFlags in an uninitialized state, the caller may behave unpredictably.
  */
  memset(pCost, 0, sizeof(*pCost));
  pCost->plan.wsFlags = WHERE_VIRTUALTABLE;

  /* If the sqlite3_index_info structure has not been previously
  ** allocated and initialized, then allocate and initialize it now.
  */
  pIdxInfo = *ppIdxInfo;
  if( pIdxInfo==0 ){
    *ppIdxInfo = pIdxInfo = allocateIndexInfo(pParse, pWC, pSrc, pOrderBy);
  }
  if( pIdxInfo==0 ){
    return;
  }

  /* At this point, the sqlite3_index_info structure that pIdxInfo points
  ** to will have been initialized, either during the current invocation or
  ** during some prior invocation.  Now we just have to customize the
  ** details of pIdxInfo for the current invocation and pass it to
  ** xBestIndex.
  */

  /* The module name must be defined. Also, by this point there must
  ** be a pointer to an sqlite3_vtab structure. Otherwise
  ** sqlite3ViewGetColumnNames() would have picked up the error. 
  */
  assert( pTab->azModuleArg && pTab->azModuleArg[0] );
  assert( sqlite3GetVTable(pParse->db, pTab) );

  /* Set the aConstraint[].usable fields and initialize all 
  ** output variables to zero.
  **
  ** aConstraint[].usable is true for constraints where the right-hand
  ** side contains only references to tables to the left of the current
  ** table.  In other words, if the constraint is of the form:
  **
  **           column = expr
  **
  ** and we are evaluating a join, then the constraint on column is 
  ** only valid if all tables referenced in expr occur to the left
  ** of the table containing column.
  **
  ** The aConstraints[] array contains entries for all constraints
  ** on the current table.  That way we only have to compute it once
  ** even though we might try to pick the best index multiple times.
  ** For each attempt at picking an index, the order of tables in the
  ** join might be different so we have to recompute the usable flag
  ** each time.
  */
  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
  pUsage = pIdxInfo->aConstraintUsage;
  for(i=0; i<pIdxInfo->nConstraint; i++, pIdxCons++){
    j = pIdxCons->iTermOffset;
    pTerm = &pWC->a[j];
    pIdxCons->usable = (pTerm->prereqRight&notReady) ? 0 : 1;
  }
  memset(pUsage, 0, sizeof(pUsage[0])*pIdxInfo->nConstraint);
  if( pIdxInfo->needToFreeIdxStr ){
    sqlite3_free(pIdxInfo->idxStr);
  }
  pIdxInfo->idxStr = 0;
  pIdxInfo->idxNum = 0;
  pIdxInfo->needToFreeIdxStr = 0;
  pIdxInfo->orderByConsumed = 0;
  /* ((double)2) In case of SQLITE_OMIT_FLOATING_POINT... */
  pIdxInfo->estimatedCost = SQLITE_BIG_DBL / ((double)2);
  nOrderBy = pIdxInfo->nOrderBy;
  if( !pOrderBy ){
    pIdxInfo->nOrderBy = 0;
  }

  if( vtabBestIndex(pParse, pTab, pIdxInfo) ){
    return;
  }

  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++){
    if( pUsage[i].argvIndex>0 ){
      pCost->used |= pWC->a[pIdxCons[i].iTermOffset].prereqRight;
    }
  }

  /* If there is an ORDER BY clause, and the selected virtual table index
  ** does not satisfy it, increase the cost of the scan accordingly. This
  ** matches the processing for non-virtual tables in bestBtreeIndex().
  */
  rCost = pIdxInfo->estimatedCost;
  if( pOrderBy && pIdxInfo->orderByConsumed==0 ){
    rCost += estLog(rCost)*rCost;
  }

  /* The cost is not allowed to be larger than SQLITE_BIG_DBL (the
  ** inital value of lowestCost in this loop. If it is, then the
  ** (cost<lowestCost) test below will never be true.
  ** 
  ** Use "(double)2" instead of "2.0" in case OMIT_FLOATING_POINT 
  ** is defined.
  */
  if( (SQLITE_BIG_DBL/((double)2))<rCost ){
    pCost->rCost = (SQLITE_BIG_DBL/((double)2));
  }else{
    pCost->rCost = rCost;
  }
  pCost->plan.u.pVtabIdx = pIdxInfo;
  if( pIdxInfo->orderByConsumed ){
    pCost->plan.wsFlags |= WHERE_ORDERBY;
  }
  pCost->plan.nEq = 0;
  pIdxInfo->nOrderBy = nOrderBy;

  /* Try to find a more efficient access pattern by using multiple indexes
  ** to optimize an OR expression within the WHERE clause. 
  */
  bestOrClauseIndex(pParse, pWC, pSrc, notReady, notValid, pOrderBy, pCost);
}