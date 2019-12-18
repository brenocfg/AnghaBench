#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_21__ {scalar_t__ tag; int* cs; } ;
struct TYPE_20__ {int* buff; } ;
typedef  TYPE_1__ Instruction ;
typedef  TYPE_2__ CharsetTag ;

/* Variables and functions */
 int CHARSETINSTSIZE ; 
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  ICommit ; 
 int /*<<< orphan*/  IJmp ; 
 scalar_t__ ISCHARSET ; 
 int /*<<< orphan*/  ISet ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* auxnew (int /*<<< orphan*/ *,TYPE_1__**,int*,int) ; 
 int /*<<< orphan*/  check2test (TYPE_1__*,int) ; 
 int /*<<< orphan*/  copypatt (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  correctset (TYPE_1__*) ; 
 scalar_t__ exclusive (TYPE_2__*,TYPE_2__*) ; 
 size_t i ; 
 scalar_t__ isheadfail (TYPE_1__*) ; 
 int /*<<< orphan*/  loopset (size_t,int) ; 
 int /*<<< orphan*/  optimizechoice (TYPE_1__*) ; 
 int /*<<< orphan*/  setinst (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tocharset (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static Instruction *basicUnion (lua_State *L, Instruction *p1, int l1,
                                int l2, int *size, CharsetTag *st2) {
  Instruction *op;
  CharsetTag st1;
  tocharset(p1, &st1);
  if (st1.tag == ISCHARSET && st2->tag == ISCHARSET) {
    Instruction *p = auxnew(L, &op, size, CHARSETINSTSIZE);
    setinst(p, ISet, 0);
    loopset(i, p[1].buff[i] = st1.cs[i] | st2->cs[i]);
    correctset(p);
  }
  else if (exclusive(&st1, st2) || isheadfail(p1)) {
    Instruction *p = auxnew(L, &op, size, l1 + 1 + l2);
    copypatt(p, p1, l1);
    check2test(p, l1 + 1);
    p += l1;
    setinst(p++, IJmp, l2 + 1);
    addpatt(L, p, 2);
  }
  else {
    /* choice L1; e1; commit L2; L1: e2; L2: ... */
    Instruction *p = auxnew(L, &op, size, 1 + l1 + 1 + l2);
    setinst(p++, IChoice, 1 + l1 + 1);
    copypatt(p, p1, l1); p += l1;
    setinst(p++, ICommit, 1 + l2);
    addpatt(L, p, 2);
    optimizechoice(p - (1 + l1 + 1));
  }
  return op;
}