#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ YuiRangeItem ;
struct TYPE_10__ {int /*<<< orphan*/  combo; int /*<<< orphan*/  key; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; TYPE_1__* items; } ;
typedef  TYPE_3__ YuiRange ;
struct TYPE_8__ {int /*<<< orphan*/  value; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 TYPE_3__* YUI_RANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_key_file_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*,char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  gtk_combo_box_append_text (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gtk_combo_box_set_active (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_range_changed ; 
 int /*<<< orphan*/  yui_range_get_type () ; 

GtkWidget * yui_range_new(GKeyFile * keyfile, const gchar * group, const gchar * key, YuiRangeItem * items) {
	GtkWidget * entry;
	YuiRange * yfe;
	gchar * current;
	guint i;

	entry = GTK_WIDGET(g_object_new(yui_range_get_type(), "spacing", 10,
		"key-file", keyfile, "group", group, "key", key, "items", items, NULL));
	yfe = YUI_RANGE(entry);

	current = g_key_file_get_value(yfe->keyfile, yfe->group, yfe->key, 0);
	i = 0;
	while(yfe->items[i].name) {
		gtk_combo_box_append_text(GTK_COMBO_BOX(yfe->combo), yfe->items[i].name);
		if (current && !strcmp(yfe->items[i].value, current))
			gtk_combo_box_set_active(GTK_COMBO_BOX(yfe->combo), i);
		i++;
	}
	if ( !current ) {
		gtk_combo_box_set_active(GTK_COMBO_BOX(yfe->combo), 0);
		g_key_file_set_value(yfe->keyfile, yfe->group, yfe->key, items[0].value);
	}

        g_signal_connect(GTK_COMBO_BOX(yfe->combo), "changed", G_CALLBACK(yui_range_changed), yfe);

	return entry;
}