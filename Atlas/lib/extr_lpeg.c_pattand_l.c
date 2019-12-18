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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  IBackCommit ; 
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  IFail ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int getpattl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setinstaux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pattand_l (lua_State *L) {
  /* &e -> choice L1; e; backcommit L2; L1: fail; L2: ... */
  int l1 = getpattl(L, 1);
  Instruction *p = newpatt(L, 1 + l1 + 2);
  setinst(p++, IChoice, 1 + l1 + 1);
  p += addpatt(L, p, 1);
  setinst(p++, IBackCommit, 2);
  setinstaux(p, IFail, 0, 1);
  return 1;
}