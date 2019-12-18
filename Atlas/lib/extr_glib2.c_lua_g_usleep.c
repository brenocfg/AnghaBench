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
 int /*<<< orphan*/  g_usleep (int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lua_g_usleep (lua_State *L) {
	int ms = luaL_checkinteger (L, 1);

	g_usleep(ms);

	return 0;
}