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
typedef  int /*<<< orphan*/  proxy_resultset_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GRef ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/ * g_ref_new () ; 
 int /*<<< orphan*/  g_ref_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  methods_proxy_resultset ; 
 int /*<<< orphan*/  proxy_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ proxy_resultset_free ; 

__attribute__((used)) static int proxy_resultset_lua_push(lua_State *L, proxy_resultset_t *_res) {
	GRef **ref_p;
	GRef *ref;

	ref = g_ref_new();
	g_ref_set(ref, _res, (GDestroyNotify)proxy_resultset_free);
	
	ref_p = lua_newuserdata(L, sizeof(GRef *));
	*ref_p = ref;

	proxy_getmetatable(L, methods_proxy_resultset);
	lua_setmetatable(L, -2);

	return 1;
}