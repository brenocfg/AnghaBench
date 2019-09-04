#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nval; } ;
struct TYPE_10__ {TYPE_1__ u; int /*<<< orphan*/  k; int /*<<< orphan*/  f; int /*<<< orphan*/  t; } ;
typedef  TYPE_2__ expdesc ;
typedef  int UnOpr ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  NO_JUMP ; 
#define  OPR_LEN 130 
#define  OPR_MINUS 129 
#define  OPR_NOT 128 
 int /*<<< orphan*/  OP_LEN ; 
 int /*<<< orphan*/  OP_UNM ; 
 int /*<<< orphan*/  VKNUM ; 
 int /*<<< orphan*/  codearith (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  codenot (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  isnumeral (TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_exp2anyreg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ luai_numunm (int /*<<< orphan*/ *,scalar_t__) ; 

void luaK_prefix (FuncState *fs, UnOpr op, expdesc *e, int line) {
  expdesc e2;
  e2.t = e2.f = NO_JUMP; e2.k = VKNUM; e2.u.nval = 0;
  switch (op) {
    case OPR_MINUS: {
      if (isnumeral(e))  /* minus constant? */
        e->u.nval = luai_numunm(NULL, e->u.nval);  /* fold it */
      else {
        luaK_exp2anyreg(fs, e);
        codearith(fs, OP_UNM, e, &e2, line);
      }
      break;
    }
    case OPR_NOT: codenot(fs, e); break;
    case OPR_LEN: {
      luaK_exp2anyreg(fs, e);  /* cannot operate on constants */
      codearith(fs, OP_LEN, e, &e2, line);
      break;
    }
    default: lua_assert(0);
  }
}