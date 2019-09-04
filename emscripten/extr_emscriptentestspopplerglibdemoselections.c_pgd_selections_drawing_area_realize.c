#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * base; int /*<<< orphan*/ * text; } ;
struct TYPE_5__ {int /*<<< orphan*/  bg_color_button; int /*<<< orphan*/  fg_color_button; } ;
typedef  TYPE_1__ PgdSelectionsDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_2__ GtkStyle ;

/* Variables and functions */
 int GDK_BUTTON1_MOTION_MASK ; 
 int GDK_BUTTON_PRESS_MASK ; 
 int GDK_BUTTON_RELEASE_MASK ; 
 int GDK_POINTER_MOTION_HINT_MASK ; 
 int /*<<< orphan*/  GTK_COLOR_BUTTON (int /*<<< orphan*/ ) ; 
 size_t GTK_STATE_SELECTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_color_button_set_color (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_add_events (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* gtk_widget_get_style (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_selections_drawing_area_realize (GtkWidget         *area,
				     PgdSelectionsDemo *demo)
{
	GtkStyle *style = gtk_widget_get_style (area);

	gtk_widget_add_events (area,
			       GDK_POINTER_MOTION_HINT_MASK |
			       GDK_BUTTON1_MOTION_MASK |
			       GDK_BUTTON_PRESS_MASK |
			       GDK_BUTTON_RELEASE_MASK);
	g_object_set (area, "has-tooltip", TRUE, NULL);

	gtk_color_button_set_color (GTK_COLOR_BUTTON (demo->fg_color_button),
				    &style->text[GTK_STATE_SELECTED]);
	gtk_color_button_set_color (GTK_COLOR_BUTTON (demo->bg_color_button),
				    &style->base[GTK_STATE_SELECTED]);
}