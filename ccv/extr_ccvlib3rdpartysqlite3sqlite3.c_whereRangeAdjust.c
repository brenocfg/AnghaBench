#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ truthProb; int wtFlags; } ;
typedef  TYPE_1__ WhereTerm ;
typedef  int LogEst ;

/* Variables and functions */
 int TERM_VNULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3LogEst (int) ; 

__attribute__((used)) static LogEst whereRangeAdjust(WhereTerm *pTerm, LogEst nNew){
  LogEst nRet = nNew;
  if( pTerm ){
    if( pTerm->truthProb<=0 ){
      nRet += pTerm->truthProb;
    }else if( (pTerm->wtFlags & TERM_VNULL)==0 ){
      nRet -= 20;        assert( 20==sqlite3LogEst(4) );
    }
  }
  return nRet;
}