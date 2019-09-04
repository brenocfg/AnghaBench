#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  l_registry; } ;
typedef  TYPE_1__ global_State ;
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_RIDX_GLOBALS ; 
 int /*<<< orphan*/  LUA_RIDX_LAST ; 
 int /*<<< orphan*/  LUA_RIDX_MAINTHREAD ; 
 int /*<<< orphan*/ * luaH_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaH_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_setint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sethvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setthvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_registry (lua_State *L, global_State *g) {
  TValue mt;
  /* create registry */
  Table *registry = luaH_new(L);
  sethvalue(L, &g->l_registry, registry);
  luaH_resize(L, registry, LUA_RIDX_LAST, 0);
  /* registry[LUA_RIDX_MAINTHREAD] = L */
  setthvalue(L, &mt, L);
  luaH_setint(L, registry, LUA_RIDX_MAINTHREAD, &mt);
  /* registry[LUA_RIDX_GLOBALS] = table of globals */
  sethvalue(L, &mt, luaH_new(L));
  luaH_setint(L, registry, LUA_RIDX_GLOBALS, &mt);
}