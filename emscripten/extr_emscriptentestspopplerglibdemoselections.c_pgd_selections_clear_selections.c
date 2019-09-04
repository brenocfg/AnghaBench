#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x; } ;
struct TYPE_5__ {int /*<<< orphan*/ * selected_region; int /*<<< orphan*/ * selected_text; int /*<<< orphan*/ * selection_region; int /*<<< orphan*/ * selection_surface; TYPE_1__ start; } ;
typedef  TYPE_2__ PgdSelectionsDemo ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_region_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_selections_clear_selections (PgdSelectionsDemo *demo)
{
	demo->start.x = -1;

	if (demo->selection_surface) {
		cairo_surface_destroy (demo->selection_surface);
		demo->selection_surface = NULL;
	}

	if (demo->selection_region) {
		cairo_region_destroy (demo->selection_region);
		demo->selection_region = NULL;
	}

	if (demo->selected_text) {
		g_free (demo->selected_text);
		demo->selected_text = NULL;
	}

	if (demo->selected_region) {
		cairo_region_destroy (demo->selected_region);
		demo->selected_region = NULL;
	}
}