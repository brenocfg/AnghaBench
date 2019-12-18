#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  combo; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PerMouseNames ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* YUI_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_get_double (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_hscale_new_with_range (int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/  gtk_range_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_vseparator_new () ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  mouse_speed_change ; 
 int /*<<< orphan*/  mousepercores ; 
 int /*<<< orphan*/  percore_changed ; 
 int /*<<< orphan*/ * yui_input_entry_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_range_new (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pertype_display_mouse(GtkWidget * box)
{
   GtkWidget * scale;
   GtkWidget * table5;
   GtkWidget * box_percore = gtk_vbox_new(FALSE, 10);
   GtkWidget * select_percore = yui_range_new(keyfile, "General", "MousePerCore", mousepercores);
   GList * entrylist = NULL;

   gtk_container_set_border_width(GTK_CONTAINER(select_percore), 0);
   gtk_container_set_border_width(GTK_CONTAINER(box_percore), 10);
   gtk_box_pack_start(GTK_BOX (box_percore), select_percore, FALSE, FALSE, 0);

   scale = gtk_hscale_new_with_range(0, 10, 0.1);
   gtk_range_set_value(GTK_RANGE(scale), g_key_file_get_double(keyfile, "General", "MouseSpeed", NULL));
   g_signal_connect(scale, "value-changed", G_CALLBACK(mouse_speed_change), NULL);
   gtk_box_pack_start(GTK_BOX (box_percore), scale, FALSE, FALSE, 0);

   gtk_box_pack_start (GTK_BOX (box), box_percore, TRUE, TRUE, 0);

   gtk_box_pack_start (GTK_BOX (box), gtk_vseparator_new(), TRUE, TRUE, 0);

   table5 = yui_input_entry_new(keyfile, "Mouse", PerMouseNames);
   entrylist = g_list_append(entrylist, table5);
   gtk_container_set_border_width(GTK_CONTAINER(table5), 10);
   gtk_box_pack_start (GTK_BOX (box), table5, TRUE, TRUE, 0);

   g_signal_connect(GTK_COMBO_BOX(YUI_RANGE(select_percore)->combo), "changed", G_CALLBACK(percore_changed), entrylist);
   gtk_widget_show_all(box);
}