#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int token; } ;
struct TYPE_19__ {int linenumber; TYPE_1__ t; } ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
#define  TK_BREAK 136 
#define  TK_DO 135 
 int /*<<< orphan*/  TK_END ; 
#define  TK_FOR 134 
#define  TK_FUNCTION 133 
#define  TK_IF 132 
#define  TK_LOCAL 131 
#define  TK_REPEAT 130 
#define  TK_RETURN 129 
#define  TK_WHILE 128 
 int /*<<< orphan*/  block (TYPE_2__*) ; 
 int /*<<< orphan*/  breakstat (TYPE_2__*) ; 
 int /*<<< orphan*/  check_match (TYPE_2__*,int /*<<< orphan*/ ,int const,int) ; 
 int /*<<< orphan*/  exprstat (TYPE_2__*) ; 
 int /*<<< orphan*/  forstat (TYPE_2__*,int) ; 
 int /*<<< orphan*/  funcstat (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ifstat (TYPE_2__*,int) ; 
 int /*<<< orphan*/  localfunc (TYPE_2__*) ; 
 int /*<<< orphan*/  localstat (TYPE_2__*) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int /*<<< orphan*/  repeatstat (TYPE_2__*,int) ; 
 int /*<<< orphan*/  retstat (TYPE_2__*) ; 
 int /*<<< orphan*/  testnext (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  whilestat (TYPE_2__*,int) ; 

__attribute__((used)) static int statement (LexState *ls) {
  int line = ls->linenumber;  /* may be needed for error messages */
  switch (ls->t.token) {
    case TK_IF: {  /* stat -> ifstat */
      ifstat(ls, line);
      return 0;
    }
    case TK_WHILE: {  /* stat -> whilestat */
      whilestat(ls, line);
      return 0;
    }
    case TK_DO: {  /* stat -> DO block END */
      luaX_next(ls);  /* skip DO */
      block(ls);
      check_match(ls, TK_END, TK_DO, line);
      return 0;
    }
    case TK_FOR: {  /* stat -> forstat */
      forstat(ls, line);
      return 0;
    }
    case TK_REPEAT: {  /* stat -> repeatstat */
      repeatstat(ls, line);
      return 0;
    }
    case TK_FUNCTION: {
      funcstat(ls, line);  /* stat -> funcstat */
      return 0;
    }
    case TK_LOCAL: {  /* stat -> localstat */
      luaX_next(ls);  /* skip LOCAL */
      if (testnext(ls, TK_FUNCTION))  /* local function? */
        localfunc(ls);
      else
        localstat(ls);
      return 0;
    }
    case TK_RETURN: {  /* stat -> retstat */
      retstat(ls);
      return 1;  /* must be last statement */
    }
    case TK_BREAK: {  /* stat -> breakstat */
      luaX_next(ls);  /* skip BREAK */
      breakstat(ls);
      return 1;  /* must be last statement */
    }
    default: {
      exprstat(ls);
      return 0;  /* to avoid warnings */
    }
  }
}