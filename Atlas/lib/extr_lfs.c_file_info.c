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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {char const* name; int /*<<< orphan*/  (* push ) (int /*<<< orphan*/ *,struct stat*) ;} ;

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* members ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct stat*) ; 

__attribute__((used)) static int file_info (lua_State *L) {
	int i;
	struct stat info;
	const char *file = luaL_checkstring (L, 1);

	if (stat(file, &info)) {
		lua_pushnil (L);
		lua_pushfstring (L, "cannot obtain information from file `%s'", file);
		return 2;
	}
	if (lua_isstring (L, 2)) {
		int v;
		const char *member = lua_tostring (L, 2);
		if (strcmp (member, "mode") == 0) v = 0;
#ifndef _WIN32
		else if (strcmp (member, "blksize") == 0) v = 12;
#endif
		else /* look for member */
			for (v = 1; members[v].name; v++)
				if (*members[v].name == *member)
					break;
		/* push member value and return */
		members[v].push (L, &info);
		return 1;
	} else if (!lua_istable (L, 2))
		/* creates a table if none is given */
		lua_newtable (L);
	/* stores all members in table on top of the stack */
	for (i = 0; members[i].name; i++) {
		lua_pushstring (L, members[i].name);
		members[i].push (L, &info);
		lua_rawset (L, -3);
	}
	return 1;
}