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
struct TYPE_5__ {TYPE_1__* preview; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_4__ {int render_width; int render_height; } ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_CLEAR ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_translate (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  gdk_cairo_set_source_pixbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gdk_pixbuf_get_height (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _draw_pixbuf(signal_user_data_t * ud, cairo_t *cr, GdkPixbuf *pix)
{
    int pix_width, pix_height, hoff, voff;

    cairo_save(cr);
    cairo_rectangle(cr, 0, 0, ud->preview->render_width,
                              ud->preview->render_height);
    cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
    cairo_fill(cr);
    cairo_restore(cr);

    pix_width  = gdk_pixbuf_get_width(pix);
    pix_height = gdk_pixbuf_get_height(pix);
    hoff = MAX((ud->preview->render_width  - pix_width)  / 2, 0);
    voff = MAX((ud->preview->render_height - pix_height) / 2, 0);
    if (voff > 0 || hoff > 0)
    {
        cairo_translate(cr, hoff, voff);
    }

    gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
    cairo_paint(cr);
}