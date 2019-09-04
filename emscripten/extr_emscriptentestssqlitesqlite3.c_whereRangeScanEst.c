#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wtFlags; } ;
typedef  TYPE_1__ WhereTerm ;
typedef  int /*<<< orphan*/  Parse ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int SQLITE_OK ; 
 int TERM_VNULL ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int whereRangeScanEst(
  Parse *pParse,       /* Parsing & code generating context */
  Index *p,            /* The index containing the range-compared column; "x" */
  int nEq,             /* index into p->aCol[] of the range-compared column */
  WhereTerm *pLower,   /* Lower bound on the range. ex: "x>123" Might be NULL */
  WhereTerm *pUpper,   /* Upper bound on the range. ex: "x<455" Might be NULL */
  int *piEst           /* OUT: Return value */
){
  int rc = SQLITE_OK;

#ifdef SQLITE_ENABLE_STAT2

  if( nEq==0 && p->aSample ){
    sqlite3_value *pLowerVal = 0;
    sqlite3_value *pUpperVal = 0;
    int iEst;
    int iLower = 0;
    int iUpper = SQLITE_INDEX_SAMPLES;
    int roundUpUpper = 0;
    int roundUpLower = 0;
    u8 aff = p->pTable->aCol[p->aiColumn[0]].affinity;

    if( pLower ){
      Expr *pExpr = pLower->pExpr->pRight;
      rc = valueFromExpr(pParse, pExpr, aff, &pLowerVal);
      assert( pLower->eOperator==WO_GT || pLower->eOperator==WO_GE );
      roundUpLower = (pLower->eOperator==WO_GT) ?1:0;
    }
    if( rc==SQLITE_OK && pUpper ){
      Expr *pExpr = pUpper->pExpr->pRight;
      rc = valueFromExpr(pParse, pExpr, aff, &pUpperVal);
      assert( pUpper->eOperator==WO_LT || pUpper->eOperator==WO_LE );
      roundUpUpper = (pUpper->eOperator==WO_LE) ?1:0;
    }

    if( rc!=SQLITE_OK || (pLowerVal==0 && pUpperVal==0) ){
      sqlite3ValueFree(pLowerVal);
      sqlite3ValueFree(pUpperVal);
      goto range_est_fallback;
    }else if( pLowerVal==0 ){
      rc = whereRangeRegion(pParse, p, pUpperVal, roundUpUpper, &iUpper);
      if( pLower ) iLower = iUpper/2;
    }else if( pUpperVal==0 ){
      rc = whereRangeRegion(pParse, p, pLowerVal, roundUpLower, &iLower);
      if( pUpper ) iUpper = (iLower + SQLITE_INDEX_SAMPLES + 1)/2;
    }else{
      rc = whereRangeRegion(pParse, p, pUpperVal, roundUpUpper, &iUpper);
      if( rc==SQLITE_OK ){
        rc = whereRangeRegion(pParse, p, pLowerVal, roundUpLower, &iLower);
      }
    }
    WHERETRACE(("range scan regions: %d..%d\n", iLower, iUpper));

    iEst = iUpper - iLower;
    testcase( iEst==SQLITE_INDEX_SAMPLES );
    assert( iEst<=SQLITE_INDEX_SAMPLES );
    if( iEst<1 ){
      *piEst = 50/SQLITE_INDEX_SAMPLES;
    }else{
      *piEst = (iEst*100)/SQLITE_INDEX_SAMPLES;
    }
    sqlite3ValueFree(pLowerVal);
    sqlite3ValueFree(pUpperVal);
    return rc;
  }
range_est_fallback:
#else
  UNUSED_PARAMETER(pParse);
  UNUSED_PARAMETER(p);
  UNUSED_PARAMETER(nEq);
#endif
  assert( pLower || pUpper );
  *piEst = 100;
  if( pLower && (pLower->wtFlags & TERM_VNULL)==0 ) *piEst /= 4;
  if( pUpper ) *piEst /= 4;
  return rc;
}