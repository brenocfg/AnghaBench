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
 int /*<<< orphan*/  LUA_GCRESTART ; 
 int /*<<< orphan*/  LUA_GCSTOP ; 
 scalar_t__ LUA_OK ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int collectargs (char**,int*) ; 
 int /*<<< orphan*/  dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dotty (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_luainit (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_script (int /*<<< orphan*/ *,char**,int) ; 
 size_t has_E ; 
 size_t has_e ; 
 size_t has_i ; 
 size_t has_v ; 
 int /*<<< orphan*/  luaL_checkversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lua_stdin_is_tty () ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int num_has ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 int /*<<< orphan*/  print_version () ; 
 char* progname ; 
 int /*<<< orphan*/  runargs (int /*<<< orphan*/ *,char**,int) ; 

__attribute__((used)) static int pmain (lua_State *L) {
  int argc = (int)lua_tointeger(L, 1);
  char **argv = (char **)lua_touserdata(L, 2);
  int script;
  int args[num_has];
  args[has_i] = args[has_v] = args[has_e] = args[has_E] = 0;
  if (argv[0] && argv[0][0]) progname = argv[0];
  script = collectargs(argv, args);
  if (script < 0) {  /* invalid arg? */
    print_usage(argv[-script]);
    return 0;
  }
  if (args[has_v]) print_version();
  if (args[has_E]) {  /* option '-E'? */
    lua_pushboolean(L, 1);  /* signal for libraries to ignore env. vars. */
    lua_setfield(L, LUA_REGISTRYINDEX, "LUA_NOENV");
  }
  /* open standard libraries */
  luaL_checkversion(L);
  lua_gc(L, LUA_GCSTOP, 0);  /* stop collector during initialization */
  luaL_openlibs(L);  /* open libraries */
  lua_gc(L, LUA_GCRESTART, 0);
  if (!args[has_E] && handle_luainit(L) != LUA_OK)
    return 0;  /* error running LUA_INIT */
  /* execute arguments -e and -l */
  if (!runargs(L, argv, (script > 0) ? script : argc)) return 0;
  /* execute main script (if there is one) */
  if (script && handle_script(L, argv, script) != LUA_OK) return 0;
  if (args[has_i])  /* -i option? */
    dotty(L);
  else if (script == 0 && !args[has_e] && !args[has_v]) {  /* no arguments? */
    if (lua_stdin_is_tty()) {
      print_version();
      dotty(L);
    }
    else dofile(L, NULL);  /* executes stdin as a file */
  }
  lua_pushboolean(L, 1);  /* signal no errors */
  return 1;
}