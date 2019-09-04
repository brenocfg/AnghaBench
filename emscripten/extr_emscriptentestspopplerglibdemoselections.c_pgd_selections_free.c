#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ selections_idle; int /*<<< orphan*/ * surface; int /*<<< orphan*/ * page; int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_source_remove (scalar_t__) ; 
 int /*<<< orphan*/  pgd_selections_clear_selections (TYPE_1__*) ; 

__attribute__((used)) static void
pgd_selections_free (PgdSelectionsDemo *demo)
{
	if (!demo)
		return;

	if (demo->selections_idle > 0) {
		g_source_remove (demo->selections_idle);
		demo->selections_idle = 0;
	}

	if (demo->doc) {
		g_object_unref (demo->doc);
		demo->doc = NULL;
	}

	if (demo->page) {
		g_object_unref (demo->page);
		demo->page = NULL;
	}

	if (demo->surface) {
		cairo_surface_destroy (demo->surface);
		demo->surface = NULL;
	}

	pgd_selections_clear_selections (demo);

	g_free (demo);
}