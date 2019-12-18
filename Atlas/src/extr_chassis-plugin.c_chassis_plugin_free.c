#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* version; scalar_t__ module; struct TYPE_4__* name; struct TYPE_4__* option_grp_name; } ;
typedef  TYPE_1__ chassis_plugin ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_module_close (scalar_t__) ; 

void chassis_plugin_free(chassis_plugin *p) {
	if (p->option_grp_name) g_free(p->option_grp_name);
	if (p->name) g_free(p->name);
	if (p->module) g_module_close(p->module);
	if (p->version) g_free(p->version);

	g_free(p);
}