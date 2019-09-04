#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lu_mem ;
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_2__ {int marked; scalar_t__ tt; int /*<<< orphan*/ * next; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/ * G (int /*<<< orphan*/ *) ; 
 scalar_t__ LUA_TTHREAD ; 
 int /*<<< orphan*/  OLDBIT ; 
 int bitmask (int /*<<< orphan*/ ) ; 
 int cast_byte (int) ; 
 int /*<<< orphan*/  freeobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* gch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2th (int /*<<< orphan*/ *) ; 
 scalar_t__ isdeadm (int,int) ; 
 scalar_t__ isgenerational (int /*<<< orphan*/ *) ; 
 int luaC_white (int /*<<< orphan*/ *) ; 
 int maskcolors ; 
 int otherwhite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sweepthread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ testbits (int,int) ; 

__attribute__((used)) static GCObject **sweeplist (lua_State *L, GCObject **p, lu_mem count) {
  global_State *g = G(L);
  int ow = otherwhite(g);
  int toclear, toset;  /* bits to clear and to set in all live objects */
  int tostop;  /* stop sweep when this is true */
  if (isgenerational(g)) {  /* generational mode? */
    toclear = ~0;  /* clear nothing */
    toset = bitmask(OLDBIT);  /* set the old bit of all surviving objects */
    tostop = bitmask(OLDBIT);  /* do not sweep old generation */
  }
  else {  /* normal mode */
    toclear = maskcolors;  /* clear all color bits + old bit */
    toset = luaC_white(g);  /* make object white */
    tostop = 0;  /* do not stop */
  }
  while (*p != NULL && count-- > 0) {
    GCObject *curr = *p;
    int marked = gch(curr)->marked;
    if (isdeadm(ow, marked)) {  /* is 'curr' dead? */
      *p = gch(curr)->next;  /* remove 'curr' from list */
      freeobj(L, curr);  /* erase 'curr' */
    }
    else {
      if (testbits(marked, tostop))
        return NULL;  /* stop sweeping this list */
      if (gch(curr)->tt == LUA_TTHREAD)
        sweepthread(L, gco2th(curr));  /* sweep thread's upvalues */
      /* update marks */
      gch(curr)->marked = cast_byte((marked & toclear) | toset);
      p = &gch(curr)->next;  /* go to next element */
    }
  }
  return (*p == NULL) ? NULL : p;
}