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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_FRAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_SHADOW_NONE ; 
 int /*<<< orphan*/ * gtk_frame_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_frame_set_label_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_frame_set_shadow_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GtkWidget *
pgd_form_field_view_new (void)
{
	GtkWidget  *frame, *label;

	frame = gtk_frame_new (NULL);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_NONE);
	label = gtk_label_new (NULL);
	gtk_label_set_markup (GTK_LABEL (label), "<b>Form Field Properties</b>");
	gtk_frame_set_label_widget (GTK_FRAME (frame), label);
	gtk_widget_show (label);

	return frame;
}