#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_16__ {int leftColumn; } ;
struct TYPE_19__ {int leftCursor; int prereqRight; int eOperator; TYPE_8__* pExpr; TYPE_1__ u; } ;
typedef  TYPE_4__ WhereTerm ;
struct TYPE_20__ {int nTerm; TYPE_6__* pParse; TYPE_4__* a; } ;
typedef  TYPE_5__ WhereClause ;
struct TYPE_24__ {int /*<<< orphan*/  zName; } ;
struct TYPE_23__ {int pLeft; int /*<<< orphan*/  pRight; } ;
struct TYPE_22__ {int* aiColumn; int nColumn; int /*<<< orphan*/ * azColl; TYPE_3__* pTable; } ;
struct TYPE_21__ {scalar_t__ nErr; } ;
struct TYPE_18__ {TYPE_2__* aCol; } ;
struct TYPE_17__ {char affinity; } ;
typedef  TYPE_6__ Parse ;
typedef  TYPE_7__ Index ;
typedef  TYPE_8__ Expr ;
typedef  TYPE_9__ CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int WO_ALL ; 
 int WO_ISNULL ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_9__* sqlite3BinaryCompareCollSeq (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IndexAffinityOk (TYPE_8__*,char) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static WhereTerm *findTerm(
  WhereClause *pWC,     /* The WHERE clause to be searched */
  int iCur,             /* Cursor number of LHS */
  int iColumn,          /* Column number of LHS */
  Bitmask notReady,     /* RHS must not overlap with this mask */
  u32 op,               /* Mask of WO_xx values describing operator */
  Index *pIdx           /* Must be compatible with this index, if not NULL */
){
  WhereTerm *pTerm;
  int k;
  assert( iCur>=0 );
  op &= WO_ALL;
  for(pTerm=pWC->a, k=pWC->nTerm; k; k--, pTerm++){
    if( pTerm->leftCursor==iCur
       && (pTerm->prereqRight & notReady)==0
       && pTerm->u.leftColumn==iColumn
       && (pTerm->eOperator & op)!=0
    ){
      if( pIdx && pTerm->eOperator!=WO_ISNULL ){
        Expr *pX = pTerm->pExpr;
        CollSeq *pColl;
        char idxaff;
        int j;
        Parse *pParse = pWC->pParse;

        idxaff = pIdx->pTable->aCol[iColumn].affinity;
        if( !sqlite3IndexAffinityOk(pX, idxaff) ) continue;

        /* Figure out the collation sequence required from an index for
        ** it to be useful for optimising expression pX. Store this
        ** value in variable pColl.
        */
        assert(pX->pLeft);
        pColl = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pX->pRight);
        assert(pColl || pParse->nErr);

        for(j=0; pIdx->aiColumn[j]!=iColumn; j++){
          if( NEVER(j>=pIdx->nColumn) ) return 0;
        }
        if( pColl && sqlite3StrICmp(pColl->zName, pIdx->azColl[j]) ) continue;
      }
      return pTerm;
    }
  }
  return 0;
}