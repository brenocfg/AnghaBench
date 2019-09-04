#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {size_t idx; scalar_t__ instack; } ;
typedef  TYPE_2__ Upvaldesc ;
typedef  int /*<<< orphan*/  UpVal ;
struct TYPE_10__ {int /*<<< orphan*/ ** upvals; TYPE_3__* p; } ;
struct TYPE_13__ {TYPE_1__ l; } ;
struct TYPE_12__ {int sizeupvalues; TYPE_4__* cache; TYPE_2__* upvalues; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_3__ Proto ;
typedef  TYPE_4__ Closure ;

/* Variables and functions */
 int /*<<< orphan*/  luaC_barrierproto (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * luaF_findupval (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* luaF_newLclosure (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setclLvalue (int /*<<< orphan*/ *,scalar_t__,TYPE_4__*) ; 

__attribute__((used)) static void pushclosure (lua_State *L, Proto *p, UpVal **encup, StkId base,
                         StkId ra) {
  int nup = p->sizeupvalues;
  Upvaldesc *uv = p->upvalues;
  int i;
  Closure *ncl = luaF_newLclosure(L, nup);
  ncl->l.p = p;
  setclLvalue(L, ra, ncl);  /* anchor new closure in stack */
  for (i = 0; i < nup; i++) {  /* fill in its upvalues */
    if (uv[i].instack)  /* upvalue refers to local variable? */
      ncl->l.upvals[i] = luaF_findupval(L, base + uv[i].idx);
    else  /* get upvalue from enclosing function */
      ncl->l.upvals[i] = encup[uv[i].idx];
  }
  luaC_barrierproto(L, p, ncl);
  p->cache = ncl;  /* save it on cache for reuse */
}