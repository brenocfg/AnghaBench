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
typedef  int /*<<< orphan*/  searchers ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/ * lua_CFunction ;

/* Variables and functions */
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
#define  searcher_C 131 
#define  searcher_Croot 130 
#define  searcher_Lua 129 
#define  searcher_preload 128 

__attribute__((used)) static void createsearcherstable (lua_State *L) {
  static const lua_CFunction searchers[] =
    {searcher_preload, searcher_Lua, searcher_C, searcher_Croot, NULL};
  int i;
  /* create 'searchers' table */
  lua_createtable(L, sizeof(searchers)/sizeof(searchers[0]) - 1, 0);
  /* fill it with pre-defined searchers */
  for (i=0; searchers[i] != NULL; i++) {
    lua_pushvalue(L, -2);  /* set 'package' as upvalue for all searchers */
    lua_pushcclosure(L, searchers[i], 1);
    lua_rawseti(L, -2, i+1);
  }
}