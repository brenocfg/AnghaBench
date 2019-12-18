#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  (* Resize ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ is_init; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GdkGLDrawable ;
typedef  int /*<<< orphan*/  GdkGLContext ;
typedef  TYPE_1__ GdkEventConfigure ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_4__* VIDCore ; 
 TYPE_3__* YUI_GL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_gl_drawable_gl_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_gl_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_widget_get_gl_drawable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean yui_gl_resize(GtkWidget *w,GdkEventConfigure *event, gpointer data) {
#ifdef HAVE_LIBGTKGLEXT
	GdkGLContext *glcontext = gtk_widget_get_gl_context (w);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (w);

	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
		return FALSE;

	glViewport(0, 0, event->width, event->height);
        if ( YUI_GL(w)->is_init ) VIDCore->Resize(event->width, event->height, FALSE );
#endif
	return FALSE;
}