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
typedef  int /*<<< orphan*/  network_backends_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  BACKEND_TYPE_RO ; 
 int /*<<< orphan*/  BACKEND_TYPE_RW ; 
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup (int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_backends_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_backends_addclient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_backends_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_backends_removeclient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_backends_save (int /*<<< orphan*/ *) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_backends_set(lua_State *L) {
	network_backends_t *bs = *(network_backends_t **)luaL_checkself(L);
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);

	if (strleq(key, keysize, C("addslave"))) {
		gchar *address = g_strdup(lua_tostring(L, -1));
		network_backends_add(bs, address, BACKEND_TYPE_RO);
		g_free(address);
	} else if (strleq(key, keysize, C("addmaster"))) {
		gchar *address = g_strdup(lua_tostring(L, -1));
		network_backends_add(bs, address, BACKEND_TYPE_RW);
		g_free(address);
	} else if (strleq(key, keysize, C("removebackend"))) {
		network_backends_remove(bs, lua_tointeger(L, -1));
	} else if (strleq(key, keysize, C("addclient"))) {
		gchar *address = g_strdup(lua_tostring(L, -1));
		network_backends_addclient(bs, address);
		g_free(address);
	} else if (strleq(key, keysize, C("removeclient"))) {
		gchar *address = g_strdup(lua_tostring(L, -1));
		network_backends_removeclient(bs, address);
		g_free(address);
	} else if (strleq(key, keysize, C("saveconfig"))) {
		network_backends_save(bs);
	} else {
		return luaL_error(L, "proxy.global.backends.%s is not writable", key);
	}
	return 1;
}