#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int gint ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  cairo_rectangle_int_t ;
struct TYPE_6__ {int x; int y; int width; int height; } ;
struct TYPE_5__ {int scale; int /*<<< orphan*/  selected_text; int /*<<< orphan*/  selected_region; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTooltip ;
typedef  TYPE_2__ GdkRectangle ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ cairo_region_contains_point (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cairo_region_get_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tooltip_set_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tooltip_set_tip_area (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static gboolean
pgd_selections_drawing_area_query_tooltip (GtkWidget         *area,
					   gint               x,
					   gint               y,
					   gboolean           keyboard_mode,
					   GtkTooltip        *tooltip,
					   PgdSelectionsDemo *demo)
{
	gboolean over_selection;

	if (!demo->selected_text)
		return FALSE;

	over_selection = cairo_region_contains_point (demo->selected_region,
                                                      x / demo->scale,
                                                      y / demo->scale);

	if (over_selection) {
		GdkRectangle selection_area;

		cairo_region_get_extents (demo->selected_region,
                                          (cairo_rectangle_int_t *)&selection_area);
		selection_area.x *= demo->scale;
		selection_area.y *= demo->scale;
		selection_area.width *= demo->scale;
		selection_area.height *= demo->scale;

		gtk_tooltip_set_text (tooltip, demo->selected_text);
		gtk_tooltip_set_tip_area (tooltip, &selection_area);

		return TRUE;
	}

	return FALSE;
}