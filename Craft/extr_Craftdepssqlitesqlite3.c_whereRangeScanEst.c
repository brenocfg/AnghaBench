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
  double *pRangeDiv   /* OUT: Reduce search space by this divisor */
){
  int rc = SQLITE_OK;

#ifdef SQLITE_ENABLE_STAT3

  if( nEq==0 && p->nSample ){
    sqlite3_value *pRangeVal;
    tRowcnt iLower = 0;
    tRowcnt iUpper = p->aiRowEst[0];
    tRowcnt a[2];
    u8 aff = p->pTable->aCol[p->aiColumn[0]].affinity;

    if( pLower ){
      Expr *pExpr = pLower->pExpr->pRight;
      rc = valueFromExpr(pParse, pExpr, aff, &pRangeVal);
      assert( (pLower->eOperator & (WO_GT|WO_GE))!=0 );
      if( rc==SQLITE_OK
       && whereKeyStats(pParse, p, pRangeVal, 0, a)==SQLITE_OK
      ){
        iLower = a[0];
        if( (pLower->eOperator & WO_GT)!=0 ) iLower += a[1];
      }
      sqlite3ValueFree(pRangeVal);
    }
    if( rc==SQLITE_OK && pUpper ){
      Expr *pExpr = pUpper->pExpr->pRight;
      rc = valueFromExpr(pParse, pExpr, aff, &pRangeVal);
      assert( (pUpper->eOperator & (WO_LT|WO_LE))!=0 );
      if( rc==SQLITE_OK
       && whereKeyStats(pParse, p, pRangeVal, 1, a)==SQLITE_OK
      ){
        iUpper = a[0];
        if( (pUpper->eOperator & WO_LE)!=0 ) iUpper += a[1];
      }
      sqlite3ValueFree(pRangeVal);
    }
    if( rc==SQLITE_OK ){
      if( iUpper<=iLower ){
        *pRangeDiv = (double)p->aiRowEst[0];
      }else{
        *pRangeDiv = (double)p->aiRowEst[0]/(double)(iUpper - iLower);
      }
      WHERETRACE(("range scan regions: %u..%u  div=%g\n",
                  (u32)iLower, (u32)iUpper, *pRangeDiv));
      return SQLITE_OK;
    }
  }
#else
  UNUSED_PARAMETER(pParse);
  UNUSED_PARAMETER(p);
  UNUSED_PARAMETER(nEq);
#endif
  assert( pLower || pUpper );
  *pRangeDiv = (double)1;
  if( pLower && (pLower->wtFlags & TERM_VNULL)==0 ) *pRangeDiv *= (double)4;
  if( pUpper ) *pRangeDiv *= (double)4;
  return rc;
}