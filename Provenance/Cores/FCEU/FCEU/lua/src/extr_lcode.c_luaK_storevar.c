#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int info; int aux; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
struct TYPE_12__ {int k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_SETGLOBAL ; 
 int /*<<< orphan*/  OP_SETTABLE ; 
 int /*<<< orphan*/  OP_SETUPVAL ; 
#define  VGLOBAL 131 
#define  VINDEXED 130 
#define  VLOCAL 129 
#define  VUPVAL 128 
 int /*<<< orphan*/  exp2reg (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  freeexp (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_codeABC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  luaK_codeABx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int luaK_exp2RK (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int luaK_exp2anyreg (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

void luaK_storevar (FuncState *fs, expdesc *var, expdesc *ex) {
  switch (var->k) {
    case VLOCAL: {
      freeexp(fs, ex);
      exp2reg(fs, ex, var->u.s.info);
      return;
    }
    case VUPVAL: {
      int e = luaK_exp2anyreg(fs, ex);
      luaK_codeABC(fs, OP_SETUPVAL, e, var->u.s.info, 0);
      break;
    }
    case VGLOBAL: {
      int e = luaK_exp2anyreg(fs, ex);
      luaK_codeABx(fs, OP_SETGLOBAL, e, var->u.s.info);
      break;
    }
    case VINDEXED: {
      int e = luaK_exp2RK(fs, ex);
      luaK_codeABC(fs, OP_SETTABLE, var->u.s.info, var->u.s.aux, e);
      break;
    }
    default: {
      lua_assert(0);  /* invalid var kind to store */
      break;
    }
  }
  freeexp(fs, ex);
}