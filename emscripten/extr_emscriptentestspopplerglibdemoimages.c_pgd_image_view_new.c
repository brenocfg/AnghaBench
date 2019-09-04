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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_drawing_area_new () ; 
 int /*<<< orphan*/  gtk_scrolled_window_add_with_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_image_view_drawing_area_expose ; 

__attribute__((used)) static GtkWidget *
pgd_image_view_new ()
{
	GtkWidget *swindow;
	GtkWidget *darea;

	swindow = gtk_scrolled_window_new (NULL, NULL);
	
	darea = gtk_drawing_area_new ();
	g_signal_connect (G_OBJECT (darea), "expose_event",
			  G_CALLBACK (pgd_image_view_drawing_area_expose),
			  (gpointer)swindow);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (swindow),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swindow),
					       darea);
	gtk_widget_show (darea);

	return swindow;
}