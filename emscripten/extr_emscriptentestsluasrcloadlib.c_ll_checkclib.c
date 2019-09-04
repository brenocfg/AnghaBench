#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char const* CLIBS ; 
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *ll_checkclib (lua_State *L, const char *path) {
  void *plib;
  lua_getfield(L, LUA_REGISTRYINDEX, CLIBS);
  lua_getfield(L, -1, path);
  plib = lua_touserdata(L, -1);  /* plib = CLIBS[path] */
  lua_pop(L, 2);  /* pop CLIBS table and 'plib' */
  return plib;
}