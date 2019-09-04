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
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_4__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ UpVal ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/  gray2black (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isblack (int /*<<< orphan*/ *) ; 
 scalar_t__ isgray (int /*<<< orphan*/ *) ; 
 int issweepphase (int /*<<< orphan*/ *) ; 
 scalar_t__ keepinvariant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  makewhite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obj2gco (TYPE_1__*) ; 
 int /*<<< orphan*/  resetoldbit (int /*<<< orphan*/ *) ; 

void luaC_checkupvalcolor (global_State *g, UpVal *uv) {
  GCObject *o = obj2gco(uv);
  lua_assert(!isblack(o));  /* open upvalues are never black */
  if (isgray(o)) {
    if (keepinvariant(g)) {
      resetoldbit(o);  /* see MOVE OLD rule */
      gray2black(o);  /* it is being visited now */
      markvalue(g, uv->v);
    }
    else {
      lua_assert(issweepphase(g));
      makewhite(g, o);
    }
  }
}