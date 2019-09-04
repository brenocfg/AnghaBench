#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  info; } ;
struct TYPE_8__ {int /*<<< orphan*/  k; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  scalar_t__ OpCode ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ OP_EQ ; 
 int /*<<< orphan*/  VJMP ; 
 int /*<<< orphan*/  condjump (int /*<<< orphan*/ *,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  freeexp (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int luaK_exp2RK (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void codecomp (FuncState *fs, OpCode op, int cond, expdesc *e1,
                                                          expdesc *e2) {
  int o1 = luaK_exp2RK(fs, e1);
  int o2 = luaK_exp2RK(fs, e2);
  freeexp(fs, e2);
  freeexp(fs, e1);
  if (cond == 0 && op != OP_EQ) {
    int temp;  /* exchange args to replace by `<' or `<=' */
    temp = o1; o1 = o2; o2 = temp;  /* o1 <==> o2 */
    cond = 1;
  }
  e1->u.info = condjump(fs, op, cond, o1, o2);
  e1->k = VJMP;
}