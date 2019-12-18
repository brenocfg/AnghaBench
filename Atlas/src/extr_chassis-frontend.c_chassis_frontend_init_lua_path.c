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
 int /*<<< orphan*/  TRUE ; 
 int chassis_frontend_init_lua_paths (char const*,char const*,char**,int /*<<< orphan*/ ) ; 

int chassis_frontend_init_lua_path(const char *set_path, const char *base_dir, char **lua_subdirs) {
	return chassis_frontend_init_lua_paths(set_path, base_dir, lua_subdirs, TRUE);
}