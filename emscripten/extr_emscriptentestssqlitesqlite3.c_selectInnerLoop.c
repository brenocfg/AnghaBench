#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_27__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_26__ {int nMem; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_25__ {int iLimit; int /*<<< orphan*/  affinity; } ;
struct TYPE_24__ {int eDest; int iParm; int iMem; int nMem; int /*<<< orphan*/  affinity; } ;
struct TYPE_23__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ SelectDest ;
typedef  TYPE_3__ Select ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ ExprList ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  OPFLAG_APPEND ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_IdxDelete ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IfZero ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_ResultRow ; 
 int /*<<< orphan*/  OP_Yield ; 
#define  SRT_Coroutine 136 
 int SRT_Discard ; 
#define  SRT_EphemTab 135 
#define  SRT_Except 134 
#define  SRT_Exists 133 
#define  SRT_Mem 132 
#define  SRT_Output 131 
#define  SRT_Set 130 
#define  SRT_Table 129 
#define  SRT_Union 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeDistinct (TYPE_4__*,int,int,int,int) ; 
 int /*<<< orphan*/  codeOffset (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pushOntoSorter (TYPE_4__*,TYPE_5__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3CompareAffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprCacheAffinityChange (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheClear (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3ExprCodeExprList (TYPE_4__*,TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeMove (TYPE_4__*,int,int,int) ; 
 int sqlite3GetTempReg (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void selectInnerLoop(
  Parse *pParse,          /* The parser context */
  Select *p,              /* The complete select statement being coded */
  ExprList *pEList,       /* List of values being extracted */
  int srcTab,             /* Pull data from this table */
  int nColumn,            /* Number of columns in the source table */
  ExprList *pOrderBy,     /* If not NULL, sort results using this key */
  int distinct,           /* If >=0, make sure results are distinct */
  SelectDest *pDest,      /* How to dispose of the results */
  int iContinue,          /* Jump here to continue with next row */
  int iBreak              /* Jump here to break out of the inner loop */
){
  Vdbe *v = pParse->pVdbe;
  int i;
  int hasDistinct;        /* True if the DISTINCT keyword is present */
  int regResult;              /* Start of memory holding result set */
  int eDest = pDest->eDest;   /* How to dispose of results */
  int iParm = pDest->iParm;   /* First argument to disposal method */
  int nResultCol;             /* Number of result columns */

  assert( v );
  if( NEVER(v==0) ) return;
  assert( pEList!=0 );
  hasDistinct = distinct>=0;
  if( pOrderBy==0 && !hasDistinct ){
    codeOffset(v, p, iContinue);
  }

  /* Pull the requested columns.
  */
  if( nColumn>0 ){
    nResultCol = nColumn;
  }else{
    nResultCol = pEList->nExpr;
  }
  if( pDest->iMem==0 ){
    pDest->iMem = pParse->nMem+1;
    pDest->nMem = nResultCol;
    pParse->nMem += nResultCol;
  }else{ 
    assert( pDest->nMem==nResultCol );
  }
  regResult = pDest->iMem;
  if( nColumn>0 ){
    for(i=0; i<nColumn; i++){
      sqlite3VdbeAddOp3(v, OP_Column, srcTab, i, regResult+i);
    }
  }else if( eDest!=SRT_Exists ){
    /* If the destination is an EXISTS(...) expression, the actual
    ** values returned by the SELECT are not required.
    */
    sqlite3ExprCacheClear(pParse);
    sqlite3ExprCodeExprList(pParse, pEList, regResult, eDest==SRT_Output);
  }
  nColumn = nResultCol;

  /* If the DISTINCT keyword was present on the SELECT statement
  ** and this row has been seen before, then do not make this row
  ** part of the result.
  */
  if( hasDistinct ){
    assert( pEList!=0 );
    assert( pEList->nExpr==nColumn );
    codeDistinct(pParse, distinct, iContinue, nColumn, regResult);
    if( pOrderBy==0 ){
      codeOffset(v, p, iContinue);
    }
  }

  switch( eDest ){
    /* In this mode, write each query result to the key of the temporary
    ** table iParm.
    */
#ifndef SQLITE_OMIT_COMPOUND_SELECT
    case SRT_Union: {
      int r1;
      r1 = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regResult, nColumn, r1);
      sqlite3VdbeAddOp2(v, OP_IdxInsert, iParm, r1);
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }

    /* Construct a record from the query result, but instead of
    ** saving that record, use it as a key to delete elements from
    ** the temporary table iParm.
    */
    case SRT_Except: {
      sqlite3VdbeAddOp3(v, OP_IdxDelete, iParm, regResult, nColumn);
      break;
    }
#endif

    /* Store the result as data using a unique key.
    */
    case SRT_Table:
    case SRT_EphemTab: {
      int r1 = sqlite3GetTempReg(pParse);
      testcase( eDest==SRT_Table );
      testcase( eDest==SRT_EphemTab );
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regResult, nColumn, r1);
      if( pOrderBy ){
        pushOntoSorter(pParse, pOrderBy, p, r1);
      }else{
        int r2 = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp2(v, OP_NewRowid, iParm, r2);
        sqlite3VdbeAddOp3(v, OP_Insert, iParm, r1, r2);
        sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
        sqlite3ReleaseTempReg(pParse, r2);
      }
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }

#ifndef SQLITE_OMIT_SUBQUERY
    /* If we are creating a set for an "expr IN (SELECT ...)" construct,
    ** then there should be a single item on the stack.  Write this
    ** item into the set table with bogus data.
    */
    case SRT_Set: {
      assert( nColumn==1 );
      p->affinity = sqlite3CompareAffinity(pEList->a[0].pExpr, pDest->affinity);
      if( pOrderBy ){
        /* At first glance you would think we could optimize out the
        ** ORDER BY in this case since the order of entries in the set
        ** does not matter.  But there might be a LIMIT clause, in which
        ** case the order does matter */
        pushOntoSorter(pParse, pOrderBy, p, regResult);
      }else{
        int r1 = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp4(v, OP_MakeRecord, regResult, 1, r1, &p->affinity, 1);
        sqlite3ExprCacheAffinityChange(pParse, regResult, 1);
        sqlite3VdbeAddOp2(v, OP_IdxInsert, iParm, r1);
        sqlite3ReleaseTempReg(pParse, r1);
      }
      break;
    }

    /* If any row exist in the result set, record that fact and abort.
    */
    case SRT_Exists: {
      sqlite3VdbeAddOp2(v, OP_Integer, 1, iParm);
      /* The LIMIT clause will terminate the loop for us */
      break;
    }

    /* If this is a scalar select that is part of an expression, then
    ** store the results in the appropriate memory cell and break out
    ** of the scan loop.
    */
    case SRT_Mem: {
      assert( nColumn==1 );
      if( pOrderBy ){
        pushOntoSorter(pParse, pOrderBy, p, regResult);
      }else{
        sqlite3ExprCodeMove(pParse, regResult, iParm, 1);
        /* The LIMIT clause will jump out of the loop for us */
      }
      break;
    }
#endif /* #ifndef SQLITE_OMIT_SUBQUERY */

    /* Send the data to the callback function or to a subroutine.  In the
    ** case of a subroutine, the subroutine itself is responsible for
    ** popping the data from the stack.
    */
    case SRT_Coroutine:
    case SRT_Output: {
      testcase( eDest==SRT_Coroutine );
      testcase( eDest==SRT_Output );
      if( pOrderBy ){
        int r1 = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp3(v, OP_MakeRecord, regResult, nColumn, r1);
        pushOntoSorter(pParse, pOrderBy, p, r1);
        sqlite3ReleaseTempReg(pParse, r1);
      }else if( eDest==SRT_Coroutine ){
        sqlite3VdbeAddOp1(v, OP_Yield, pDest->iParm);
      }else{
        sqlite3VdbeAddOp2(v, OP_ResultRow, regResult, nColumn);
        sqlite3ExprCacheAffinityChange(pParse, regResult, nColumn);
      }
      break;
    }

#if !defined(SQLITE_OMIT_TRIGGER)
    /* Discard the results.  This is used for SELECT statements inside
    ** the body of a TRIGGER.  The purpose of such selects is to call
    ** user-defined functions that have side effects.  We do not care
    ** about the actual results of the select.
    */
    default: {
      assert( eDest==SRT_Discard );
      break;
    }
#endif
  }

  /* Jump to the end of the loop if the LIMIT is reached.  Except, if
  ** there is a sorter, in which case the sorter has already limited
  ** the output for us.
  */
  if( pOrderBy==0 && p->iLimit ){
    sqlite3VdbeAddOp3(v, OP_IfZero, p->iLimit, iBreak, -1);
  }
}