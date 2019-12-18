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
struct luaL_reg {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  proxy_backends_get 131 
#define  proxy_backends_len 130 
#define  proxy_backends_pwds 129 
#define  proxy_backends_set 128 
 int proxy_getmetatable (int /*<<< orphan*/ *,struct luaL_reg const*) ; 

int network_backends_lua_getmetatable(lua_State *L) {
	static const struct luaL_reg methods[] = {
		{ "__index", proxy_backends_get },
		{ "__newindex", proxy_backends_set },
		{ "__len", proxy_backends_len },
		{ "__call", proxy_backends_pwds },
		{ NULL, NULL },
	};

	return proxy_getmetatable(L, methods);
}