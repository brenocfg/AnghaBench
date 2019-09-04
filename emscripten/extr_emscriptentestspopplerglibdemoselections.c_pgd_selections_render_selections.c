#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int gdouble ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_10__ {int x1; int y1; int x2; int y2; } ;
struct TYPE_9__ {int x; int y; } ;
struct TYPE_8__ {int x; int y; } ;
struct TYPE_11__ {int scale; scalar_t__ selections_idle; int /*<<< orphan*/  darea; TYPE_3__ doc_area; int /*<<< orphan*/  background_color; int /*<<< orphan*/  glyph_color; int /*<<< orphan*/  style; int /*<<< orphan*/  page; int /*<<< orphan*/  selection_surface; TYPE_2__ stop; TYPE_1__ start; } ;
typedef  TYPE_3__ PopplerRectangle ;
typedef  TYPE_4__ PgdSelectionsDemo ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_image_surface_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  poppler_page_render_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
pgd_selections_render_selections (PgdSelectionsDemo *demo)
{
	PopplerRectangle doc_area;
	gdouble page_width, page_height;
	cairo_t *cr;

	if (!demo->page || demo->start.x == -1) {
		demo->selections_idle = 0;

		return FALSE;
	}

	poppler_page_get_size (demo->page, &page_width, &page_height);
	page_width *= demo->scale;
	page_height *= demo->scale;

	doc_area.x1 = demo->start.x / demo->scale;
	doc_area.y1 = demo->start.y / demo->scale;
	doc_area.x2 = demo->stop.x / demo->scale;
	doc_area.y2 = demo->stop.y / demo->scale;

	if (demo->selection_surface)
		cairo_surface_destroy (demo->selection_surface);
	demo->selection_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
							      page_width, page_height);
	cr = cairo_create (demo->selection_surface);
	if (demo->scale != 1.0)
		cairo_scale (cr, demo->scale, demo->scale);
	poppler_page_render_selection (demo->page, cr,
				       &doc_area, &demo->doc_area,
				       demo->style,
				       &demo->glyph_color,
				       &demo->background_color);
	cairo_destroy (cr);

	demo->doc_area = doc_area;
	gtk_widget_queue_draw (demo->darea);

	demo->selections_idle = 0;

	return FALSE;
}