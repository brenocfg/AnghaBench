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
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int wtFlags; int eOperator; TYPE_3__* pExpr; } ;
typedef  TYPE_4__ WhereTerm ;
struct TYPE_19__ {TYPE_7__* pIdx; } ;
struct TYPE_20__ {int nEq; int wsFlags; TYPE_1__ u; } ;
struct TYPE_23__ {int iTabCur; int /*<<< orphan*/  addrBrk; TYPE_2__ plan; } ;
typedef  TYPE_5__ WhereLevel ;
typedef  int /*<<< orphan*/  WhereClause ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_25__ {int nColumn; int* aiColumn; } ;
struct TYPE_24__ {int nMem; TYPE_10__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_21__ {int /*<<< orphan*/ * pRight; } ;
struct TYPE_18__ {int mallocFailed; } ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ Index ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SCopy ; 
 char SQLITE_AFF_NONE ; 
 int TERM_CODED ; 
 int TERM_VIRTUAL ; 
 int WHERE_INDEXED ; 
 int WO_IN ; 
 int WO_ISNULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int codeEqualityTerm (TYPE_6__*,TYPE_4__*,TYPE_5__*,int,int) ; 
 TYPE_4__* findTerm (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,TYPE_7__*) ; 
 char sqlite3CompareAffinity (int /*<<< orphan*/ *,char) ; 
 char* sqlite3DbStrDup (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprCodeIsNullJump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3ExprNeedsNoAffinityChange (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  sqlite3IndexAffinityStr (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int codeAllEqualityTerms(
  Parse *pParse,        /* Parsing context */
  WhereLevel *pLevel,   /* Which nested loop of the FROM we are coding */
  WhereClause *pWC,     /* The WHERE clause */
  Bitmask notReady,     /* Which parts of FROM have not yet been coded */
  int nExtraReg,        /* Number of extra registers to allocate */
  char **pzAff          /* OUT: Set to point to affinity string */
){
  int nEq = pLevel->plan.nEq;   /* The number of == or IN constraints to code */
  Vdbe *v = pParse->pVdbe;      /* The vm under construction */
  Index *pIdx;                  /* The index being used for this loop */
  int iCur = pLevel->iTabCur;   /* The cursor of the table */
  WhereTerm *pTerm;             /* A single constraint term */
  int j;                        /* Loop counter */
  int regBase;                  /* Base register */
  int nReg;                     /* Number of registers to allocate */
  char *zAff;                   /* Affinity string to return */

  /* This module is only called on query plans that use an index. */
  assert( pLevel->plan.wsFlags & WHERE_INDEXED );
  pIdx = pLevel->plan.u.pIdx;

  /* Figure out how many memory cells we will need then allocate them.
  */
  regBase = pParse->nMem + 1;
  nReg = pLevel->plan.nEq + nExtraReg;
  pParse->nMem += nReg;

  zAff = sqlite3DbStrDup(pParse->db, sqlite3IndexAffinityStr(v, pIdx));
  if( !zAff ){
    pParse->db->mallocFailed = 1;
  }

  /* Evaluate the equality constraints
  */
  assert( pIdx->nColumn>=nEq );
  for(j=0; j<nEq; j++){
    int r1;
    int k = pIdx->aiColumn[j];
    pTerm = findTerm(pWC, iCur, k, notReady, pLevel->plan.wsFlags, pIdx);
    if( pTerm==0 ) break;
    /* The following true for indices with redundant columns. 
    ** Ex: CREATE INDEX i1 ON t1(a,b,a); SELECT * FROM t1 WHERE a=0 AND b=0; */
    testcase( (pTerm->wtFlags & TERM_CODED)!=0 );
    testcase( pTerm->wtFlags & TERM_VIRTUAL ); /* EV: R-30575-11662 */
    r1 = codeEqualityTerm(pParse, pTerm, pLevel, j, regBase+j);
    if( r1!=regBase+j ){
      if( nReg==1 ){
        sqlite3ReleaseTempReg(pParse, regBase);
        regBase = r1;
      }else{
        sqlite3VdbeAddOp2(v, OP_SCopy, r1, regBase+j);
      }
    }
    testcase( pTerm->eOperator & WO_ISNULL );
    testcase( pTerm->eOperator & WO_IN );
    if( (pTerm->eOperator & (WO_ISNULL|WO_IN))==0 ){
      Expr *pRight = pTerm->pExpr->pRight;
      sqlite3ExprCodeIsNullJump(v, pRight, regBase+j, pLevel->addrBrk);
      if( zAff ){
        if( sqlite3CompareAffinity(pRight, zAff[j])==SQLITE_AFF_NONE ){
          zAff[j] = SQLITE_AFF_NONE;
        }
        if( sqlite3ExprNeedsNoAffinityChange(pRight, zAff[j]) ){
          zAff[j] = SQLITE_AFF_NONE;
        }
      }
    }
  }
  *pzAff = zAff;
  return regBase;
}