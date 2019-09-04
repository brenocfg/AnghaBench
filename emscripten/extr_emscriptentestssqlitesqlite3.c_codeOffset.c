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
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_3__ {scalar_t__ iOffset; } ;
typedef  TYPE_1__ Select ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AddImm ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IfNeg ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codeOffset(
  Vdbe *v,          /* Generate code into this VM */
  Select *p,        /* The SELECT statement being coded */
  int iContinue     /* Jump here to skip the current record */
){
  if( p->iOffset && iContinue!=0 ){
    int addr;
    sqlite3VdbeAddOp2(v, OP_AddImm, p->iOffset, -1);
    addr = sqlite3VdbeAddOp1(v, OP_IfNeg, p->iOffset);
    sqlite3VdbeAddOp2(v, OP_Goto, 0, iContinue);
    VdbeComment((v, "skip OFFSET records"));
    sqlite3VdbeJumpHere(v, addr);
  }
}