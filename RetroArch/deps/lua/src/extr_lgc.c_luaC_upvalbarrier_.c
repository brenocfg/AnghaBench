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
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_4__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ UpVal ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 int /*<<< orphan*/ * G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gcvalue (int /*<<< orphan*/ ) ; 
 scalar_t__ keepinvariant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markobject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upisopen (TYPE_1__*) ; 

void luaC_upvalbarrier_ (lua_State *L, UpVal *uv) {
  global_State *g = G(L);
  GCObject *o = gcvalue(uv->v);
  lua_assert(!upisopen(uv));  /* ensured by macro luaC_upvalbarrier */
  if (keepinvariant(g))
    markobject(g, o);
}