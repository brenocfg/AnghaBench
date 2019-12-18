#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_22__ {TYPE_1__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_21__ {int iLimit; TYPE_3__* pEList; } ;
struct TYPE_20__ {int iSdst; int nSdst; int eDest; int iSDParm; char affSdst; } ;
struct TYPE_19__ {TYPE_2__* a; } ;
struct TYPE_18__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_17__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_4__ SelectDest ;
typedef  TYPE_5__ Select ;
typedef  TYPE_6__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  OPFLAG_APPEND ; 
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_IfZero ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_ResultRow ; 
 int /*<<< orphan*/  OP_Return ; 
 int /*<<< orphan*/  OP_Yield ; 
#define  SRT_Coroutine 133 
#define  SRT_EphemTab 132 
#define  SRT_Exists 131 
#define  SRT_Mem 130 
 int const SRT_Output ; 
#define  SRT_Set 129 
#define  SRT_Table 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeOffset (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 char sqlite3CompareAffinity (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  sqlite3ExprCacheAffinityChange (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeMove (TYPE_6__*,int,int,int) ; 
 int sqlite3GetTempRange (TYPE_6__*,int) ; 
 int sqlite3GetTempReg (TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_6__*,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int generateOutputSubroutine(
  Parse *pParse,          /* Parsing context */
  Select *p,              /* The SELECT statement */
  SelectDest *pIn,        /* Coroutine supplying data */
  SelectDest *pDest,      /* Where to send the data */
  int regReturn,          /* The return address register */
  int regPrev,            /* Previous result register.  No uniqueness if 0 */
  KeyInfo *pKeyInfo,      /* For comparing with previous entry */
  int p4type,             /* The p4 type for pKeyInfo */
  int iBreak              /* Jump here if we hit the LIMIT */
){
  Vdbe *v = pParse->pVdbe;
  int iContinue;
  int addr;

  addr = sqlite3VdbeCurrentAddr(v);
  iContinue = sqlite3VdbeMakeLabel(v);

  /* Suppress duplicates for UNION, EXCEPT, and INTERSECT 
  */
  if( regPrev ){
    int j1, j2;
    j1 = sqlite3VdbeAddOp1(v, OP_IfNot, regPrev);
    j2 = sqlite3VdbeAddOp4(v, OP_Compare, pIn->iSdst, regPrev+1, pIn->nSdst,
                              (char*)pKeyInfo, p4type);
    sqlite3VdbeAddOp3(v, OP_Jump, j2+2, iContinue, j2+2);
    sqlite3VdbeJumpHere(v, j1);
    sqlite3VdbeAddOp3(v, OP_Copy, pIn->iSdst, regPrev+1, pIn->nSdst-1);
    sqlite3VdbeAddOp2(v, OP_Integer, 1, regPrev);
  }
  if( pParse->db->mallocFailed ) return 0;

  /* Suppress the first OFFSET entries if there is an OFFSET clause
  */
  codeOffset(v, p, iContinue);

  switch( pDest->eDest ){
    /* Store the result as data using a unique key.
    */
    case SRT_Table:
    case SRT_EphemTab: {
      int r1 = sqlite3GetTempReg(pParse);
      int r2 = sqlite3GetTempReg(pParse);
      testcase( pDest->eDest==SRT_Table );
      testcase( pDest->eDest==SRT_EphemTab );
      sqlite3VdbeAddOp3(v, OP_MakeRecord, pIn->iSdst, pIn->nSdst, r1);
      sqlite3VdbeAddOp2(v, OP_NewRowid, pDest->iSDParm, r2);
      sqlite3VdbeAddOp3(v, OP_Insert, pDest->iSDParm, r1, r2);
      sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
      sqlite3ReleaseTempReg(pParse, r2);
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }

#ifndef SQLITE_OMIT_SUBQUERY
    /* If we are creating a set for an "expr IN (SELECT ...)" construct,
    ** then there should be a single item on the stack.  Write this
    ** item into the set table with bogus data.
    */
    case SRT_Set: {
      int r1;
      assert( pIn->nSdst==1 );
      pDest->affSdst = 
         sqlite3CompareAffinity(p->pEList->a[0].pExpr, pDest->affSdst);
      r1 = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp4(v, OP_MakeRecord, pIn->iSdst, 1, r1, &pDest->affSdst,1);
      sqlite3ExprCacheAffinityChange(pParse, pIn->iSdst, 1);
      sqlite3VdbeAddOp2(v, OP_IdxInsert, pDest->iSDParm, r1);
      sqlite3ReleaseTempReg(pParse, r1);
      break;
    }

#if 0  /* Never occurs on an ORDER BY query */
    /* If any row exist in the result set, record that fact and abort.
    */
    case SRT_Exists: {
      sqlite3VdbeAddOp2(v, OP_Integer, 1, pDest->iSDParm);
      /* The LIMIT clause will terminate the loop for us */
      break;
    }
#endif

    /* If this is a scalar select that is part of an expression, then
    ** store the results in the appropriate memory cell and break out
    ** of the scan loop.
    */
    case SRT_Mem: {
      assert( pIn->nSdst==1 );
      sqlite3ExprCodeMove(pParse, pIn->iSdst, pDest->iSDParm, 1);
      /* The LIMIT clause will jump out of the loop for us */
      break;
    }
#endif /* #ifndef SQLITE_OMIT_SUBQUERY */

    /* The results are stored in a sequence of registers
    ** starting at pDest->iSdst.  Then the co-routine yields.
    */
    case SRT_Coroutine: {
      if( pDest->iSdst==0 ){
        pDest->iSdst = sqlite3GetTempRange(pParse, pIn->nSdst);
        pDest->nSdst = pIn->nSdst;
      }
      sqlite3ExprCodeMove(pParse, pIn->iSdst, pDest->iSdst, pDest->nSdst);
      sqlite3VdbeAddOp1(v, OP_Yield, pDest->iSDParm);
      break;
    }

    /* If none of the above, then the result destination must be
    ** SRT_Output.  This routine is never called with any other
    ** destination other than the ones handled above or SRT_Output.
    **
    ** For SRT_Output, results are stored in a sequence of registers.  
    ** Then the OP_ResultRow opcode is used to cause sqlite3_step() to
    ** return the next row of result.
    */
    default: {
      assert( pDest->eDest==SRT_Output );
      sqlite3VdbeAddOp2(v, OP_ResultRow, pIn->iSdst, pIn->nSdst);
      sqlite3ExprCacheAffinityChange(pParse, pIn->iSdst, pIn->nSdst);
      break;
    }
  }

  /* Jump to the end of the loop if the LIMIT is reached.
  */
  if( p->iLimit ){
    sqlite3VdbeAddOp3(v, OP_IfZero, p->iLimit, iBreak, -1);
  }

  /* Generate the subroutine return
  */
  sqlite3VdbeResolveLabel(v, iContinue);
  sqlite3VdbeAddOp1(v, OP_Return, regReturn);

  return addr;
}