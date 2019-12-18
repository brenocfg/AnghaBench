#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int hookmask; scalar_t__ hookcount; int /*<<< orphan*/  ci; int /*<<< orphan*/  const* savedpc; } ;
typedef  TYPE_2__ lua_State ;
typedef  int lu_byte ;
struct TYPE_7__ {int /*<<< orphan*/ * p; } ;
struct TYPE_9__ {TYPE_1__ l; } ;
typedef  int /*<<< orphan*/  Proto ;
typedef  int /*<<< orphan*/  const Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_HOOKCOUNT ; 
 int /*<<< orphan*/  LUA_HOOKLINE ; 
 int LUA_MASKCOUNT ; 
 int LUA_MASKLINE ; 
 TYPE_6__* ci_func (int /*<<< orphan*/ ) ; 
 int getline (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaD_callhook (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int pcRel (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resethookcount (TYPE_2__*) ; 

__attribute__((used)) static void traceexec (lua_State *L, const Instruction *pc) {
  lu_byte mask = L->hookmask;
  const Instruction *oldpc = L->savedpc;
  L->savedpc = pc;
  if ((mask & LUA_MASKCOUNT) && L->hookcount == 0) {
    resethookcount(L);
    luaD_callhook(L, LUA_HOOKCOUNT, -1);
  }
  if (mask & LUA_MASKLINE) {
    Proto *p = ci_func(L->ci)->l.p;
    int npc = pcRel(pc, p);
    int newline = getline(p, npc);
    /* call linehook when enter a new function, when jump back (loop),
       or when enter a new line */
    if (npc == 0 || pc <= oldpc || newline != getline(p, pcRel(oldpc, p)))
      luaD_callhook(L, LUA_HOOKLINE, newline);
  }
}