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
typedef  int /*<<< orphan*/  guint8 ;
typedef  int gint ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 int gdk_pixbuf_get_n_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_get_pixels (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_rowstride (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
horz_line(
    GdkPixbuf * pb,
    guint8 r,
    guint8 g,
    guint8 b,
    gint x,
    gint y,
    gint len,
    gint width)
{
    guint8 *pixels = gdk_pixbuf_get_pixels (pb);
    guint8 *dst;
    gint ii, jj;
    gint channels = gdk_pixbuf_get_n_channels (pb);
    gint stride = gdk_pixbuf_get_rowstride (pb);

    for (jj = 0; jj < width; jj++)
    {
        dst = pixels + (y+jj) * stride + x * channels;
        for (ii = 0; ii < len; ii++)
        {
            dst[0] = r;
            dst[1] = g;
            dst[2] = b;
            dst += channels;
        }
    }
}