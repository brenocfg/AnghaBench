#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guchar ;
typedef  int gint ;
struct TYPE_4__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_1__ PopplerColor ;
typedef  int /*<<< orphan*/  PopplerAnnot ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_COLORSPACE_RGB ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int gdk_pixbuf_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_get_pixels (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_rowstride (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__* poppler_annot_get_color (int /*<<< orphan*/ *) ; 

GdkPixbuf *
get_annot_color (PopplerAnnot *poppler_annot)
{
    PopplerColor *poppler_color;

    if ((poppler_color = poppler_annot_get_color (poppler_annot))) {
        GdkPixbuf *pixbuf;
	gint rowstride, num, x;
	guchar *pixels;

        pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB,
                                 FALSE, 8,
                                 64, 16);

	rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixels = gdk_pixbuf_get_pixels (pixbuf);
            
	num = gdk_pixbuf_get_width (pixbuf) *
                gdk_pixbuf_get_height (pixbuf);

	for (x = 0; x < num; x++) {
          pixels[0] = poppler_color->red;
	  pixels[1] = poppler_color->green;
	  pixels[2] = poppler_color->blue;
	  pixels += 3;
	}

        g_free (poppler_color);

        return pixbuf;
    }

    return NULL;
}