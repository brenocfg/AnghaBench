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
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  GLIB_CHECK_VERSION (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLIB_MAJOR_VERSION ; 
 int /*<<< orphan*/  GLIB_MICRO_VERSION ; 
 int /*<<< orphan*/  GLIB_MINOR_VERSION ; 
 int /*<<< orphan*/  g_critical (char*,...) ; 
 int /*<<< orphan*/  g_mem_set_vtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_module_supported () ; 
 int /*<<< orphan*/  g_thread_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glib_check_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glib_major_version ; 
 int /*<<< orphan*/  glib_mem_profiler_table ; 
 int /*<<< orphan*/  glib_micro_version ; 
 int /*<<< orphan*/  glib_minor_version ; 

int chassis_frontend_init_glib() {
	const gchar *check_str = NULL;
#if 0
	g_mem_set_vtable(glib_mem_profiler_table);
#endif

	if (!GLIB_CHECK_VERSION(2, 6, 0)) {
		g_critical("the glib header are too old, need at least 2.6.0, got: %d.%d.%d", 
				GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

		return -1;
	}

	check_str = glib_check_version(GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

	if (check_str) {
		g_critical("%s, got: lib=%d.%d.%d, headers=%d.%d.%d", 
			check_str,
			glib_major_version, glib_minor_version, glib_micro_version,
			GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

		return -1;
	}

	if (!g_module_supported()) {
		g_critical("loading modules is not supported on this platform");
		return -1;
	}

	g_thread_init(NULL);

	return 0;
}