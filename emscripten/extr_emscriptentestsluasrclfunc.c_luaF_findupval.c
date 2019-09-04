#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* next; TYPE_3__* prev; } ;
struct TYPE_16__ {TYPE_1__ l; int /*<<< orphan*/  value; } ;
struct TYPE_17__ {TYPE_2__ u; int /*<<< orphan*/ * v; int /*<<< orphan*/ * next; int /*<<< orphan*/ * openupval; } ;
typedef  TYPE_3__ lua_State ;
struct TYPE_18__ {TYPE_3__ uvhead; } ;
typedef  TYPE_4__ global_State ;
typedef  TYPE_3__ UpVal ;
struct TYPE_19__ {TYPE_3__ uv; } ;
typedef  int /*<<< orphan*/ * StkId ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_4__* G (TYPE_3__*) ; 
 int /*<<< orphan*/  LUA_TUPVAL ; 
 int /*<<< orphan*/  changewhite (int /*<<< orphan*/ *) ; 
 TYPE_3__* gco2uv (int /*<<< orphan*/ *) ; 
 scalar_t__ isdead (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ isold (int /*<<< orphan*/ *) ; 
 TYPE_9__* luaC_newobj (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * obj2gco (TYPE_3__*) ; 

UpVal *luaF_findupval (lua_State *L, StkId level) {
  global_State *g = G(L);
  GCObject **pp = &L->openupval;
  UpVal *p;
  UpVal *uv;
  while (*pp != NULL && (p = gco2uv(*pp))->v >= level) {
    GCObject *o = obj2gco(p);
    lua_assert(p->v != &p->u.value);
    lua_assert(!isold(o) || isold(obj2gco(L)));
    if (p->v == level) {  /* found a corresponding upvalue? */
      if (isdead(g, o))  /* is it dead? */
        changewhite(o);  /* resurrect it */
      return p;
    }
    pp = &p->next;
  }
  /* not found: create a new one */
  uv = &luaC_newobj(L, LUA_TUPVAL, sizeof(UpVal), pp, 0)->uv;
  uv->v = level;  /* current value lives in the stack */
  uv->u.l.prev = &g->uvhead;  /* double link it in `uvhead' list */
  uv->u.l.next = g->uvhead.u.l.next;
  uv->u.l.next->u.l.prev = uv;
  g->uvhead.u.l.next = uv;
  lua_assert(uv->u.l.next->u.l.prev == uv && uv->u.l.prev->u.l.next == uv);
  return uv;
}