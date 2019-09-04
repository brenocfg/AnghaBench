#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  OPFLAG_TYPEOFARG ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sqlite3SetHasNullFlag(Vdbe *v, int iCur, int regHasNull){
  int addr1;
  sqlite3VdbeAddOp2(v, OP_Integer, 0, regHasNull);
  addr1 = sqlite3VdbeAddOp1(v, OP_Rewind, iCur); VdbeCoverage(v);
  sqlite3VdbeAddOp3(v, OP_Column, iCur, 0, regHasNull);
  sqlite3VdbeChangeP5(v, OPFLAG_TYPEOFARG);
  VdbeComment((v, "first_entry_in(%d)", iCur));
  sqlite3VdbeJumpHere(v, addr1);
}