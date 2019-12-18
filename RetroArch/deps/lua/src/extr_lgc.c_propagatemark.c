#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {TYPE_6__* gclist; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ lu_mem ;
struct TYPE_34__ {int /*<<< orphan*/  GCmemtrav; TYPE_6__* gray; int /*<<< orphan*/  grayagain; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_35__ {TYPE_6__* gclist; } ;
typedef  TYPE_3__ Table ;
struct TYPE_39__ {TYPE_6__* gclist; } ;
struct TYPE_38__ {int tt; } ;
struct TYPE_37__ {TYPE_6__* gclist; } ;
struct TYPE_36__ {TYPE_6__* gclist; } ;
typedef  TYPE_4__ Proto ;
typedef  TYPE_5__ LClosure ;
typedef  TYPE_6__ GCObject ;
typedef  TYPE_7__ CClosure ;

/* Variables and functions */
#define  LUA_TCCL 132 
#define  LUA_TLCL 131 
#define  LUA_TPROTO 130 
#define  LUA_TTABLE 129 
#define  LUA_TTHREAD 128 
 int /*<<< orphan*/  black2gray (TYPE_6__*) ; 
 TYPE_7__* gco2ccl (TYPE_6__*) ; 
 TYPE_5__* gco2lcl (TYPE_6__*) ; 
 TYPE_4__* gco2p (TYPE_6__*) ; 
 TYPE_3__* gco2t (TYPE_6__*) ; 
 TYPE_1__* gco2th (TYPE_6__*) ; 
 int /*<<< orphan*/  gray2black (TYPE_6__*) ; 
 int /*<<< orphan*/  isgray (TYPE_6__*) ; 
 int /*<<< orphan*/  linkgclist (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ traverseCclosure (TYPE_2__*,TYPE_7__*) ; 
 scalar_t__ traverseLclosure (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ traverseproto (TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ traversetable (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ traversethread (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void propagatemark (global_State *g) {
  lu_mem size;
  GCObject *o = g->gray;
  lua_assert(isgray(o));
  gray2black(o);
  switch (o->tt) {
    case LUA_TTABLE: {
      Table *h = gco2t(o);
      g->gray = h->gclist;  /* remove from 'gray' list */
      size = traversetable(g, h);
      break;
    }
    case LUA_TLCL: {
      LClosure *cl = gco2lcl(o);
      g->gray = cl->gclist;  /* remove from 'gray' list */
      size = traverseLclosure(g, cl);
      break;
    }
    case LUA_TCCL: {
      CClosure *cl = gco2ccl(o);
      g->gray = cl->gclist;  /* remove from 'gray' list */
      size = traverseCclosure(g, cl);
      break;
    }
    case LUA_TTHREAD: {
      lua_State *th = gco2th(o);
      g->gray = th->gclist;  /* remove from 'gray' list */
      linkgclist(th, g->grayagain);  /* insert into 'grayagain' list */
      black2gray(o);
      size = traversethread(g, th);
      break;
    }
    case LUA_TPROTO: {
      Proto *p = gco2p(o);
      g->gray = p->gclist;  /* remove from 'gray' list */
      size = traverseproto(g, p);
      break;
    }
    default: lua_assert(0); return;
  }
  g->GCmemtrav += size;
}