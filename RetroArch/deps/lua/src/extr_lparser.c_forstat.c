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
struct TYPE_10__ {int token; } ;
struct TYPE_11__ {TYPE_1__ t; int /*<<< orphan*/ * fs; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  TK_END ; 
 int /*<<< orphan*/  TK_FOR ; 
#define  TK_IN 128 
 int /*<<< orphan*/  check_match (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enterblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  forlist (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fornum (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  leaveblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * str_checkname (TYPE_2__*) ; 

__attribute__((used)) static void forstat (LexState *ls, int line) {
  /* forstat -> FOR (fornum | forlist) END */
  FuncState *fs = ls->fs;
  TString *varname;
  BlockCnt bl;
  enterblock(fs, &bl, 1);  /* scope for loop and control variables */
  luaX_next(ls);  /* skip 'for' */
  varname = str_checkname(ls);  /* first variable name */
  switch (ls->t.token) {
    case '=': fornum(ls, varname, line); break;
    case ',': case TK_IN: forlist(ls, varname); break;
    default: luaX_syntaxerror(ls, "'=' or 'in' expected");
  }
  check_match(ls, TK_END, TK_FOR, line);
  leaveblock(fs);  /* loop scope ('break' jumps to this point) */
}