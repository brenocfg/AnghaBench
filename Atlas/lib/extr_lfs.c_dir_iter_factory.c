#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {long hFile; int /*<<< orphan*/ * dir; int /*<<< orphan*/  pattern; scalar_t__ closed; } ;
typedef  TYPE_1__ dir_data ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_METATABLE ; 
 scalar_t__ MAX_DIR_LENGTH ; 
 int /*<<< orphan*/  dir_iter ; 
 int /*<<< orphan*/  errno ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int dir_iter_factory (lua_State *L) {
	const char *path = luaL_checkstring (L, 1);
	dir_data *d = (dir_data *) lua_newuserdata (L, sizeof(dir_data));
	d->closed = 0;
#ifdef _WIN32
	d->hFile = 0L;
	luaL_getmetatable (L, DIR_METATABLE);
	lua_setmetatable (L, -2);
	if (strlen(path) > MAX_DIR_LENGTH)
		luaL_error (L, "path too long: %s", path);
	else
		sprintf (d->pattern, "%s/*", path);
#else
	luaL_getmetatable (L, DIR_METATABLE);
	lua_setmetatable (L, -2);
	d->dir = opendir (path);
	if (d->dir == NULL)
		luaL_error (L, "cannot open %s: %s", path, strerror (errno));
#endif
	lua_pushcclosure (L, dir_iter, 1);
	return 1;
}