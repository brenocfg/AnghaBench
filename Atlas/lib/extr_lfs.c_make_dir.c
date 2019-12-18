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
typedef  void* mode_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int _mkdir (char const*) ; 
 int /*<<< orphan*/  errno ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int mkdir (char const*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* umask (void*) ; 

__attribute__((used)) static int make_dir (lua_State *L) {
	const char *path = luaL_checkstring (L, 1);
	int fail;
#ifdef _WIN32
	int oldmask = umask (0);
	fail = _mkdir (path);
#else
	mode_t oldmask = umask( (mode_t)0 );
	fail =  mkdir (path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP |
	                     S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH );
#endif
	if (fail) {
		lua_pushnil (L);
        lua_pushfstring (L, "%s", strerror(errno));
		return 2;
	}
	umask (oldmask);
	lua_pushboolean (L, 1);
	return 1;
}