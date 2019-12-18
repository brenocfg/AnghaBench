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
typedef  int /*<<< orphan*/  GRef ;

/* Variables and functions */
 int /*<<< orphan*/  g_ref_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  methods_proxy_resultset ; 
 int /*<<< orphan*/  proxy_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_resultset_lua_push_ref(lua_State *L, GRef *ref) {
	GRef **ref_p;

	g_ref_ref(ref);
	
	ref_p = lua_newuserdata(L, sizeof(GRef *));
	*ref_p = ref;

	proxy_getmetatable(L, methods_proxy_resultset);
	lua_setmetatable(L, -2);

	return 1;
}