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
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  IPartialCommit ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Instruction *repeats (lua_State *L, Instruction *p1, int l1, int n) {
  /* e; ...; e; choice L1; L2: e; partialcommit L2; L1: ... */
  int i;
  Instruction *op = newpatt(L, (n + 1)*l1 + 2);
  Instruction *p = op;
  if (!verify(L, p1, p1, p1 + l1, 0, 0))
    luaL_error(L, "loop body may accept empty string");
  for (i = 0; i < n; i++) {
    p += addpatt(L, p, 1);
  }
  setinst(p++, IChoice, 1 + l1 + 1);
  p += addpatt(L, p, 1);
  setinst(p, IPartialCommit, -l1);
  return op;
}