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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_6__ {scalar_t__ magic; int /*<<< orphan*/  (* new_stats ) () ;int /*<<< orphan*/  stats; int /*<<< orphan*/  version; scalar_t__ name; int /*<<< orphan*/  (* init ) () ;int /*<<< orphan*/  config; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ chassis_plugin ;

/* Variables and functions */
 scalar_t__ CHASSIS_PLUGIN_MAGIC ; 
 int /*<<< orphan*/  G_MODULE_BIND_LOCAL ; 
 int /*<<< orphan*/  chassis_plugin_free (TYPE_1__*) ; 
 TYPE_1__* chassis_plugin_new () ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/  const*,...) ; 
 int /*<<< orphan*/  g_module_error () ; 
 int /*<<< orphan*/  g_module_open (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_module_symbol (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_strdup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

chassis_plugin *chassis_plugin_load(const gchar *name) {
	int (*plugin_init)(chassis_plugin *p);
	chassis_plugin *p = chassis_plugin_new();

	p->module = g_module_open(name, G_MODULE_BIND_LOCAL);

	if (!p->module) {
		g_critical("loading module '%s' failed: %s", name, g_module_error());

		chassis_plugin_free(p);

		return NULL;
	}

	/* each module has to have a plugin_init function */
	if (!g_module_symbol(p->module, "plugin_init", (gpointer) &plugin_init)) {
		g_critical("module '%s' doesn't have a init-function: %s", name, g_module_error());
		chassis_plugin_free(p);
		return NULL;
	}

	if (0 != plugin_init(p)) {
		g_critical("init-function for module '%s' failed", name);
		chassis_plugin_free(p);
		return NULL;
	}

	if (p->magic != CHASSIS_PLUGIN_MAGIC) {
		g_critical("plugin '%s' doesn't match the current plugin interface (plugin is %lx, chassis is %lx)", name, p->magic, CHASSIS_PLUGIN_MAGIC);
		chassis_plugin_free(p);
		return NULL;
	}

	if (p->init) {
		p->config = p->init();
	}

	/* if the plugins haven't set p->name provide our own name */
	if (!p->name) p->name = g_strdup(name);
	/* set dummy version number if the plugin doesn't provide a real one */
	if (!p->version) {
		g_critical("plugin '%s' doesn't set a version number, refusing to load this plugin", name);
		chassis_plugin_free(p);
		return NULL;
	}
	
	if (p->new_stats) {
		p->stats = p->new_stats();
	}

	return p;
}