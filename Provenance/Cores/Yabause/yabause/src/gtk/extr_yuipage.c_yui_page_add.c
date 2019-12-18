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
typedef  char gchar ;
typedef  int /*<<< orphan*/  YuiPage ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FRAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SHADOW_NONE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_frame_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_frame_set_label_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_frame_set_shadow_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_label_new (char*) ; 
 int /*<<< orphan*/  gtk_label_set_use_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

GtkWidget * yui_page_add(YuiPage * yp, const gchar * name) {
	GtkWidget * label;
	GtkWidget * frame;
	GtkWidget * box;
	gchar buffer[1024];

	frame = gtk_frame_new(NULL);
  
	gtk_box_pack_start(GTK_BOX(yp), frame, FALSE, TRUE, 0);
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_NONE);

	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(frame), box);

	sprintf(buffer, "<b>%s</b>", name);

	label = gtk_label_new(buffer);
	gtk_frame_set_label_widget(GTK_FRAME(frame), label);
	gtk_label_set_use_markup(GTK_LABEL(label), TRUE);

	return box;
}