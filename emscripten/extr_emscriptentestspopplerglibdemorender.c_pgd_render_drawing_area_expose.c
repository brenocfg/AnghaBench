#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_5__ {int /*<<< orphan*/ * fg_gc; } ;
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  pixbuf; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ PgdRenderDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GdkEventExpose ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_RGB_DITHER_NORMAL ; 
 size_t GTK_STATE_NORMAL ; 
 scalar_t__ PGD_RENDER_CAIRO ; 
 scalar_t__ PGD_RENDER_PIXBUF ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/ * gdk_cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_draw_pixbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_pixbuf_get_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_pixbuf_get_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_clear (int /*<<< orphan*/ ) ; 
 TYPE_3__* gtk_widget_get_style (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
pgd_render_drawing_area_expose (GtkWidget      *area,
				GdkEventExpose *event,
				PgdRenderDemo  *demo)
{
	if (demo->mode == PGD_RENDER_CAIRO && !demo->surface)
		return FALSE;

	if (demo->mode == PGD_RENDER_PIXBUF && !demo->pixbuf)
		return FALSE;

	gdk_window_clear (gtk_widget_get_window (area));

	if (demo->mode == PGD_RENDER_CAIRO) {
		cairo_t *cr;

		cr = gdk_cairo_create (gtk_widget_get_window (area));
		cairo_set_source_surface (cr, demo->surface, 0, 0);
		cairo_paint (cr);
		cairo_destroy (cr);
	} else if (demo->mode == PGD_RENDER_PIXBUF) {
		gdk_draw_pixbuf (gtk_widget_get_window (area),
				 gtk_widget_get_style(area)->fg_gc[GTK_STATE_NORMAL],
				 demo->pixbuf,
				 0, 0,
				 0, 0,
				 gdk_pixbuf_get_width (demo->pixbuf),
				 gdk_pixbuf_get_height (demo->pixbuf),
				 GDK_RGB_DITHER_NORMAL,
				 0, 0);
	} else {
		g_assert_not_reached ();
	}

	return TRUE;
}