#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_5__* pVtabIdx; } ;
struct TYPE_23__ {int nOBSat; scalar_t__ nEq; int /*<<< orphan*/  wsFlags; TYPE_3__ u; } ;
struct sqlite3_index_constraint_usage {scalar_t__ argvIndex; int used; scalar_t__ omit; double rCost; TYPE_4__ plan; } ;
struct sqlite3_index_constraint {int iTermOffset; int usable; } ;
struct SrcList_item {TYPE_9__* pTab; } ;
struct TYPE_24__ {int nConstraint; scalar_t__ orderByConsumed; double estimatedCost; int nOrderBy; int /*<<< orphan*/  aConstraint; scalar_t__ needToFreeIdxStr; scalar_t__ idxNum; scalar_t__ idxStr; struct sqlite3_index_constraint_usage* aConstraintUsage; } ;
typedef  TYPE_5__ sqlite3_index_info ;
typedef  int /*<<< orphan*/  pUsage ;
struct TYPE_25__ {int prereqRight; int eOperator; } ;
typedef  TYPE_6__ WhereTerm ;
struct TYPE_26__ {TYPE_6__* a; } ;
typedef  TYPE_7__ WhereClause ;
struct TYPE_27__ {int notReady; int i; struct sqlite3_index_constraint_usage cost; TYPE_2__* aLevel; scalar_t__ pOrderBy; TYPE_5__** ppIdxInfo; struct SrcList_item* pSrc; TYPE_7__* pWC; TYPE_10__* pParse; } ;
typedef  TYPE_8__ WhereBestIdx ;
struct TYPE_28__ {scalar_t__* azModuleArg; } ;
typedef  TYPE_9__ Table ;
struct TYPE_20__ {int wsFlags; int nOBSat; } ;
struct TYPE_21__ {TYPE_1__ plan; } ;
struct TYPE_19__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_10__ Parse ;

/* Variables and functions */
 double SQLITE_BIG_DBL ; 
 int /*<<< orphan*/  WHERE_ORDERED ; 
 int WHERE_UNIQUE ; 
 int /*<<< orphan*/  WHERE_VIRTUALTABLE ; 
 int WO_IN ; 
 TYPE_5__* allocateIndexInfo (TYPE_8__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bestOrClauseIndex (TYPE_8__*) ; 
 double estLog (double) ; 
 int /*<<< orphan*/  memset (struct sqlite3_index_constraint_usage*,int /*<<< orphan*/ ,int) ; 
 int sqlite3GetVTable (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 scalar_t__ vtabBestIndex (TYPE_10__*,TYPE_9__*,TYPE_5__*) ; 

__attribute__((used)) static void bestVirtualIndex(WhereBestIdx *p){
  Parse *pParse = p->pParse;      /* The parsing context */
  WhereClause *pWC = p->pWC;      /* The WHERE clause */
  struct SrcList_item *pSrc = p->pSrc; /* The FROM clause term to search */
  Table *pTab = pSrc->pTab;
  sqlite3_index_info *pIdxInfo;
  struct sqlite3_index_constraint *pIdxCons;
  struct sqlite3_index_constraint_usage *pUsage;
  WhereTerm *pTerm;
  int i, j;
  int nOrderBy;
  int bAllowIN;                   /* Allow IN optimizations */
  double rCost;

  /* Make sure wsFlags is initialized to some sane value. Otherwise, if the 
  ** malloc in allocateIndexInfo() fails and this function returns leaving
  ** wsFlags in an uninitialized state, the caller may behave unpredictably.
  */
  memset(&p->cost, 0, sizeof(p->cost));
  p->cost.plan.wsFlags = WHERE_VIRTUALTABLE;

  /* If the sqlite3_index_info structure has not been previously
  ** allocated and initialized, then allocate and initialize it now.
  */
  pIdxInfo = *p->ppIdxInfo;
  if( pIdxInfo==0 ){
    *p->ppIdxInfo = pIdxInfo = allocateIndexInfo(p);
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

  /* Try once or twice.  On the first attempt, allow IN optimizations.
  ** If an IN optimization is accepted by the virtual table xBestIndex
  ** method, but the  pInfo->aConstrainUsage.omit flag is not set, then
  ** the query will not work because it might allow duplicate rows in
  ** output.  In that case, run the xBestIndex method a second time
  ** without the IN constraints.  Usually this loop only runs once.
  ** The loop will exit using a "break" statement.
  */
  for(bAllowIN=1; 1; bAllowIN--){
    assert( bAllowIN==0 || bAllowIN==1 );

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
      if( (pTerm->prereqRight&p->notReady)==0
       && (bAllowIN || (pTerm->eOperator & WO_IN)==0)
      ){
        pIdxCons->usable = 1;
      }else{
        pIdxCons->usable = 0;
      }
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
    if( !p->pOrderBy ){
      pIdxInfo->nOrderBy = 0;
    }
  
    if( vtabBestIndex(pParse, pTab, pIdxInfo) ){
      return;
    }
  
    pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
    for(i=0; i<pIdxInfo->nConstraint; i++, pIdxCons++){
      if( pUsage[i].argvIndex>0 ){
        j = pIdxCons->iTermOffset;
        pTerm = &pWC->a[j];
        p->cost.used |= pTerm->prereqRight;
        if( (pTerm->eOperator & WO_IN)!=0 ){
          if( pUsage[i].omit==0 ){
            /* Do not attempt to use an IN constraint if the virtual table
            ** says that the equivalent EQ constraint cannot be safely omitted.
            ** If we do attempt to use such a constraint, some rows might be
            ** repeated in the output. */
            break;
          }
          /* A virtual table that is constrained by an IN clause may not
          ** consume the ORDER BY clause because (1) the order of IN terms
          ** is not necessarily related to the order of output terms and
          ** (2) Multiple outputs from a single IN value will not merge
          ** together.  */
          pIdxInfo->orderByConsumed = 0;
        }
      }
    }
    if( i>=pIdxInfo->nConstraint ) break;
  }

  /* The orderByConsumed signal is only valid if all outer loops collectively
  ** generate just a single row of output.
  */
  if( pIdxInfo->orderByConsumed ){
    for(i=0; i<p->i; i++){
      if( (p->aLevel[i].plan.wsFlags & WHERE_UNIQUE)==0 ){
        pIdxInfo->orderByConsumed = 0;
      }
    }
  }
  
  /* If there is an ORDER BY clause, and the selected virtual table index
  ** does not satisfy it, increase the cost of the scan accordingly. This
  ** matches the processing for non-virtual tables in bestBtreeIndex().
  */
  rCost = pIdxInfo->estimatedCost;
  if( p->pOrderBy && pIdxInfo->orderByConsumed==0 ){
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
    p->cost.rCost = (SQLITE_BIG_DBL/((double)2));
  }else{
    p->cost.rCost = rCost;
  }
  p->cost.plan.u.pVtabIdx = pIdxInfo;
  if( pIdxInfo->orderByConsumed ){
    p->cost.plan.wsFlags |= WHERE_ORDERED;
    p->cost.plan.nOBSat = nOrderBy;
  }else{
    p->cost.plan.nOBSat = p->i ? p->aLevel[p->i-1].plan.nOBSat : 0;
  }
  p->cost.plan.nEq = 0;
  pIdxInfo->nOrderBy = nOrderBy;

  /* Try to find a more efficient access pattern by using multiple indexes
  ** to optimize an OR expression within the WHERE clause. 
  */
  bestOrClauseIndex(p);
}