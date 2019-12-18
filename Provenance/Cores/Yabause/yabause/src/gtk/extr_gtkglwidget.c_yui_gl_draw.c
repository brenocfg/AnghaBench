#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guchar ;
struct TYPE_10__ {int pixels_width; int pixels_height; int pixels_rowstride; int is_init; } ;
typedef  TYPE_2__ YuiGl ;
struct TYPE_12__ {int /*<<< orphan*/  (* GetGlSize ) (int*,int*) ;} ;
struct TYPE_9__ {int width; int height; } ;
struct TYPE_11__ {int /*<<< orphan*/  window; TYPE_1__ allocation; } ;
typedef  int /*<<< orphan*/  GdkPixbuf ;
typedef  int /*<<< orphan*/  GdkGLDrawable ;
typedef  int /*<<< orphan*/  GdkGLContext ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_COLORSPACE_RGB ; 
 int /*<<< orphan*/  GDK_INTERP_NEAREST ; 
 int /*<<< orphan*/  GDK_RGB_DITHER_NONE ; 
 TYPE_4__* GTK_WIDGET (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__* VIDCore ; 
 int X_NOSCALE ; 
 int Y_NOSCALE ; 
 int /*<<< orphan*/ * dispbuffer ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_print (char*) ; 
 int /*<<< orphan*/  gdk_draw_pixbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_gl_drawable_make_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_gl_drawable_swap_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_new_from_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_scale_simple (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_gl_context (TYPE_4__*) ; 
 int /*<<< orphan*/ * gtk_widget_get_gl_drawable (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int*,int*) ; 

void yui_gl_draw(YuiGl * glxarea) {
#ifdef HAVE_LIBGTKGLEXT
	GdkGLContext *glcontext = gtk_widget_get_gl_context (GTK_WIDGET(glxarea));
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (GTK_WIDGET(glxarea));

	if (!gdk_gl_drawable_make_current (gldrawable, glcontext)) {
		g_print("Cannot set gl drawable current\n");
		return;
	}

	gdk_gl_drawable_swap_buffers(gldrawable);
#else
	int buf_width, buf_height;
	GdkPixbuf * pixbuf, * scaledpixbuf;

	VIDCore->GetGlSize( &buf_width, &buf_height );
	glxarea->pixels_width = GTK_WIDGET(glxarea)->allocation.width;
	glxarea->pixels_height = GTK_WIDGET(glxarea)->allocation.height;
	glxarea->pixels_rowstride = glxarea->pixels_width * 4;
	glxarea->pixels_rowstride += (glxarea->pixels_rowstride % 4)? (4 - (glxarea->pixels_rowstride % 4)): 0;

	if (dispbuffer == NULL) return;

	pixbuf = gdk_pixbuf_new_from_data((const guchar *) dispbuffer, GDK_COLORSPACE_RGB, TRUE, 8,
			buf_width, buf_height, buf_width*4, NULL, NULL);

	if (( glxarea->pixels_width < buf_width + X_NOSCALE )&&( glxarea->pixels_height < buf_height + Y_NOSCALE )) {

	  gdk_draw_pixbuf(GTK_WIDGET(glxarea)->window, NULL, pixbuf, 0, 0,
			  (glxarea->pixels_width-buf_width)/2, (glxarea->pixels_height-buf_height)/2,
			  buf_width, buf_height, GDK_RGB_DITHER_NONE, 0, 0);
	} else {

	  scaledpixbuf = gdk_pixbuf_scale_simple(pixbuf, 
						 glxarea->pixels_width, glxarea->pixels_height, GDK_INTERP_NEAREST );
	  gdk_draw_pixbuf(GTK_WIDGET(glxarea)->window, NULL, 
			  scaledpixbuf, 0, 0, 0, 0, glxarea->pixels_width, glxarea->pixels_height, 
			  GDK_RGB_DITHER_NONE, 0, 0);
	  g_object_unref(scaledpixbuf);
	}
	g_object_unref(pixbuf);
#endif
	glxarea->is_init = 1;
}