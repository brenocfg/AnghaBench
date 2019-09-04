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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GdkEventExpose ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_image_surface_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_image_surface_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_object_get_data (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gdk_cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_size_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
pgd_image_view_drawing_area_expose (GtkWidget      *area,
				    GdkEventExpose *event,
				    GtkWidget      *image_view)
{
	cairo_t         *cr;
	cairo_surface_t *image;

	image = g_object_get_data (G_OBJECT (image_view), "image-surface");
	if (!image)
		return FALSE;

	gtk_widget_set_size_request (area,
				     cairo_image_surface_get_width (image),
				     cairo_image_surface_get_height (image));
	
	cr = gdk_cairo_create (gtk_widget_get_window (area));
	cairo_set_source_surface (cr, image, 0, 0);
	cairo_paint (cr);
	cairo_destroy (cr);

	return TRUE;
}