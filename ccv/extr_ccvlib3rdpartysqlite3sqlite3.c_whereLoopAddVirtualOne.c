#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int u16 ;
struct sqlite3_index_constraint_usage {int argvIndex; scalar_t__ omit; } ;
struct sqlite3_index_constraint {size_t iTermOffset; int usable; } ;
struct SrcList_item {TYPE_14__* pTab; scalar_t__ colUsed; } ;
typedef  int /*<<< orphan*/  sqlite3_uint64 ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_21__ {int nConstraint; int needToFreeIdxStr; double estimatedCost; int estimatedRows; int idxFlags; scalar_t__ nOrderBy; scalar_t__ orderByConsumed; scalar_t__ idxStr; scalar_t__ idxNum; int /*<<< orphan*/  aConstraint; scalar_t__ colUsed; struct sqlite3_index_constraint_usage* aConstraintUsage; } ;
typedef  TYPE_5__ sqlite3_index_info ;
typedef  int /*<<< orphan*/  pUsage ;
typedef  scalar_t__ i8 ;
struct TYPE_22__ {int prereqRight; int eOperator; } ;
typedef  TYPE_6__ WhereTerm ;
struct TYPE_23__ {TYPE_2__* pWInfo; TYPE_8__* pNew; TYPE_9__* pWC; } ;
typedef  TYPE_7__ WhereLoopBuilder ;
struct TYPE_19__ {int omitMask; int needFree; scalar_t__ idxStr; scalar_t__ isOrdered; scalar_t__ idxNum; } ;
struct TYPE_20__ {TYPE_3__ vtab; } ;
struct TYPE_24__ {size_t iTab; int prereq; int nLSlot; int nLTerm; scalar_t__* aLTerm; TYPE_4__ u; int /*<<< orphan*/  wsFlags; int /*<<< orphan*/  nOut; int /*<<< orphan*/  rRun; scalar_t__ rSetup; } ;
typedef  TYPE_8__ WhereLoop ;
struct TYPE_25__ {int nTerm; TYPE_6__* a; } ;
typedef  TYPE_9__ WhereClause ;
struct TYPE_18__ {TYPE_1__* pTabList; int /*<<< orphan*/ * pParse; } ;
struct TYPE_17__ {struct SrcList_item* a; } ;
struct TYPE_16__ {int /*<<< orphan*/  zName; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int Bitmask ;

/* Variables and functions */
 double SQLITE_BIG_DBL ; 
 int SQLITE_ERROR ; 
 int SQLITE_INDEX_SCAN_UNIQUE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  WHERETRACE (int,char*) ; 
 int /*<<< orphan*/  WHERE_ONEROW ; 
 int WO_IN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct sqlite3_index_constraint_usage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3LogEst (int) ; 
 int /*<<< orphan*/  sqlite3LogEstFromDouble (double) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int vtabBestIndex (int /*<<< orphan*/ *,TYPE_14__*,TYPE_5__*) ; 
 int whereLoopInsert (TYPE_7__*,TYPE_8__*) ; 

__attribute__((used)) static int whereLoopAddVirtualOne(
  WhereLoopBuilder *pBuilder,
  Bitmask mPrereq,                /* Mask of tables that must be used. */
  Bitmask mUsable,                /* Mask of usable tables */
  u16 mExclude,                   /* Exclude terms using these operators */
  sqlite3_index_info *pIdxInfo,   /* Populated object for xBestIndex */
  u16 mNoOmit,                    /* Do not omit these constraints */
  int *pbIn                       /* OUT: True if plan uses an IN(...) op */
){
  WhereClause *pWC = pBuilder->pWC;
  struct sqlite3_index_constraint *pIdxCons;
  struct sqlite3_index_constraint_usage *pUsage = pIdxInfo->aConstraintUsage;
  int i;
  int mxTerm;
  int rc = SQLITE_OK;
  WhereLoop *pNew = pBuilder->pNew;
  Parse *pParse = pBuilder->pWInfo->pParse;
  struct SrcList_item *pSrc = &pBuilder->pWInfo->pTabList->a[pNew->iTab];
  int nConstraint = pIdxInfo->nConstraint;

  assert( (mUsable & mPrereq)==mPrereq );
  *pbIn = 0;
  pNew->prereq = mPrereq;

  /* Set the usable flag on the subset of constraints identified by 
  ** arguments mUsable and mExclude. */
  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
  for(i=0; i<nConstraint; i++, pIdxCons++){
    WhereTerm *pTerm = &pWC->a[pIdxCons->iTermOffset];
    pIdxCons->usable = 0;
    if( (pTerm->prereqRight & mUsable)==pTerm->prereqRight 
     && (pTerm->eOperator & mExclude)==0
    ){
      pIdxCons->usable = 1;
    }
  }

  /* Initialize the output fields of the sqlite3_index_info structure */
  memset(pUsage, 0, sizeof(pUsage[0])*nConstraint);
  assert( pIdxInfo->needToFreeIdxStr==0 );
  pIdxInfo->idxStr = 0;
  pIdxInfo->idxNum = 0;
  pIdxInfo->orderByConsumed = 0;
  pIdxInfo->estimatedCost = SQLITE_BIG_DBL / (double)2;
  pIdxInfo->estimatedRows = 25;
  pIdxInfo->idxFlags = 0;
  pIdxInfo->colUsed = (sqlite3_int64)pSrc->colUsed;

  /* Invoke the virtual table xBestIndex() method */
  rc = vtabBestIndex(pParse, pSrc->pTab, pIdxInfo);
  if( rc ) return rc;

  mxTerm = -1;
  assert( pNew->nLSlot>=nConstraint );
  for(i=0; i<nConstraint; i++) pNew->aLTerm[i] = 0;
  pNew->u.vtab.omitMask = 0;
  pIdxCons = *(struct sqlite3_index_constraint**)&pIdxInfo->aConstraint;
  for(i=0; i<nConstraint; i++, pIdxCons++){
    int iTerm;
    if( (iTerm = pUsage[i].argvIndex - 1)>=0 ){
      WhereTerm *pTerm;
      int j = pIdxCons->iTermOffset;
      if( iTerm>=nConstraint
       || j<0
       || j>=pWC->nTerm
       || pNew->aLTerm[iTerm]!=0
       || pIdxCons->usable==0
      ){
        sqlite3ErrorMsg(pParse,"%s.xBestIndex malfunction",pSrc->pTab->zName);
        testcase( pIdxInfo->needToFreeIdxStr );
        return SQLITE_ERROR;
      }
      testcase( iTerm==nConstraint-1 );
      testcase( j==0 );
      testcase( j==pWC->nTerm-1 );
      pTerm = &pWC->a[j];
      pNew->prereq |= pTerm->prereqRight;
      assert( iTerm<pNew->nLSlot );
      pNew->aLTerm[iTerm] = pTerm;
      if( iTerm>mxTerm ) mxTerm = iTerm;
      testcase( iTerm==15 );
      testcase( iTerm==16 );
      if( iTerm<16 && pUsage[i].omit ) pNew->u.vtab.omitMask |= 1<<iTerm;
      if( (pTerm->eOperator & WO_IN)!=0 ){
        /* A virtual table that is constrained by an IN clause may not
        ** consume the ORDER BY clause because (1) the order of IN terms
        ** is not necessarily related to the order of output terms and
        ** (2) Multiple outputs from a single IN value will not merge
        ** together.  */
        pIdxInfo->orderByConsumed = 0;
        pIdxInfo->idxFlags &= ~SQLITE_INDEX_SCAN_UNIQUE;
        *pbIn = 1; assert( (mExclude & WO_IN)==0 );
      }
    }
  }
  pNew->u.vtab.omitMask &= ~mNoOmit;

  pNew->nLTerm = mxTerm+1;
  for(i=0; i<=mxTerm; i++){
    if( pNew->aLTerm[i]==0 ){
      /* The non-zero argvIdx values must be contiguous.  Raise an
      ** error if they are not */
      sqlite3ErrorMsg(pParse,"%s.xBestIndex malfunction",pSrc->pTab->zName);
      testcase( pIdxInfo->needToFreeIdxStr );
      return SQLITE_ERROR;
    }
  }
  assert( pNew->nLTerm<=pNew->nLSlot );
  pNew->u.vtab.idxNum = pIdxInfo->idxNum;
  pNew->u.vtab.needFree = pIdxInfo->needToFreeIdxStr;
  pIdxInfo->needToFreeIdxStr = 0;
  pNew->u.vtab.idxStr = pIdxInfo->idxStr;
  pNew->u.vtab.isOrdered = (i8)(pIdxInfo->orderByConsumed ?
      pIdxInfo->nOrderBy : 0);
  pNew->rSetup = 0;
  pNew->rRun = sqlite3LogEstFromDouble(pIdxInfo->estimatedCost);
  pNew->nOut = sqlite3LogEst(pIdxInfo->estimatedRows);

  /* Set the WHERE_ONEROW flag if the xBestIndex() method indicated
  ** that the scan will visit at most one row. Clear it otherwise. */
  if( pIdxInfo->idxFlags & SQLITE_INDEX_SCAN_UNIQUE ){
    pNew->wsFlags |= WHERE_ONEROW;
  }else{
    pNew->wsFlags &= ~WHERE_ONEROW;
  }
  rc = whereLoopInsert(pBuilder, pNew);
  if( pNew->u.vtab.needFree ){
    sqlite3_free(pNew->u.vtab.idxStr);
    pNew->u.vtab.needFree = 0;
  }
  WHERETRACE(0xffff, ("  bIn=%d prereqIn=%04llx prereqOut=%04llx\n",
                      *pbIn, (sqlite3_uint64)mPrereq,
                      (sqlite3_uint64)(pNew->prereq & ~mPrereq)));

  return rc;
}