#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int size; scalar_t__ nuse; } ;
struct TYPE_5__ {scalar_t__ gckind; int /*<<< orphan*/  buff; TYPE_1__ strt; } ;
typedef  TYPE_2__ global_State ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ KGC_EMERGENCY ; 
 scalar_t__ cast (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lu_int32 ; 
 int /*<<< orphan*/  luaS_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaZ_freebuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void checkSizes (lua_State *L) {
  global_State *g = G(L);
  if (g->gckind != KGC_EMERGENCY) {  /* do not change sizes in emergency */
    int hs = g->strt.size / 2;  /* half the size of the string table */
    if (g->strt.nuse < cast(lu_int32, hs))  /* using less than that half? */
      luaS_resize(L, hs);  /* halve its size */
    luaZ_freebuffer(L, &g->buff);  /* free concatenation buffer */
  }
}