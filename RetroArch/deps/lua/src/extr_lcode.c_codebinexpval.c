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
struct TYPE_8__ {int /*<<< orphan*/  info; } ;
struct TYPE_9__ {int /*<<< orphan*/  k; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  OpCode ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  VRELOCABLE ; 
 int /*<<< orphan*/  freeexps (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_codeABC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int luaK_exp2RK (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_fixline (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codebinexpval (FuncState *fs, OpCode op,
                           expdesc *e1, expdesc *e2, int line) {
  int rk2 = luaK_exp2RK(fs, e2);  /* both operands are "RK" */
  int rk1 = luaK_exp2RK(fs, e1);
  freeexps(fs, e1, e2);
  e1->u.info = luaK_codeABC(fs, op, 0, rk1, rk2);  /* generate opcode */
  e1->k = VRELOCABLE;  /* all those operations are relocatable */
  luaK_fixline(fs, line);
}