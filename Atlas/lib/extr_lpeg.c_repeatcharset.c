#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/ * buff; } ;
typedef  TYPE_1__ Instruction ;
typedef  int /*<<< orphan*/ * Charset ;

/* Variables and functions */
 scalar_t__ CHARSETINSTSIZE ; 
 int /*<<< orphan*/  ISpan ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  correctset (TYPE_1__*) ; 
 size_t k ; 
 int /*<<< orphan*/  loopset (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* newpatt (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setinst (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int repeatcharset (lua_State *L, Charset cs, int l1, int n) {
  /* e; ...; e; span; */
  int i;
  Instruction *p = newpatt(L, n*l1 + CHARSETINSTSIZE);
  for (i = 0; i < n; i++) {
    p += addpatt(L, p, 1);
  }
  setinst(p, ISpan, 0);
  loopset(k, p[1].buff[k] = cs[k]);
  correctset(p);
  return 1;
}