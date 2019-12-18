#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * options; int /*<<< orphan*/ * entry_h; int /*<<< orphan*/ * entry_w; } ;
typedef  TYPE_1__ YuiResolution ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_combo_box_append_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gtk_combo_box_new_text () ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 void* gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_width_chars (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_label_new (char*) ; 
 int /*<<< orphan*/  yui_resolution_height_changed ; 
 int /*<<< orphan*/  yui_resolution_options_changed ; 
 int /*<<< orphan*/  yui_resolution_width_changed ; 

__attribute__((used)) static void yui_resolution_init(YuiResolution * yr) {
	GtkWidget * label_w;
	GtkWidget * label_h;

	gtk_container_set_border_width (GTK_CONTAINER (yr), 10);

	label_w = gtk_label_new ("Width");
	gtk_box_pack_start(GTK_BOX(yr), label_w, TRUE, TRUE, 0);

	yr->entry_w = gtk_entry_new ();
	gtk_entry_set_width_chars(GTK_ENTRY(yr->entry_w), 8);
	gtk_box_pack_start(GTK_BOX(yr), yr->entry_w, TRUE, TRUE, 0);

	label_h = gtk_label_new ("Height");
	gtk_box_pack_start(GTK_BOX(yr), label_h, TRUE, TRUE, 0);

	yr->entry_h = gtk_entry_new ();
	gtk_entry_set_width_chars(GTK_ENTRY(yr->entry_h), 8);
	gtk_box_pack_start(GTK_BOX(yr), yr->entry_h, TRUE, TRUE, 0);

	yr->options = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(yr->options), "Window");
	gtk_combo_box_append_text(GTK_COMBO_BOX(yr->options), "Fullscreen");
	gtk_combo_box_append_text(GTK_COMBO_BOX(yr->options), "Keep ratio");
	gtk_box_pack_start(GTK_BOX(yr), yr->options, TRUE, TRUE, 0);

	g_signal_connect(yr->entry_w, "changed", G_CALLBACK(yui_resolution_width_changed), yr);
	g_signal_connect(yr->entry_h, "changed", G_CALLBACK(yui_resolution_height_changed), yr);
	g_signal_connect(yr->options, "changed", G_CALLBACK(yui_resolution_options_changed), yr);
}