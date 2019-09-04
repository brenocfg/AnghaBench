#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_9__ {int nMem; } ;
struct TYPE_8__ {int iLimit; double nSelectRow; int iOffset; int /*<<< orphan*/  pOffset; int /*<<< orphan*/  pLimit; } ;
typedef  TYPE_1__ Select ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  OP_Add ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IfPos ; 
 int /*<<< orphan*/  OP_IfZero ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_MustBeInt ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheClear (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3ExprIsInteger (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void computeLimitRegisters(Parse *pParse, Select *p, int iBreak){
  Vdbe *v = 0;
  int iLimit = 0;
  int iOffset;
  int addr1, n;
  if( p->iLimit ) return;

  /* 
  ** "LIMIT -1" always shows all rows.  There is some
  ** contraversy about what the correct behavior should be.
  ** The current implementation interprets "LIMIT 0" to mean
  ** no rows.
  */
  sqlite3ExprCacheClear(pParse);
  assert( p->pOffset==0 || p->pLimit!=0 );
  if( p->pLimit ){
    p->iLimit = iLimit = ++pParse->nMem;
    v = sqlite3GetVdbe(pParse);
    if( NEVER(v==0) ) return;  /* VDBE should have already been allocated */
    if( sqlite3ExprIsInteger(p->pLimit, &n) ){
      sqlite3VdbeAddOp2(v, OP_Integer, n, iLimit);
      VdbeComment((v, "LIMIT counter"));
      if( n==0 ){
        sqlite3VdbeAddOp2(v, OP_Goto, 0, iBreak);
      }else{
        if( p->nSelectRow > (double)n ) p->nSelectRow = (double)n;
      }
    }else{
      sqlite3ExprCode(pParse, p->pLimit, iLimit);
      sqlite3VdbeAddOp1(v, OP_MustBeInt, iLimit);
      VdbeComment((v, "LIMIT counter"));
      sqlite3VdbeAddOp2(v, OP_IfZero, iLimit, iBreak);
    }
    if( p->pOffset ){
      p->iOffset = iOffset = ++pParse->nMem;
      pParse->nMem++;   /* Allocate an extra register for limit+offset */
      sqlite3ExprCode(pParse, p->pOffset, iOffset);
      sqlite3VdbeAddOp1(v, OP_MustBeInt, iOffset);
      VdbeComment((v, "OFFSET counter"));
      addr1 = sqlite3VdbeAddOp1(v, OP_IfPos, iOffset);
      sqlite3VdbeAddOp2(v, OP_Integer, 0, iOffset);
      sqlite3VdbeJumpHere(v, addr1);
      sqlite3VdbeAddOp3(v, OP_Add, iLimit, iOffset, iOffset+1);
      VdbeComment((v, "LIMIT+OFFSET"));
      addr1 = sqlite3VdbeAddOp1(v, OP_IfPos, iLimit);
      sqlite3VdbeAddOp2(v, OP_Integer, -1, iOffset+1);
      sqlite3VdbeJumpHere(v, addr1);
    }
  }
}