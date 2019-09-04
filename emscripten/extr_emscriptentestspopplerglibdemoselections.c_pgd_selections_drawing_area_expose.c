#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_3__ {scalar_t__ selection_surface; scalar_t__ surface; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GdkEventExpose ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdk_cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
pgd_selections_drawing_area_expose (GtkWidget         *area,
				    GdkEventExpose    *event,
				    PgdSelectionsDemo *demo)
{
	cairo_t *cr;

	if (!demo->surface)
		return FALSE;

	gdk_window_clear (gtk_widget_get_window (area));

	cr = gdk_cairo_create (gtk_widget_get_window (area));

	cairo_save (cr);
	cairo_set_source_surface (cr, demo->surface, 0, 0);
	cairo_paint (cr);
	cairo_restore (cr);

	if (demo->selection_surface) {
		cairo_set_source_surface (cr, demo->selection_surface, 0, 0);
		cairo_paint (cr);
	}

	cairo_destroy (cr);

	return TRUE;
}