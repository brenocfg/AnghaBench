#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_25__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_32__ {TYPE_4__* pList; } ;
struct TYPE_37__ {int iTable; struct TYPE_37__* pLeft; TYPE_1__ x; } ;
struct TYPE_36__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_35__ {TYPE_25__* db; scalar_t__ nErr; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_34__ {TYPE_5__* pExpr; } ;
struct TYPE_33__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ ExprList ;
typedef  TYPE_5__ Expr ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  EP_xIsSelect ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int IN_INDEX_EPH ; 
 int IN_INDEX_INDEX_ASC ; 
 int IN_INDEX_INDEX_DESC ; 
 int IN_INDEX_MEMBERSHIP ; 
 int IN_INDEX_NOOP ; 
 int IN_INDEX_NOOP_OK ; 
 int IN_INDEX_ROWID ; 
 int /*<<< orphan*/  OP_Affinity ; 
 int /*<<< orphan*/  OP_BitAnd ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Eq ; 
 int /*<<< orphan*/  OP_Found ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_Ne ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_NotFound ; 
 int /*<<< orphan*/  OP_NotNull ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_SeekRowid ; 
 int /*<<< orphan*/  P4_COLLSEQ ; 
 char SQLITE_JUMPIFNULL ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VdbeNoopComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int exprCodeVector (TYPE_3__*,TYPE_5__*,int*) ; 
 char* exprINAffinity (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_25__*,...) ; 
 scalar_t__ sqlite3DbMallocZero (TYPE_25__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprCachePop (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ExprCachePush (TYPE_3__*) ; 
 scalar_t__ sqlite3ExprCanBeNull (TYPE_5__*) ; 
 scalar_t__ sqlite3ExprCheckIN (TYPE_3__*,TYPE_5__*) ; 
 int sqlite3ExprCodeTemp (TYPE_3__*,TYPE_5__*,int*) ; 
 int /*<<< orphan*/ * sqlite3ExprCollSeq (TYPE_3__*,TYPE_5__*) ; 
 int sqlite3ExprVectorSize (TYPE_5__*) ; 
 int sqlite3FindInIndex (TYPE_3__*,TYPE_5__*,int,int*,int*) ; 
 int sqlite3GetTempRange (TYPE_3__*,int) ; 
 int sqlite3GetTempReg (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_3__*,int) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,void*,int) ; 
 int sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* sqlite3VectorFieldSubexpr (TYPE_5__*,int) ; 

__attribute__((used)) static void sqlite3ExprCodeIN(
  Parse *pParse,        /* Parsing and code generating context */
  Expr *pExpr,          /* The IN expression */
  int destIfFalse,      /* Jump here if LHS is not contained in the RHS */
  int destIfNull        /* Jump here if the results are unknown due to NULLs */
){
  int rRhsHasNull = 0;  /* Register that is true if RHS contains NULL values */
  int eType;            /* Type of the RHS */
  int rLhs;             /* Register(s) holding the LHS values */
  int rLhsOrig;         /* LHS values prior to reordering by aiMap[] */
  Vdbe *v;              /* Statement under construction */
  int *aiMap = 0;       /* Map from vector field to index column */
  char *zAff = 0;       /* Affinity string for comparisons */
  int nVector;          /* Size of vectors for this IN operator */
  int iDummy;           /* Dummy parameter to exprCodeVector() */
  Expr *pLeft;          /* The LHS of the IN operator */
  int i;                /* loop counter */
  int destStep2;        /* Where to jump when NULLs seen in step 2 */
  int destStep6 = 0;    /* Start of code for Step 6 */
  int addrTruthOp;      /* Address of opcode that determines the IN is true */
  int destNotNull;      /* Jump here if a comparison is not true in step 6 */
  int addrTop;          /* Top of the step-6 loop */ 

  pLeft = pExpr->pLeft;
  if( sqlite3ExprCheckIN(pParse, pExpr) ) return;
  zAff = exprINAffinity(pParse, pExpr);
  nVector = sqlite3ExprVectorSize(pExpr->pLeft);
  aiMap = (int*)sqlite3DbMallocZero(
      pParse->db, nVector*(sizeof(int) + sizeof(char)) + 1
  );
  if( pParse->db->mallocFailed ) goto sqlite3ExprCodeIN_oom_error;

  /* Attempt to compute the RHS. After this step, if anything other than
  ** IN_INDEX_NOOP is returned, the table opened ith cursor pExpr->iTable 
  ** contains the values that make up the RHS. If IN_INDEX_NOOP is returned,
  ** the RHS has not yet been coded.  */
  v = pParse->pVdbe;
  assert( v!=0 );       /* OOM detected prior to this routine */
  VdbeNoopComment((v, "begin IN expr"));
  eType = sqlite3FindInIndex(pParse, pExpr,
                             IN_INDEX_MEMBERSHIP | IN_INDEX_NOOP_OK,
                             destIfFalse==destIfNull ? 0 : &rRhsHasNull, aiMap);

  assert( pParse->nErr || nVector==1 || eType==IN_INDEX_EPH
       || eType==IN_INDEX_INDEX_ASC || eType==IN_INDEX_INDEX_DESC 
  );
#ifdef SQLITE_DEBUG
  /* Confirm that aiMap[] contains nVector integer values between 0 and
  ** nVector-1. */
  for(i=0; i<nVector; i++){
    int j, cnt;
    for(cnt=j=0; j<nVector; j++) if( aiMap[j]==i ) cnt++;
    assert( cnt==1 );
  }
#endif

  /* Code the LHS, the <expr> from "<expr> IN (...)". If the LHS is a 
  ** vector, then it is stored in an array of nVector registers starting 
  ** at r1.
  **
  ** sqlite3FindInIndex() might have reordered the fields of the LHS vector
  ** so that the fields are in the same order as an existing index.   The
  ** aiMap[] array contains a mapping from the original LHS field order to
  ** the field order that matches the RHS index.
  */
  sqlite3ExprCachePush(pParse);
  rLhsOrig = exprCodeVector(pParse, pLeft, &iDummy);
  for(i=0; i<nVector && aiMap[i]==i; i++){} /* Are LHS fields reordered? */
  if( i==nVector ){
    /* LHS fields are not reordered */
    rLhs = rLhsOrig;
  }else{
    /* Need to reorder the LHS fields according to aiMap */
    rLhs = sqlite3GetTempRange(pParse, nVector);
    for(i=0; i<nVector; i++){
      sqlite3VdbeAddOp3(v, OP_Copy, rLhsOrig+i, rLhs+aiMap[i], 0);
    }
  }

  /* If sqlite3FindInIndex() did not find or create an index that is
  ** suitable for evaluating the IN operator, then evaluate using a
  ** sequence of comparisons.
  **
  ** This is step (1) in the in-operator.md optimized algorithm.
  */
  if( eType==IN_INDEX_NOOP ){
    ExprList *pList = pExpr->x.pList;
    CollSeq *pColl = sqlite3ExprCollSeq(pParse, pExpr->pLeft);
    int labelOk = sqlite3VdbeMakeLabel(v);
    int r2, regToFree;
    int regCkNull = 0;
    int ii;
    assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
    if( destIfNull!=destIfFalse ){
      regCkNull = sqlite3GetTempReg(pParse);
      sqlite3VdbeAddOp3(v, OP_BitAnd, rLhs, rLhs, regCkNull);
    }
    for(ii=0; ii<pList->nExpr; ii++){
      r2 = sqlite3ExprCodeTemp(pParse, pList->a[ii].pExpr, &regToFree);
      if( regCkNull && sqlite3ExprCanBeNull(pList->a[ii].pExpr) ){
        sqlite3VdbeAddOp3(v, OP_BitAnd, regCkNull, r2, regCkNull);
      }
      if( ii<pList->nExpr-1 || destIfNull!=destIfFalse ){
        sqlite3VdbeAddOp4(v, OP_Eq, rLhs, labelOk, r2,
                          (void*)pColl, P4_COLLSEQ);
        VdbeCoverageIf(v, ii<pList->nExpr-1);
        VdbeCoverageIf(v, ii==pList->nExpr-1);
        sqlite3VdbeChangeP5(v, zAff[0]);
      }else{
        assert( destIfNull==destIfFalse );
        sqlite3VdbeAddOp4(v, OP_Ne, rLhs, destIfFalse, r2,
                          (void*)pColl, P4_COLLSEQ); VdbeCoverage(v);
        sqlite3VdbeChangeP5(v, zAff[0] | SQLITE_JUMPIFNULL);
      }
      sqlite3ReleaseTempReg(pParse, regToFree);
    }
    if( regCkNull ){
      sqlite3VdbeAddOp2(v, OP_IsNull, regCkNull, destIfNull); VdbeCoverage(v);
      sqlite3VdbeGoto(v, destIfFalse);
    }
    sqlite3VdbeResolveLabel(v, labelOk);
    sqlite3ReleaseTempReg(pParse, regCkNull);
    goto sqlite3ExprCodeIN_finished;
  }

  /* Step 2: Check to see if the LHS contains any NULL columns.  If the
  ** LHS does contain NULLs then the result must be either FALSE or NULL.
  ** We will then skip the binary search of the RHS.
  */
  if( destIfNull==destIfFalse ){
    destStep2 = destIfFalse;
  }else{
    destStep2 = destStep6 = sqlite3VdbeMakeLabel(v);
  }
  for(i=0; i<nVector; i++){
    Expr *p = sqlite3VectorFieldSubexpr(pExpr->pLeft, i);
    if( sqlite3ExprCanBeNull(p) ){
      sqlite3VdbeAddOp2(v, OP_IsNull, rLhs+i, destStep2);
      VdbeCoverage(v);
    }
  }

  /* Step 3.  The LHS is now known to be non-NULL.  Do the binary search
  ** of the RHS using the LHS as a probe.  If found, the result is
  ** true.
  */
  if( eType==IN_INDEX_ROWID ){
    /* In this case, the RHS is the ROWID of table b-tree and so we also
    ** know that the RHS is non-NULL.  Hence, we combine steps 3 and 4
    ** into a single opcode. */
    sqlite3VdbeAddOp3(v, OP_SeekRowid, pExpr->iTable, destIfFalse, rLhs);
    VdbeCoverage(v);
    addrTruthOp = sqlite3VdbeAddOp0(v, OP_Goto);  /* Return True */
  }else{
    sqlite3VdbeAddOp4(v, OP_Affinity, rLhs, nVector, 0, zAff, nVector);
    if( destIfFalse==destIfNull ){
      /* Combine Step 3 and Step 5 into a single opcode */
      sqlite3VdbeAddOp4Int(v, OP_NotFound, pExpr->iTable, destIfFalse,
                           rLhs, nVector); VdbeCoverage(v);
      goto sqlite3ExprCodeIN_finished;
    }
    /* Ordinary Step 3, for the case where FALSE and NULL are distinct */
    addrTruthOp = sqlite3VdbeAddOp4Int(v, OP_Found, pExpr->iTable, 0,
                                      rLhs, nVector); VdbeCoverage(v);
  }

  /* Step 4.  If the RHS is known to be non-NULL and we did not find
  ** an match on the search above, then the result must be FALSE.
  */
  if( rRhsHasNull && nVector==1 ){
    sqlite3VdbeAddOp2(v, OP_NotNull, rRhsHasNull, destIfFalse);
    VdbeCoverage(v);
  }

  /* Step 5.  If we do not care about the difference between NULL and
  ** FALSE, then just return false. 
  */
  if( destIfFalse==destIfNull ) sqlite3VdbeGoto(v, destIfFalse);

  /* Step 6: Loop through rows of the RHS.  Compare each row to the LHS.
  ** If any comparison is NULL, then the result is NULL.  If all
  ** comparisons are FALSE then the final result is FALSE.
  **
  ** For a scalar LHS, it is sufficient to check just the first row
  ** of the RHS.
  */
  if( destStep6 ) sqlite3VdbeResolveLabel(v, destStep6);
  addrTop = sqlite3VdbeAddOp2(v, OP_Rewind, pExpr->iTable, destIfFalse);
  VdbeCoverage(v);
  if( nVector>1 ){
    destNotNull = sqlite3VdbeMakeLabel(v);
  }else{
    /* For nVector==1, combine steps 6 and 7 by immediately returning
    ** FALSE if the first comparison is not NULL */
    destNotNull = destIfFalse;
  }
  for(i=0; i<nVector; i++){
    Expr *p;
    CollSeq *pColl;
    int r3 = sqlite3GetTempReg(pParse);
    p = sqlite3VectorFieldSubexpr(pLeft, i);
    pColl = sqlite3ExprCollSeq(pParse, p);
    sqlite3VdbeAddOp3(v, OP_Column, pExpr->iTable, i, r3);
    sqlite3VdbeAddOp4(v, OP_Ne, rLhs+i, destNotNull, r3,
                      (void*)pColl, P4_COLLSEQ);
    VdbeCoverage(v);
    sqlite3ReleaseTempReg(pParse, r3);
  }
  sqlite3VdbeAddOp2(v, OP_Goto, 0, destIfNull);
  if( nVector>1 ){
    sqlite3VdbeResolveLabel(v, destNotNull);
    sqlite3VdbeAddOp2(v, OP_Next, pExpr->iTable, addrTop+1);
    VdbeCoverage(v);

    /* Step 7:  If we reach this point, we know that the result must
    ** be false. */
    sqlite3VdbeAddOp2(v, OP_Goto, 0, destIfFalse);
  }

  /* Jumps here in order to return true. */
  sqlite3VdbeJumpHere(v, addrTruthOp);

sqlite3ExprCodeIN_finished:
  if( rLhs!=rLhsOrig ) sqlite3ReleaseTempReg(pParse, rLhs);
  sqlite3ExprCachePop(pParse);
  VdbeComment((v, "end IN expr"));
sqlite3ExprCodeIN_oom_error:
  sqlite3DbFree(pParse->db, aiMap);
  sqlite3DbFree(pParse->db, zAff);
}