#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {int /*<<< orphan*/ * finobj; int /*<<< orphan*/ * allgc; int /*<<< orphan*/ ** sweepgc; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_10__ {int /*<<< orphan*/  marked; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ GCheader ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEPARATED ; 
 int /*<<< orphan*/  TM_GC ; 
 TYPE_2__* gch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gfasttm (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isfinalized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issweepphase (TYPE_1__*) ; 
 int /*<<< orphan*/  keepinvariantout (TYPE_1__*) ; 
 int /*<<< orphan*/  l_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makewhite (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetoldbit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sweeptolive (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ testbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void luaC_checkfinalizer (lua_State *L, GCObject *o, Table *mt) {
  global_State *g = G(L);
  if (testbit(gch(o)->marked, SEPARATED) || /* obj. is already separated... */
      isfinalized(o) ||                           /* ... or is finalized... */
      gfasttm(g, mt, TM_GC) == NULL)                /* or has no finalizer? */
    return;  /* nothing to be done */
  else {  /* move 'o' to 'finobj' list */
    GCObject **p;
    GCheader *ho = gch(o);
    if (g->sweepgc == &ho->next) {  /* avoid removing current sweep object */
      lua_assert(issweepphase(g));
      g->sweepgc = sweeptolive(L, g->sweepgc, NULL);
    }
    /* search for pointer pointing to 'o' */
    for (p = &g->allgc; *p != o; p = &gch(*p)->next) { /* empty */ }
    *p = ho->next;  /* remove 'o' from root list */
    ho->next = g->finobj;  /* link it in list 'finobj' */
    g->finobj = o;
    l_setbit(ho->marked, SEPARATED);  /* mark it as such */
    if (!keepinvariantout(g))  /* not keeping invariant? */
      makewhite(g, o);  /* "sweep" object */
    else
      resetoldbit(o);  /* see MOVE OLD rule */
  }
}