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
typedef  int /*<<< orphan*/  gdouble ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_3__ {int /*<<< orphan*/  darea; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_1__ PgdLayersDemo ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_RGB24 ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_source_rgb (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_size_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_render (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cairo_surface_t *
pgd_layers_render_page (PgdLayersDemo *demo)
{
	cairo_t *cr;
	PopplerPage *page;
	gdouble width, height;
	cairo_surface_t *surface = NULL;

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return NULL;

	poppler_page_get_size (page, &width, &height);
	gtk_widget_set_size_request (demo->darea, width, height);
	
	surface = cairo_image_surface_create (CAIRO_FORMAT_RGB24,
					      width, height);
	cr = cairo_create (surface);

	cairo_save (cr);
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_rectangle (cr, 0, 0, width, height);
	cairo_fill (cr);
	cairo_restore (cr);

	cairo_save (cr);
	poppler_page_render (page, cr);
	cairo_restore (cr);
	
	cairo_destroy (cr);
	g_object_unref (page);

	return surface;
}