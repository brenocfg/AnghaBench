#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int info; } ;
struct TYPE_28__ {scalar_t__ k; TYPE_3__ u; } ;
typedef  TYPE_4__ expdesc ;
struct TYPE_30__ {int freereg; } ;
struct TYPE_25__ {int /*<<< orphan*/  ts; } ;
struct TYPE_26__ {int token; TYPE_1__ seminfo; } ;
struct TYPE_29__ {TYPE_2__ t; TYPE_6__* fs; } ;
typedef  TYPE_5__ LexState ;
typedef  TYPE_6__ FuncState ;

/* Variables and functions */
 int LUA_MULTRET ; 
 int /*<<< orphan*/  OP_CALL ; 
#define  TK_STRING 128 
 int /*<<< orphan*/  VCALL ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  check_match (TYPE_5__*,char,char,int) ; 
 int /*<<< orphan*/  codestring (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constructor (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  explist (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ hasmultret (scalar_t__) ; 
 int /*<<< orphan*/  init_exp (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_6__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  luaK_fixline (TYPE_6__*,int) ; 
 int /*<<< orphan*/  luaK_setmultret (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  luaX_next (TYPE_5__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void funcargs (LexState *ls, expdesc *f, int line) {
  FuncState *fs = ls->fs;
  expdesc args;
  int base, nparams;
  switch (ls->t.token) {
    case '(': {  /* funcargs -> `(' [ explist ] `)' */
      luaX_next(ls);
      if (ls->t.token == ')')  /* arg list is empty? */
        args.k = VVOID;
      else {
        explist(ls, &args);
        luaK_setmultret(fs, &args);
      }
      check_match(ls, ')', '(', line);
      break;
    }
    case '{': {  /* funcargs -> constructor */
      constructor(ls, &args);
      break;
    }
    case TK_STRING: {  /* funcargs -> STRING */
      codestring(ls, &args, ls->t.seminfo.ts);
      luaX_next(ls);  /* must use `seminfo' before `next' */
      break;
    }
    default: {
      luaX_syntaxerror(ls, "function arguments expected");
    }
  }
  lua_assert(f->k == VNONRELOC);
  base = f->u.info;  /* base register for call */
  if (hasmultret(args.k))
    nparams = LUA_MULTRET;  /* open call */
  else {
    if (args.k != VVOID)
      luaK_exp2nextreg(fs, &args);  /* close last argument */
    nparams = fs->freereg - (base+1);
  }
  init_exp(f, VCALL, luaK_codeABC(fs, OP_CALL, base, nparams+1, 2));
  luaK_fixline(fs, line);
  fs->freereg = base+1;  /* call remove function and arguments and leaves
                            (unless changed) one result */
}