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
typedef  int /*<<< orphan*/  cairo_surface_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ cairo_surface_destroy ; 
 int /*<<< orphan*/  g_object_set_data_full (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_image_view_set_image (GtkWidget       *image_view,
			  cairo_surface_t *image)
{
	g_object_set_data_full (G_OBJECT (image_view), "image-surface",
				image,
				(GDestroyNotify)cairo_surface_destroy);
	gtk_widget_queue_draw (image_view);
}