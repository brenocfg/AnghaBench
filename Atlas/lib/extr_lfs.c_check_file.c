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
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static FILE *check_file (lua_State *L, int idx, const char *funcname) {
	FILE **fh = (FILE **)luaL_checkudata (L, idx, "FILE*");
	if (fh == NULL) {
		luaL_error (L, "%s: not a file", funcname);
		return 0;
	} else if (*fh == NULL) {
		luaL_error (L, "%s: closed file", funcname);
		return 0;
	} else
		return *fh;
}