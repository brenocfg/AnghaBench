#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int gckind; int /*<<< orphan*/  GCestimate; } ;
typedef  TYPE_1__ global_State ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GCSpropagate ; 
 int KGC_GEN ; 
 int KGC_NORMAL ; 
 int /*<<< orphan*/  bitmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entersweep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettotalbytes (TYPE_1__*) ; 
 int /*<<< orphan*/  luaC_runtilstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sweepphases ; 

void luaC_changemode (lua_State *L, int mode) {
  global_State *g = G(L);
  if (mode == g->gckind) return;  /* nothing to change */
  if (mode == KGC_GEN) {  /* change to generational mode */
    /* make sure gray lists are consistent */
    luaC_runtilstate(L, bitmask(GCSpropagate));
    g->GCestimate = gettotalbytes(g);
    g->gckind = KGC_GEN;
  }
  else {  /* change to incremental mode */
    /* sweep all objects to turn them back to white
       (as white has not changed, nothing extra will be collected) */
    g->gckind = KGC_NORMAL;
    entersweep(L);
    luaC_runtilstate(L, ~sweepphases);
  }
}