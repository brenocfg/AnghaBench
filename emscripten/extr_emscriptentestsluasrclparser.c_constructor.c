#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ k; } ;
struct ConsControl {scalar_t__ na; scalar_t__ nh; scalar_t__ tostore; TYPE_3__ v; TYPE_3__* t; } ;
typedef  TYPE_3__ expdesc ;
struct TYPE_22__ {TYPE_2__* f; } ;
struct TYPE_18__ {char token; } ;
struct TYPE_21__ {int linenumber; TYPE_1__ t; TYPE_5__* fs; } ;
struct TYPE_19__ {int /*<<< orphan*/ * code; } ;
typedef  TYPE_4__ LexState ;
typedef  TYPE_5__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_NEWTABLE ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETARG_C (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VRELOCABLE ; 
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  check_match (TYPE_4__*,char,char,int) ; 
 int /*<<< orphan*/  checknext (TYPE_4__*,char) ; 
 int /*<<< orphan*/  closelistfield (TYPE_5__*,struct ConsControl*) ; 
 int /*<<< orphan*/  field (TYPE_4__*,struct ConsControl*) ; 
 int /*<<< orphan*/  init_exp (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/  lastlistfield (TYPE_5__*,struct ConsControl*) ; 
 int luaK_codeABC (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaO_int2fb (scalar_t__) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ testnext (TYPE_4__*,char) ; 

__attribute__((used)) static void constructor (LexState *ls, expdesc *t) {
  /* constructor -> '{' [ field { sep field } [sep] ] '}'
     sep -> ',' | ';' */
  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  int pc = luaK_codeABC(fs, OP_NEWTABLE, 0, 0, 0);
  struct ConsControl cc;
  cc.na = cc.nh = cc.tostore = 0;
  cc.t = t;
  init_exp(t, VRELOCABLE, pc);
  init_exp(&cc.v, VVOID, 0);  /* no value (yet) */
  luaK_exp2nextreg(ls->fs, t);  /* fix it at stack top */
  checknext(ls, '{');
  do {
    lua_assert(cc.v.k == VVOID || cc.tostore > 0);
    if (ls->t.token == '}') break;
    closelistfield(fs, &cc);
    field(ls, &cc);
  } while (testnext(ls, ',') || testnext(ls, ';'));
  check_match(ls, '}', '{', line);
  lastlistfield(fs, &cc);
  SETARG_B(fs->f->code[pc], luaO_int2fb(cc.na)); /* set initial array size */
  SETARG_C(fs->f->code[pc], luaO_int2fb(cc.nh));  /* set initial table size */
}