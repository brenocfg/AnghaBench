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
typedef  char gchar ;
struct TYPE_3__ {int /*<<< orphan*/  options; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; int /*<<< orphan*/  entry_h; int /*<<< orphan*/  entry_w; } ;
typedef  TYPE_1__ YuiResolution ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 TYPE_1__* YUI_RESOLUTION (int /*<<< orphan*/ *) ; 
 int g_key_file_get_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* g_key_file_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yui_resolution_get_type () ; 

GtkWidget* yui_resolution_new(GKeyFile * keyfile, const gchar * group) {
	GtkWidget * widget;
	YuiResolution * yr;
	gchar *widthText, *heightText;

	widget = GTK_WIDGET(g_object_new(yui_resolution_get_type(), "key-file", keyfile, "group", group, NULL));
	yr = YUI_RESOLUTION(widget);

	widthText = g_key_file_get_value(yr->keyfile, yr->group, "Width", 0);
	if ( !widthText ) widthText = "";
	heightText = g_key_file_get_value(yr->keyfile, yr->group, "Height", 0);
	if ( !heightText ) heightText = "";
	gtk_entry_set_text(GTK_ENTRY(yr->entry_w), widthText );
	gtk_entry_set_text(GTK_ENTRY(yr->entry_h), heightText );
	if (g_key_file_get_integer(yr->keyfile, yr->group, "Fullscreen", 0) == 1)
		gtk_combo_box_set_active(GTK_COMBO_BOX(yr->options), 1);
	else if (g_key_file_get_integer(yr->keyfile, yr->group, "KeepRatio", 0) == 1)
		gtk_combo_box_set_active(GTK_COMBO_BOX(yr->options), 2);
	else
		gtk_combo_box_set_active(GTK_COMBO_BOX(yr->options), 0);

	return widget;
}