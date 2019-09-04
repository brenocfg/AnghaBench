#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expdesc ;
struct TYPE_10__ {int token; } ;
struct TYPE_11__ {int linenumber; TYPE_1__ t; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
#define  TK_STRING 128 
 int /*<<< orphan*/  checkname (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fieldsel (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funcargs (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaK_exp2anyregup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_indexed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_self (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int /*<<< orphan*/  primaryexp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yindex (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void suffixedexp (LexState *ls, expdesc *v) {
  /* suffixedexp ->
       primaryexp { '.' NAME | '[' exp ']' | ':' NAME funcargs | funcargs } */
  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  primaryexp(ls, v);
  for (;;) {
    switch (ls->t.token) {
      case '.': {  /* fieldsel */
        fieldsel(ls, v);
        break;
      }
      case '[': {  /* `[' exp1 `]' */
        expdesc key;
        luaK_exp2anyregup(fs, v);
        yindex(ls, &key);
        luaK_indexed(fs, v, &key);
        break;
      }
      case ':': {  /* `:' NAME funcargs */
        expdesc key;
        luaX_next(ls);
        checkname(ls, &key);
        luaK_self(fs, v, &key);
        funcargs(ls, v, line);
        break;
      }
      case '(': case TK_STRING: case '{': {  /* funcargs */
        luaK_exp2nextreg(fs, v);
        funcargs(ls, v, line);
        break;
      }
      default: return;
    }
  }
}