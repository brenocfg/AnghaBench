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
typedef  double gdouble ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_5__ {double scale; int /*<<< orphan*/  darea; scalar_t__ page; int /*<<< orphan*/ * surface; int /*<<< orphan*/  page_index; int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_DEST_OVER ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_rgb (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_size_request (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  pgd_selections_clear_selections (TYPE_1__*) ; 
 int /*<<< orphan*/  pgd_selections_update_selection_region (TYPE_1__*) ; 
 scalar_t__ poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_size (scalar_t__,double*,double*) ; 
 int /*<<< orphan*/  poppler_page_render (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_selections_render (GtkButton         *button,
		       PgdSelectionsDemo *demo)
{
	gdouble  page_width, page_height;
	cairo_t *cr;

	if (!demo->page)
		demo->page = poppler_document_get_page (demo->doc, demo->page_index);

	if (!demo->page)
		return;

	pgd_selections_clear_selections (demo);
	pgd_selections_update_selection_region (demo);

	if (demo->surface)
		cairo_surface_destroy (demo->surface);
	demo->surface = NULL;

	poppler_page_get_size (demo->page, &page_width, &page_height);
	page_width *= demo->scale;
	page_height *= demo->scale;

	demo->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
						    page_width, page_height);
	cr = cairo_create (demo->surface);

	cairo_save (cr);

	if (demo->scale != 1.0)
		cairo_scale (cr, demo->scale, demo->scale);

	poppler_page_render (demo->page, cr);
	cairo_restore (cr);

	cairo_set_operator (cr, CAIRO_OPERATOR_DEST_OVER);
	cairo_set_source_rgb (cr, 1., 1., 1.);
	cairo_paint (cr);

	cairo_destroy (cr);

	gtk_widget_set_size_request (demo->darea, page_width, page_height);
	gtk_widget_queue_draw (demo->darea);
}