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
typedef  int gint ;
typedef  int gdouble ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_4__ {int width; int height; int x; int y; } ;
struct TYPE_5__ {int rotate; int scale; scalar_t__ mode; int /*<<< orphan*/  darea; int /*<<< orphan*/  timer_label; scalar_t__ printing; int /*<<< orphan*/ * surface; TYPE_1__ slice; int /*<<< orphan*/ * pixbuf; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_2__ PgdRenderDemo ;
typedef  int /*<<< orphan*/  GtkButton ;
typedef  int /*<<< orphan*/  GTimer ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_DEST_OVER ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 double G_PI ; 
 scalar_t__ PGD_RENDER_CAIRO ; 
 scalar_t__ PGD_RENDER_PIXBUF ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_rotate (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_rgb (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_translate (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timer_elapsed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_timer_new () ; 
 int /*<<< orphan*/  g_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_size_request (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_get_size (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  poppler_page_render (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_render_for_printing (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_render_start (GtkButton     *button,
		  PgdRenderDemo *demo)
{
	PopplerPage *page;
	gdouble      page_width, page_height;
	gdouble      width, height;
	gint         x, y;
	gchar       *str;
	GTimer      *timer;

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	if (demo->surface)
		cairo_surface_destroy (demo->surface);
	demo->surface = NULL;

	if (demo->pixbuf)
		g_object_unref (demo->pixbuf);
	demo->pixbuf = NULL;
	
	poppler_page_get_size (page, &page_width, &page_height);

	if (demo->rotate == 0 || demo->rotate == 180) {
		width = demo->slice.width * demo->scale;
		height = demo->slice.height * demo->scale;
		x = demo->slice.x * demo->scale;
		y = demo->slice.y * demo->scale;
	} else {
		width = demo->slice.height * demo->scale;
		height = demo->slice.width * demo->scale;
		x = demo->slice.y * demo->scale;
		y = demo->slice.x * demo->scale;
	}

	if (demo->mode == PGD_RENDER_CAIRO) {
		cairo_t *cr;

		timer = g_timer_new ();
		demo->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32,
							    width, height);
		cr = cairo_create (demo->surface);

		cairo_save (cr);
		switch (demo->rotate) {
		case 90:
			cairo_translate (cr, x + width, -y);
			break;
		case 180:
			cairo_translate (cr, x + width, y + height);
			break;
		case 270:
			cairo_translate (cr, -x, y + height);
			break;
		default:
			cairo_translate (cr, -x, -y);
		}

		if (demo->scale != 1.0)
			cairo_scale (cr, demo->scale, demo->scale);
		
		if (demo->rotate != 0)
			cairo_rotate (cr, demo->rotate * G_PI / 180.0);

		if (demo->printing)
			poppler_page_render_for_printing (page, cr);
		else
			poppler_page_render (page, cr);
		cairo_restore (cr);

		cairo_set_operator (cr, CAIRO_OPERATOR_DEST_OVER);
		cairo_set_source_rgb (cr, 1., 1., 1.);
		cairo_paint (cr);

		g_timer_stop (timer);
		
		cairo_destroy (cr);
	} else if (demo->mode == PGD_RENDER_PIXBUF) {
#ifdef POPPLER_WITH_GDK
		timer = g_timer_new ();
		demo->pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB,
					       FALSE, 8, width, height);
		gdk_pixbuf_fill (demo->pixbuf, 0xffffff);
		if (demo->printing) {
			poppler_page_render_to_pixbuf_for_printing (page,
								    x, y,
								    width,
								    height,
								    demo->scale,
								    demo->rotate,
								    demo->pixbuf);
		} else {
			poppler_page_render_to_pixbuf (page,
						       x, y,
						       width,
						       height,
						       demo->scale,
						       demo->rotate,
						       demo->pixbuf);
		}
		g_timer_stop (timer);
#endif /* POPPLER_WITH_GDK */
	} else {
		g_assert_not_reached ();
	}

	g_object_unref (page);
	
	str = g_strdup_printf ("<i>Page rendered in %.4f seconds</i>",
			       g_timer_elapsed (timer, NULL));
	gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
	g_free (str);
	
	g_timer_destroy (timer);
	
	gtk_widget_set_size_request (demo->darea, width, height);
	gtk_widget_queue_draw (demo->darea);
}