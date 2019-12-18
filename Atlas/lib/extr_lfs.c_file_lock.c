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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ _file_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,long const,long,char*) ; 
 int /*<<< orphan*/ * check_file (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  errno ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 void* luaL_optlong (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_lock (lua_State *L) {
	FILE *fh = check_file (L, 1, "lock");
	const char *mode = luaL_checkstring (L, 2);
	const long start = luaL_optlong (L, 3, 0);
	long len = luaL_optlong (L, 4, 0);
	if (_file_lock (L, fh, mode, start, len, "lock")) {
		lua_pushboolean (L, 1);
		return 1;
	} else {
		lua_pushnil (L);
		lua_pushfstring (L, "%s", strerror(errno));
		return 2;
	}
}