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
 int /*<<< orphan*/  PACKAGE ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ ,...) ; 

int chassis_frontend_init_plugin_dir(char **_plugin_dir, const char *base_dir) {
	char *plugin_dir = *_plugin_dir;

	if (plugin_dir) return 0;

#ifdef WIN32
	plugin_dir = g_build_filename(base_dir, "bin", NULL);
#else
	plugin_dir = g_build_filename(base_dir, "lib", PACKAGE, "plugins", NULL);
#endif

	*_plugin_dir = plugin_dir;

	return 0;
}