#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
struct TYPE_9__ {int /*<<< orphan*/  config; int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ chassis_plugin ;
struct TYPE_10__ {int /*<<< orphan*/  backends; int /*<<< orphan*/  sc; int /*<<< orphan*/  shutdown_hooks; struct TYPE_10__* event_hdr_version; scalar_t__ event_base; struct TYPE_10__* instance_name; TYPE_3__* threads; scalar_t__ stats; struct TYPE_10__* user; struct TYPE_10__* log_path; struct TYPE_10__* base_dir; TYPE_3__* modules; } ;
typedef  TYPE_2__ chassis ;
struct TYPE_11__ {size_t len; TYPE_1__** pdata; } ;
typedef  TYPE_3__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chassis_event_thread_free (TYPE_1__*) ; 
 int /*<<< orphan*/  chassis_plugin_free (TYPE_1__*) ; 
 int /*<<< orphan*/  chassis_shutdown_hooks_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chassis_shutdown_hooks_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chassis_stats_free (scalar_t__) ; 
 int /*<<< orphan*/  chassis_timestamps_global_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_free (scalar_t__) ; 
 char* event_get_version () ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  g_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_scope_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_backends_free (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void chassis_free(chassis *chas) {
	guint i;
#ifdef HAVE_EVENT_BASE_FREE
	const char *version;
#endif

	if (!chas) return;

	/* call the destructor for all plugins */
	for (i = 0; i < chas->modules->len; i++) {
		chassis_plugin *p = chas->modules->pdata[i];

		g_assert(p->destroy);
		p->destroy(p->config);
	}
	
	chassis_shutdown_hooks_call(chas->shutdown_hooks); /* cleanup the global 3rd party stuff before we unload the modules */

	for (i = 0; i < chas->modules->len; i++) {
		chassis_plugin *p = chas->modules->pdata[i];

		chassis_plugin_free(p);
	}
	
	g_ptr_array_free(chas->modules, TRUE);

	if (chas->base_dir) g_free(chas->base_dir);
	if (chas->log_path) g_free(chas->log_path);
	if (chas->user) g_free(chas->user);
	
	if (chas->stats) chassis_stats_free(chas->stats);

	chassis_timestamps_global_free(NULL);

	GPtrArray *threads = chas->threads;
	if (threads) {
		for (i = 0; i < threads->len; ++i) {
			chassis_event_thread_free(threads->pdata[i]);
		}

		g_ptr_array_free(threads, TRUE);
	}

	if (chas->instance_name) g_free(chas->instance_name);

#ifdef HAVE_EVENT_BASE_FREE
	/* only recent versions have this call */

	version = event_get_version();

	/* libevent < 1.3e doesn't cleanup its own fds from the event-queue in signal_init()
	 * calling event_base_free() would cause a assert() on shutdown
	 */
	if (version && (strcmp(version, "1.3e") >= 0)) {
		if (chas->event_base) event_base_free(chas->event_base);
	}
#endif
	g_free(chas->event_hdr_version);

	chassis_shutdown_hooks_free(chas->shutdown_hooks);

	lua_scope_free(chas->sc);

	network_backends_free(chas->backends);

	g_free(chas);
}