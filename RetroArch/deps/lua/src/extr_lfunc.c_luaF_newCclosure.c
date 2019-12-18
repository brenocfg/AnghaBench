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
struct TYPE_4__ {int /*<<< orphan*/  nupvalues; } ;
typedef  int /*<<< orphan*/  GCObject ;
typedef  TYPE_1__ CClosure ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TCCL ; 
 int /*<<< orphan*/  cast_byte (int) ; 
 TYPE_1__* gco2ccl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaC_newobj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeCclosure (int) ; 

CClosure *luaF_newCclosure (lua_State *L, int n) {
  GCObject *o = luaC_newobj(L, LUA_TCCL, sizeCclosure(n));
  CClosure *c = gco2ccl(o);
  c->nupvalues = cast_byte(n);
  return c;
}