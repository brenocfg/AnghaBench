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
typedef  int guchar ;
typedef  int gint ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
typedef  scalar_t__ cairo_format_t ;
typedef  int /*<<< orphan*/  GtkImage ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 scalar_t__ CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/  GDK_COLORSPACE_RGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create_for_data (int*,scalar_t__,int,int,int) ; 
 scalar_t__ cairo_image_surface_get_format (int /*<<< orphan*/ *) ; 
 int cairo_image_surface_get_height (int /*<<< orphan*/ *) ; 
 int cairo_image_surface_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_mask_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_n_channels (int /*<<< orphan*/ *) ; 
 int* gdk_pixbuf_get_pixels (int /*<<< orphan*/ *) ; 
 int gdk_pixbuf_get_rowstride (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  gtk_image_set_from_pixbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
image_set_from_surface (GtkImage        *gtkimage,
			cairo_surface_t *surface)
{
	GdkPixbuf       *pixbuf;
	cairo_surface_t *image;
	cairo_t         *cr;
	gboolean         has_alpha;
	gint             width, height;
	cairo_format_t   surface_format;
	gint             pixbuf_n_channels;
	gint             pixbuf_rowstride;
	guchar          *pixbuf_pixels;
	gint             x, y;

	width = cairo_image_surface_get_width (surface);
	height = cairo_image_surface_get_height (surface);
	
	surface_format = cairo_image_surface_get_format (surface);
	has_alpha = (surface_format == CAIRO_FORMAT_ARGB32);

	pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB,
				 TRUE, 8,
				 width, height);
	pixbuf_n_channels = gdk_pixbuf_get_n_channels (pixbuf);
	pixbuf_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
	pixbuf_pixels = gdk_pixbuf_get_pixels (pixbuf);

	image = cairo_image_surface_create_for_data (pixbuf_pixels,
						     surface_format,
						     width, height,
						     pixbuf_rowstride);
	cr = cairo_create (image);
	cairo_set_source_surface (cr, surface, 0, 0);

	if (has_alpha)
		cairo_mask_surface (cr, surface, 0, 0);
	else
		cairo_paint (cr);

	cairo_destroy (cr);
	cairo_surface_destroy (image);

	for (y = 0; y < height; y++) {
		guchar *p = pixbuf_pixels + y * pixbuf_rowstride;

		for (x = 0; x < width; x++) {
			guchar tmp;
			
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
			tmp = p[0];
			p[0] = p[2];
			p[2] = tmp;
			p[3] = (has_alpha) ? p[3] : 0xff;
#else
			tmp = p[0];
			p[0] = (has_alpha) ? p[3] : 0xff;
			p[3] = p[2];
			p[2] = p[1];
			p[1] = tmp;
#endif			
			p += pixbuf_n_channels;
		}
	}

	gtk_image_set_from_pixbuf (gtkimage, pixbuf);
	g_object_unref (pixbuf);
}