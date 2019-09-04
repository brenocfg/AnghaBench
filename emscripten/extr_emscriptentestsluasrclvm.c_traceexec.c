#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int hookmask; int hookcount; scalar_t__ oldpc; scalar_t__ status; scalar_t__ top; TYPE_4__* ci; } ;
typedef  TYPE_3__ lua_State ;
typedef  int lu_byte ;
struct TYPE_15__ {int /*<<< orphan*/ * p; } ;
struct TYPE_11__ {scalar_t__ savedpc; } ;
struct TYPE_12__ {TYPE_1__ l; } ;
struct TYPE_14__ {int callstatus; scalar_t__ func; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  Proto ;
typedef  TYPE_4__ CallInfo ;

/* Variables and functions */
 int CIST_HOOKYIELD ; 
 int /*<<< orphan*/  LUA_HOOKCOUNT ; 
 int /*<<< orphan*/  LUA_HOOKLINE ; 
 int LUA_MASKCOUNT ; 
 int LUA_MASKLINE ; 
 scalar_t__ LUA_YIELD ; 
 TYPE_9__* ci_func (TYPE_4__*) ; 
 int getfuncline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaD_hook (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaD_throw (TYPE_3__*,scalar_t__) ; 
 int pcRel (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resethookcount (TYPE_3__*) ; 

__attribute__((used)) static void traceexec (lua_State *L) {
  CallInfo *ci = L->ci;
  lu_byte mask = L->hookmask;
  int counthook = ((mask & LUA_MASKCOUNT) && L->hookcount == 0);
  if (counthook)
    resethookcount(L);  /* reset count */
  if (ci->callstatus & CIST_HOOKYIELD) {  /* called hook last time? */
    ci->callstatus &= ~CIST_HOOKYIELD;  /* erase mark */
    return;  /* do not call hook again (VM yielded, so it did not move) */
  }
  if (counthook)
    luaD_hook(L, LUA_HOOKCOUNT, -1);  /* call count hook */
  if (mask & LUA_MASKLINE) {
    Proto *p = ci_func(ci)->p;
    int npc = pcRel(ci->u.l.savedpc, p);
    int newline = getfuncline(p, npc);
    if (npc == 0 ||  /* call linehook when enter a new function, */
        ci->u.l.savedpc <= L->oldpc ||  /* when jump back (loop), or when */
        newline != getfuncline(p, pcRel(L->oldpc, p)))  /* enter a new line */
      luaD_hook(L, LUA_HOOKLINE, newline);  /* call line hook */
  }
  L->oldpc = ci->u.l.savedpc;
  if (L->status == LUA_YIELD) {  /* did hook yield? */
    if (counthook)
      L->hookcount = 1;  /* undo decrement to zero */
    ci->u.l.savedpc--;  /* undo increment (resume will increment it again) */
    ci->callstatus |= CIST_HOOKYIELD;  /* mark that it yielded */
    ci->func = L->top - 1;  /* protect stack below results */
    luaD_throw(L, LUA_YIELD);
  }
}