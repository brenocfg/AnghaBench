#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; } ;
typedef  TYPE_1__ YuiCheckButton ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (TYPE_1__*) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* YUI_CHECK_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_key_file_get_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_button_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_check_button_get_type () ; 
 int /*<<< orphan*/  yui_check_button_toggled ; 

GtkWidget * yui_check_button_new(const gchar * label, GKeyFile * keyfile, const gchar * group, const gchar * key) {
	GtkWidget * button;
	YuiCheckButton * ycb;
	gboolean current;

	button = GTK_WIDGET(g_object_new(yui_check_button_get_type(),
		"label", label,
		"key-file", keyfile, "group", group, "key", key, NULL));
	ycb = YUI_CHECK_BUTTON(button);

	gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(ycb), TRUE);

	current = g_key_file_get_boolean(ycb->keyfile, ycb->group, ycb->key, NULL);
	gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(ycb), current);

        g_signal_connect(GTK_TOGGLE_BUTTON(ycb), "toggled", G_CALLBACK(yui_check_button_toggled), ycb);

	return button;
}