#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  scalar_t__ gboolean ;
struct TYPE_6__ {scalar_t__ len; char const* str; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  C (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  G_STRLOC ; 
 char* LUA_CPATH ; 
 char* LUA_PATH ; 
 int /*<<< orphan*/  LUA_PATHSEP ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * chassis_frontend_get_default_lua_cpath (char const*,char const*) ; 
 int /*<<< orphan*/ * chassis_frontend_get_default_lua_path (char const*,char const*) ; 
 scalar_t__ chassis_frontend_lua_setenv (char const*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_getenv (char const*) ; 
 int /*<<< orphan*/  g_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_append_len (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_free (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* g_string_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chassis_frontend_init_lua_paths(const char *set_path,
		const char *base_dir, char **lua_subdirs,
		gboolean is_lua_path) {
	const char *env_var = is_lua_path ? LUA_PATH : LUA_CPATH;
	int ret = 0;

	if (set_path) {
		if (0 != chassis_frontend_lua_setenv(env_var, set_path)) {
			g_critical("%s: setting %s = %s failed: %s", G_STRLOC,
					env_var, set_path,
					g_strerror(errno));
			ret = -1;
		}
	} else if (!g_getenv(env_var)) {
		GString *lua_path = g_string_new(NULL);
		guint i;
		gboolean all_in_one_folder = FALSE;

#ifdef _WIN32
		/**
		 * call the get_default_lua_cpath() only once on win32 as it has
		 * all the lua-module-DLLs in one folder
		 */
		if (!is_lua_path) all_in_one_folder = TRUE;
#endif

		/* build a path for each sub_name */
		for (i = 0; (all_in_one_folder && i == 0) || (!all_in_one_folder && lua_subdirs[i] != NULL); i++) {
			gchar *path;
			const char *sub_name = all_in_one_folder ? NULL : lua_subdirs[i];

			if (is_lua_path) {
				path = chassis_frontend_get_default_lua_path(base_dir, sub_name);
			} else {
				path = chassis_frontend_get_default_lua_cpath(base_dir, sub_name);
			}

			if (lua_path->len > 0) {
				g_string_append_len(lua_path, C(LUA_PATHSEP));
			}

			g_string_append(lua_path, path);

			g_free(path);
		}

		if (lua_path->len) {
			if (chassis_frontend_lua_setenv(env_var, lua_path->str)) {
				g_critical("%s: setting %s = %s failed: %s", G_STRLOC,
						env_var, lua_path->str,
						g_strerror(errno));
				ret = -1;
			}
		}
		g_string_free(lua_path, TRUE);
	}

	return 0;
}