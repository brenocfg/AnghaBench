#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ cursor; struct TYPE_19__* hbox; struct TYPE_19__* vbox; int /*<<< orphan*/  buffer; struct TYPE_19__* spin; } ;
typedef  TYPE_1__ YuiScsp ;
typedef  TYPE_1__ GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_POLICY_AUTOMATIC ; 
 int /*<<< orphan*/  GTK_SCROLLED_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_SIGNAL_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_TEXT_VIEW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  G_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_box_set_spacing (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_hbutton_box_new () ; 
 TYPE_1__* gtk_scrolled_window_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_scrolled_window_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_spin_button_new_with_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_spin_button_set_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_text_view_get_buffer (int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_text_view_new () ; 
 int /*<<< orphan*/  gtk_text_view_set_cursor_visible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_text_view_set_editable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gtk_vbox_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_window_set_title (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yui_scsp_destroy ; 
 int /*<<< orphan*/  yui_scsp_spin_cursor_changed ; 

__attribute__((used)) static void yui_scsp_init (YuiScsp * yv) {
	gtk_window_set_title(GTK_WINDOW(yv), "SCSP");

	yv->vbox = gtk_vbox_new(FALSE, 2);
	gtk_container_set_border_width(GTK_CONTAINER(yv->vbox), 4);
	gtk_container_add(GTK_CONTAINER(yv), yv->vbox);

	yv->spin = gtk_spin_button_new_with_range(0, 31, 1);
	gtk_spin_button_set_range(GTK_SPIN_BUTTON(yv->spin), 0, 31);
	gtk_box_pack_start(GTK_BOX(yv->vbox), yv->spin, FALSE, FALSE, 4);
	g_signal_connect(G_OBJECT(yv->spin), "value-changed", GTK_SIGNAL_FUNC(yui_scsp_spin_cursor_changed), yv);

	g_signal_connect(G_OBJECT(yv), "delete-event", GTK_SIGNAL_FUNC(yui_scsp_destroy), NULL);

	{
		GtkWidget * scroll = gtk_scrolled_window_new(NULL, NULL);
		GtkWidget * text = gtk_text_view_new();
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
		gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text), FALSE);
		yv->buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text));
		gtk_container_add(GTK_CONTAINER(scroll), text);
		gtk_box_pack_start(GTK_BOX(yv->vbox), scroll, TRUE, TRUE, 4);
	}

	yv->hbox = gtk_hbutton_box_new();
	gtk_box_set_spacing(GTK_BOX(yv->hbox), 4);
	gtk_box_pack_start(GTK_BOX(yv->vbox ), yv->hbox, FALSE, FALSE, 4);

	yv->cursor = 0;
}