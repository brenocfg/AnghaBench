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

/* Variables and functions */
 char* g_build_filename (char const*,char*,char const*,char*,char*,int /*<<< orphan*/ *) ; 

char *chassis_frontend_get_default_lua_path(const char *base_dir, const char *prg_name) {
	return g_build_filename(base_dir, "lib", prg_name, "lua", "?.lua", NULL);
}