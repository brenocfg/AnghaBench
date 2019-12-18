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
 scalar_t__ chdir (char const*) ; 
 int /*<<< orphan*/  chdir_error ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int change_dir (lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	if (chdir(path)) {
		lua_pushnil (L);
		lua_pushfstring (L,"Unable to change working directory to '%s'\n%s\n",
				path, chdir_error);
		return 2;
	} else {
		lua_pushboolean (L, 1);
		return 1;
	}
}