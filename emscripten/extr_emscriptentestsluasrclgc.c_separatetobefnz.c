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
struct TYPE_4__ {int /*<<< orphan*/ * tobefnz; int /*<<< orphan*/ * finobj; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_5__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  marked; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  FINALIZEDBIT ; 
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEPARATED ; 
 TYPE_2__* gch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isfinalized (int /*<<< orphan*/ *) ; 
 scalar_t__ iswhite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int testbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void separatetobefnz (lua_State *L, int all) {
  global_State *g = G(L);
  GCObject **p = &g->finobj;
  GCObject *curr;
  GCObject **lastnext = &g->tobefnz;
  /* find last 'next' field in 'tobefnz' list (to add elements in its end) */
  while (*lastnext != NULL)
    lastnext = &gch(*lastnext)->next;
  while ((curr = *p) != NULL) {  /* traverse all finalizable objects */
    lua_assert(!isfinalized(curr));
    lua_assert(testbit(gch(curr)->marked, SEPARATED));
    if (!(iswhite(curr) || all))  /* not being collected? */
      p = &gch(curr)->next;  /* don't bother with it */
    else {
      l_setbit(gch(curr)->marked, FINALIZEDBIT); /* won't be finalized again */
      *p = gch(curr)->next;  /* remove 'curr' from 'finobj' list */
      gch(curr)->next = *lastnext;  /* link at the end of 'tobefnz' list */
      *lastnext = curr;
      lastnext = &gch(curr)->next;
    }
  }
}