#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t gint ;
struct TYPE_3__ {int /*<<< orphan*/ * (* create_widget ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PopplerDocument ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_NOTEBOOK (int /*<<< orphan*/ *) ; 
 size_t G_N_ELEMENTS (TYPE_1__*) ; 
 TYPE_1__* demo_list ; 
 int /*<<< orphan*/  gtk_notebook_append_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_notebook_new () ; 
 int /*<<< orphan*/  gtk_notebook_set_show_border (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_notebook_set_show_tabs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GtkWidget *
pdg_demo_notebook_create (PopplerDocument *document)
{
	GtkWidget *notebook;
	gint       i;

	notebook = gtk_notebook_new ();
	gtk_notebook_set_show_tabs (GTK_NOTEBOOK (notebook), FALSE);
	gtk_notebook_set_show_border (GTK_NOTEBOOK (notebook), FALSE);
	
	for (i = 0; i < G_N_ELEMENTS (demo_list); i++) {
		GtkWidget *demo_widget;

		demo_widget = demo_list[i].create_widget (document);
		gtk_notebook_append_page (GTK_NOTEBOOK (notebook), demo_widget, NULL);
		gtk_widget_show (demo_widget);
	}

	return notebook;
}