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
typedef  void* time_t ;
struct utimbuf {void* actime; void* modtime; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_optnumber (int /*<<< orphan*/ *,int,void*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ utime (char const*,struct utimbuf*) ; 

__attribute__((used)) static int file_utime (lua_State *L) {
	const char *file = luaL_checkstring (L, 1);
	struct utimbuf utb, *buf;

	if (lua_gettop (L) == 1) /* set to current date/time */
		buf = NULL;
	else {
		utb.actime = (time_t)luaL_optnumber (L, 2, 0);
		utb.modtime = (time_t)luaL_optnumber (L, 3, utb.actime);
		buf = &utb;
	}
	if (utime (file, buf)) {
		lua_pushnil (L);
		lua_pushfstring (L, "%s", strerror (errno));
		return 2;
	}
	lua_pushboolean (L, 1);
	return 1;
}