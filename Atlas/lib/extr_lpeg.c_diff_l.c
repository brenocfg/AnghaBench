#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {int* cs; } ;
struct TYPE_13__ {int* buff; } ;
typedef  TYPE_1__ Instruction ;
typedef  TYPE_2__ CharsetTag ;

/* Variables and functions */
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  IFail ; 
 int /*<<< orphan*/  IFailTwice ; 
 scalar_t__ ISCHARSET ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  check2test (TYPE_1__*,int) ; 
 int /*<<< orphan*/  correctset (TYPE_1__*) ; 
 TYPE_1__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 size_t i ; 
 scalar_t__ isheadfail (TYPE_1__*) ; 
 int /*<<< orphan*/  loopset (size_t,int) ; 
 TYPE_1__* newcharset (int /*<<< orphan*/ *) ; 
 TYPE_1__* newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  optimizechoice (TYPE_1__*) ; 
 int /*<<< orphan*/  setinst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tocharset (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int diff_l (lua_State *L) {
  int l1, l2;
  Instruction *p1 = getpatt(L, 1, &l1);
  Instruction *p2 = getpatt(L, 2, &l2);
  CharsetTag st1, st2;
  if (tocharset(p1, &st1) == ISCHARSET && tocharset(p2, &st2) == ISCHARSET) {
    Instruction *p = newcharset(L);
    loopset(i, p[1].buff[i] = st1.cs[i] & ~st2.cs[i]);
    correctset(p);
  }
  else if (isheadfail(p2)) {
    Instruction *p = newpatt(L, l2 + 1 + l1);
    p += addpatt(L, p, 2);
    check2test(p - l2, l2 + 1);
    setinst(p++, IFail, 0);
    addpatt(L, p, 1);
  }
  else {  /* !e2 . e1 */
    /* !e -> choice L1; e; failtwice; L1: ... */
    Instruction *p = newpatt(L, 1 + l2 + 1 + l1);
    Instruction *pi = p;
    setinst(p++, IChoice, 1 + l2 + 1);
    p += addpatt(L, p, 2);
    setinst(p++, IFailTwice, 0);
    addpatt(L, p, 1);
    optimizechoice(pi);
  }
  return 1;
}