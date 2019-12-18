#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pixels; int /*<<< orphan*/  pixels_height; int /*<<< orphan*/  pixels_width; } ;
typedef  TYPE_3__ YuiGl ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {TYPE_2__ allocation; TYPE_1__* style; int /*<<< orphan*/  window; } ;
struct TYPE_9__ {int /*<<< orphan*/ * bg_gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 TYPE_7__* GTK_WIDGET (TYPE_3__*) ; 
 size_t GTK_WIDGET_STATE (TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ dispbuffer ; 
 int /*<<< orphan*/  gdk_draw_rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDrawPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glPixelZoom (int,int) ; 
 int /*<<< orphan*/  glRasterPos2i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_gl_draw (TYPE_3__*) ; 

void yui_gl_draw_pause(YuiGl * glxarea) {
#ifdef HAVE_LIBGTKGLEXT
	if (glxarea->pixels) {
		/* The "correct" raster position would be (0, height) but it's not a
		 * valid position, so I have to use this hack... found here:
		 * http://www.opengl.org/resources/features/KilgardTechniques/oglpitfall/ */ 
		glRasterPos2i(0, 0);
		glBitmap(0, 0, 0, 0, 0, - glxarea->pixels_height, NULL);
		glPixelZoom(1, 1);
		glDrawPixels(glxarea->pixels_width, glxarea->pixels_height, GL_RGB, GL_UNSIGNED_BYTE, glxarea->pixels);
		yui_gl_draw(glxarea);
	} else {
		gdk_draw_rectangle(GTK_WIDGET(glxarea)->window, GTK_WIDGET(glxarea)->style->bg_gc[GTK_WIDGET_STATE (glxarea)],
				TRUE, 0, 0, GTK_WIDGET(glxarea)->allocation.width, GTK_WIDGET(glxarea)->allocation.height);
	}
#else
	if (dispbuffer)
		yui_gl_draw(glxarea);
#endif
}