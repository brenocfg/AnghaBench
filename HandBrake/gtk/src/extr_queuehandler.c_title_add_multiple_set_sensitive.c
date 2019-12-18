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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  PangoAttribute ;
typedef  int /*<<< orphan*/  PangoAttrList ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * default_title_attrs ; 
 int /*<<< orphan*/ * find_widget (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_label_set_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_has_tooltip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pango_attr_background_new (int,int,int) ; 
 int /*<<< orphan*/  pango_attr_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_attr_list_new () ; 

__attribute__((used)) static void
title_add_multiple_set_sensitive(GtkWidget *row, gboolean sensitive)
{
    GtkWidget *widget;
    widget = find_widget(row, "title_selected");
    gtk_widget_set_sensitive(widget, sensitive);

    widget = find_widget(row, "title_label");
    if (!sensitive)
    {
        PangoAttrList *pal;
        PangoAttribute *bg;
        bg = pango_attr_background_new(0xFFFF, 0xFFFF, 0xA000);
        pal = pango_attr_list_new();
        pango_attr_list_insert(pal, bg);
        gtk_label_set_attributes(GTK_LABEL(widget), pal);
        gtk_widget_set_has_tooltip(widget, TRUE);
    }
    else
    {
        gtk_label_set_attributes(GTK_LABEL(widget), default_title_attrs);
        gtk_widget_set_has_tooltip(widget, FALSE);
    }
}