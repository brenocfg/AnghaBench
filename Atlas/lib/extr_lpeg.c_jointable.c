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
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_equal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getfenv (int /*<<< orphan*/ *,int) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int jointable (lua_State *L, int p1) {
  int n, n1, i;
  lua_getfenv(L, p1);
  n1 = lua_objlen(L, -1);  /* number of elements in p1's env */
  lua_getfenv(L, -2);
  if (n1 == 0 || lua_equal(L, -2, -1)) {
    lua_pop(L, 2);
    return 0;  /* no need to change anything */
  }
  n = lua_objlen(L, -1);  /* number of elements in p's env */
  if (n == 0) {
    lua_pop(L, 1);  /* removes p env */
    lua_setfenv(L, -2);  /* p now shares p1's env */
    return 0;  /* no need to correct anything */
  }
  lua_createtable(L, n + n1, 0);
  /* stack: p; p1 env; p env; new p env */
  for (i = 1; i <= n; i++) {
    lua_rawgeti(L, -2, i);
    lua_rawseti(L, -2, i);
  }
  for (i = 1; i <= n1; i++) {
    lua_rawgeti(L, -3, i);
    lua_rawseti(L, -2, n + i);
  }
  lua_setfenv(L, -4);  /* new table becomes p env */
  lua_pop(L, 2);  /* remove p1 env and old p env */
  return n;
}