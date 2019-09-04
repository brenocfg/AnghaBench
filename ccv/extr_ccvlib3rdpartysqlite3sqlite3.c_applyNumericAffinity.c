#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_5__ {double r; int /*<<< orphan*/  i; } ;
struct TYPE_6__ {int flags; TYPE_1__ u; int /*<<< orphan*/  n; int /*<<< orphan*/  z; int /*<<< orphan*/  enc; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Int ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AtoF (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3Atoi64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeIntegerAffinity (TYPE_2__*) ; 

__attribute__((used)) static void applyNumericAffinity(Mem *pRec, int bTryForInt){
  double rValue;
  i64 iValue;
  u8 enc = pRec->enc;
  assert( (pRec->flags & (MEM_Str|MEM_Int|MEM_Real))==MEM_Str );
  if( sqlite3AtoF(pRec->z, &rValue, pRec->n, enc)==0 ) return;
  if( 0==sqlite3Atoi64(pRec->z, &iValue, pRec->n, enc) ){
    pRec->u.i = iValue;
    pRec->flags |= MEM_Int;
  }else{
    pRec->u.r = rValue;
    pRec->flags |= MEM_Real;
    if( bTryForInt ) sqlite3VdbeIntegerAffinity(pRec);
  }
  /* TEXT->NUMERIC is many->one.  Hence, it is important to invalidate the
  ** string representation after computing a numeric equivalent, because the
  ** string representation might not be the canonical representation for the
  ** numeric value.  Ticket [343634942dd54ab57b7024] 2018-01-31. */
  pRec->flags &= ~MEM_Str;
}