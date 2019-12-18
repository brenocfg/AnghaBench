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
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  newpattfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  span ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int span_l (lua_State *L) {
  const char *s = luaL_checkstring(L, 1);
  newpattfunc(L, span, s, strlen(s) + 1);
  return 1;
}