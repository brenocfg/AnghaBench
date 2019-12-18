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
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 char* getcwd_error ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int get_dir (lua_State *L) {
	char path[255+2];
	if (getcwd(path, 255) == NULL) {
		lua_pushnil(L);
		lua_pushstring(L, getcwd_error);
		return 2;
	}
	else {
		lua_pushstring(L, path);
		return 1;
	}
}