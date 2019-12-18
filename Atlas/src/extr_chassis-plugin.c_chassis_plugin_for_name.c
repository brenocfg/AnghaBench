#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t gsize ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ chassis_plugin ;
struct TYPE_8__ {TYPE_1__* modules; } ;
typedef  TYPE_3__ chassis ;
struct TYPE_6__ {size_t len; TYPE_2__** pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

chassis_plugin* chassis_plugin_for_name(chassis *chas, gchar* plugin_name) {
    gsize i;

    if (!chas || !plugin_name) return NULL;

    /* search for a plugin named plugin_name */
	for (i = 0; i < chas->modules->len; i++) {
		chassis_plugin *p = chas->modules->pdata[i];
        if (!strcmp(p->name, plugin_name)) {
            return p;
        }
	}
    return NULL;
    
}