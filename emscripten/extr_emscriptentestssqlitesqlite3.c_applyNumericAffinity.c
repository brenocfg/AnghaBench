#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_4__ {int /*<<< orphan*/  i; } ;
struct TYPE_5__ {int flags; double r; TYPE_1__ u; int /*<<< orphan*/  n; int /*<<< orphan*/  z; int /*<<< orphan*/  enc; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Int ; 
 int MEM_Real ; 
 int MEM_Str ; 
 scalar_t__ sqlite3AtoF (int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3Atoi64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void applyNumericAffinity(Mem *pRec){
  if( (pRec->flags & (MEM_Real|MEM_Int))==0 ){
    double rValue;
    i64 iValue;
    u8 enc = pRec->enc;
    if( (pRec->flags&MEM_Str)==0 ) return;
    if( sqlite3AtoF(pRec->z, &rValue, pRec->n, enc)==0 ) return;
    if( 0==sqlite3Atoi64(pRec->z, &iValue, pRec->n, enc) ){
      pRec->u.i = iValue;
      pRec->flags |= MEM_Int;
    }else{
      pRec->r = rValue;
      pRec->flags |= MEM_Real;
    }
  }
}