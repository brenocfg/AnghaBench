#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_7__* pKeyInfo; } ;
struct TYPE_21__ {int p2; TYPE_2__ p4; } ;
typedef  TYPE_3__ VdbeOp ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_25__ {scalar_t__ nKeyField; scalar_t__ nAllField; int /*<<< orphan*/  aSortOrder; } ;
struct TYPE_24__ {int nMem; TYPE_1__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_23__ {scalar_t__ iOffset; int iLimit; } ;
struct TYPE_22__ {int sortFlags; int nOBSat; int labelDone; int iECursor; int labelBkOut; int regReturn; scalar_t__ bOrderedInnerLoop; TYPE_11__* pOrderBy; int /*<<< orphan*/  addrSortIndex; } ;
struct TYPE_19__ {scalar_t__ mallocFailed; } ;
struct TYPE_18__ {int nExpr; } ;
typedef  TYPE_4__ SortCtx ;
typedef  TYPE_5__ Select ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ KeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Delete ; 
 int /*<<< orphan*/  OP_Eq ; 
 int /*<<< orphan*/  OP_Gosub ; 
 int OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_IfNotZero ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  OP_Last ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_ResetSorter ; 
 int /*<<< orphan*/  OP_Sequence ; 
 int /*<<< orphan*/  OP_SequenceTest ; 
 int OP_SorterInsert ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 int SORTFLAG_UseSorter ; 
 int SQLITE_ECEL_DUP ; 
 int SQLITE_ECEL_REF ; 
 int /*<<< orphan*/  SQLITE_NULLEQ ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* keyInfoFromExprList (TYPE_6__*,TYPE_11__*,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3ExprCodeExprList (TYPE_6__*,TYPE_11__*,int,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeMove (TYPE_6__*,int,int,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP4 (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 TYPE_3__* sqlite3VdbeGetOp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 void* sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void pushOntoSorter(
  Parse *pParse,         /* Parser context */
  SortCtx *pSort,        /* Information about the ORDER BY clause */
  Select *pSelect,       /* The whole SELECT statement */
  int regData,           /* First register holding data to be sorted */
  int regOrigData,       /* First register holding data before packing */
  int nData,             /* Number of elements in the data array */
  int nPrefixReg         /* No. of reg prior to regData available for use */
){
  Vdbe *v = pParse->pVdbe;                         /* Stmt under construction */
  int bSeq = ((pSort->sortFlags & SORTFLAG_UseSorter)==0);
  int nExpr = pSort->pOrderBy->nExpr;              /* No. of ORDER BY terms */
  int nBase = nExpr + bSeq + nData;                /* Fields in sorter record */
  int regBase;                                     /* Regs for sorter record */
  int regRecord = ++pParse->nMem;                  /* Assembled sorter record */
  int nOBSat = pSort->nOBSat;                      /* ORDER BY terms to skip */
  int op;                            /* Opcode to add sorter record to sorter */
  int iLimit;                        /* LIMIT counter */

  assert( bSeq==0 || bSeq==1 );
  assert( nData==1 || regData==regOrigData || regOrigData==0 );
  if( nPrefixReg ){
    assert( nPrefixReg==nExpr+bSeq );
    regBase = regData - nExpr - bSeq;
  }else{
    regBase = pParse->nMem + 1;
    pParse->nMem += nBase;
  }
  assert( pSelect->iOffset==0 || pSelect->iLimit!=0 );
  iLimit = pSelect->iOffset ? pSelect->iOffset+1 : pSelect->iLimit;
  pSort->labelDone = sqlite3VdbeMakeLabel(v);
  sqlite3ExprCodeExprList(pParse, pSort->pOrderBy, regBase, regOrigData,
                          SQLITE_ECEL_DUP | (regOrigData? SQLITE_ECEL_REF : 0));
  if( bSeq ){
    sqlite3VdbeAddOp2(v, OP_Sequence, pSort->iECursor, regBase+nExpr);
  }
  if( nPrefixReg==0 && nData>0 ){
    sqlite3ExprCodeMove(pParse, regData, regBase+nExpr+bSeq, nData);
  }
  sqlite3VdbeAddOp3(v, OP_MakeRecord, regBase+nOBSat, nBase-nOBSat, regRecord);
  if( nOBSat>0 ){
    int regPrevKey;   /* The first nOBSat columns of the previous row */
    int addrFirst;    /* Address of the OP_IfNot opcode */
    int addrJmp;      /* Address of the OP_Jump opcode */
    VdbeOp *pOp;      /* Opcode that opens the sorter */
    int nKey;         /* Number of sorting key columns, including OP_Sequence */
    KeyInfo *pKI;     /* Original KeyInfo on the sorter table */

    regPrevKey = pParse->nMem+1;
    pParse->nMem += pSort->nOBSat;
    nKey = nExpr - pSort->nOBSat + bSeq;
    if( bSeq ){
      addrFirst = sqlite3VdbeAddOp1(v, OP_IfNot, regBase+nExpr); 
    }else{
      addrFirst = sqlite3VdbeAddOp1(v, OP_SequenceTest, pSort->iECursor);
    }
    VdbeCoverage(v);
    sqlite3VdbeAddOp3(v, OP_Compare, regPrevKey, regBase, pSort->nOBSat);
    pOp = sqlite3VdbeGetOp(v, pSort->addrSortIndex);
    if( pParse->db->mallocFailed ) return;
    pOp->p2 = nKey + nData;
    pKI = pOp->p4.pKeyInfo;
    memset(pKI->aSortOrder, 0, pKI->nKeyField); /* Makes OP_Jump testable */
    sqlite3VdbeChangeP4(v, -1, (char*)pKI, P4_KEYINFO);
    testcase( pKI->nAllField > pKI->nKeyField+2 );
    pOp->p4.pKeyInfo = keyInfoFromExprList(pParse, pSort->pOrderBy, nOBSat,
                                           pKI->nAllField-pKI->nKeyField-1);
    addrJmp = sqlite3VdbeCurrentAddr(v);
    sqlite3VdbeAddOp3(v, OP_Jump, addrJmp+1, 0, addrJmp+1); VdbeCoverage(v);
    pSort->labelBkOut = sqlite3VdbeMakeLabel(v);
    pSort->regReturn = ++pParse->nMem;
    sqlite3VdbeAddOp2(v, OP_Gosub, pSort->regReturn, pSort->labelBkOut);
    sqlite3VdbeAddOp1(v, OP_ResetSorter, pSort->iECursor);
    if( iLimit ){
      sqlite3VdbeAddOp2(v, OP_IfNot, iLimit, pSort->labelDone);
      VdbeCoverage(v);
    }
    sqlite3VdbeJumpHere(v, addrFirst);
    sqlite3ExprCodeMove(pParse, regBase, regPrevKey, pSort->nOBSat);
    sqlite3VdbeJumpHere(v, addrJmp);
  }
  if( pSort->sortFlags & SORTFLAG_UseSorter ){
    op = OP_SorterInsert;
  }else{
    op = OP_IdxInsert;
  }
  sqlite3VdbeAddOp4Int(v, op, pSort->iECursor, regRecord,
                       regBase+nOBSat, nBase-nOBSat);
  if( iLimit ){
    int addr;
    int r1 = 0;
    /* Fill the sorter until it contains LIMIT+OFFSET entries.  (The iLimit
    ** register is initialized with value of LIMIT+OFFSET.)  After the sorter
    ** fills up, delete the least entry in the sorter after each insert.
    ** Thus we never hold more than the LIMIT+OFFSET rows in memory at once */
    addr = sqlite3VdbeAddOp1(v, OP_IfNotZero, iLimit); VdbeCoverage(v);
    sqlite3VdbeAddOp1(v, OP_Last, pSort->iECursor);
    if( pSort->bOrderedInnerLoop ){
      r1 = ++pParse->nMem;
      sqlite3VdbeAddOp3(v, OP_Column, pSort->iECursor, nExpr, r1);
      VdbeComment((v, "seq"));
    }
    sqlite3VdbeAddOp1(v, OP_Delete, pSort->iECursor);
    if( pSort->bOrderedInnerLoop ){
      /* If the inner loop is driven by an index such that values from
      ** the same iteration of the inner loop are in sorted order, then
      ** immediately jump to the next iteration of an inner loop if the
      ** entry from the current iteration does not fit into the top
      ** LIMIT+OFFSET entries of the sorter. */
      int iBrk = sqlite3VdbeCurrentAddr(v) + 2;
      sqlite3VdbeAddOp3(v, OP_Eq, regBase+nExpr, iBrk, r1);
      sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);
      VdbeCoverage(v);
    }
    sqlite3VdbeJumpHere(v, addr);
  }
}