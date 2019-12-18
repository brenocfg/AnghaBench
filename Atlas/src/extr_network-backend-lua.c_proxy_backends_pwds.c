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
typedef  int guint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
#define  ADD_ENPWD 130 
#define  ADD_PWD 129 
 int ERR_USER_EXIST ; 
 int ERR_USER_NOT_EXIST ; 
 int /*<<< orphan*/  FALSE ; 
#define  REMOVE_PWD 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_tostring (int /*<<< orphan*/ *,int) ; 
 int network_backends_addpwd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int network_backends_removepwd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proxy_pwds_exist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_backends_pwds(lua_State *L) {
	network_backends_t *bs = *(network_backends_t **)luaL_checkself(L);
	guint type  = lua_tointeger(L, -1);
	gchar *pwd  = lua_tostring(L, -2);
	gchar *user = lua_tostring(L, -3);

	gboolean is_user_exist = proxy_pwds_exist(bs, user);
	int ret = -1;

	switch (type) {
	case ADD_PWD:
		if (is_user_exist) {
			ret = ERR_USER_EXIST;
		} else {
			ret = network_backends_addpwd(bs, user, pwd, FALSE);
		}
		break;

	case ADD_ENPWD:
		if (is_user_exist) {
			ret = ERR_USER_EXIST;
		} else {
			ret = network_backends_addpwd(bs, user, pwd, TRUE);
		}
		break;

	case REMOVE_PWD:
		if (!is_user_exist) {
			ret = ERR_USER_NOT_EXIST;
		} else {
			ret = network_backends_removepwd(bs, user);
		}
		break;

	default:
		g_assert_not_reached();
	}

	lua_pushinteger(L, ret);
	return 1;
}