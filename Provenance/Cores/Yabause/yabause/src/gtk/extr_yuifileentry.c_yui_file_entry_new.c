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
typedef  int gint ;
typedef  char gchar ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  entry; int /*<<< orphan*/  key; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; int /*<<< orphan*/  button; } ;
typedef  TYPE_1__ YuiFileEntry ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* YUI_FILE_ENTRY (int /*<<< orphan*/ *) ; 
 int YUI_FILE_ENTRY_BROWSE ; 
 char* g_key_file_get_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ *,char*,char const*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_button_new_with_mnemonic (char*) ; 
 int /*<<< orphan*/  gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_label_new_with_mnemonic (char const*) ; 
 int /*<<< orphan*/  yui_file_entry_browse ; 
 int /*<<< orphan*/  yui_file_entry_changed ; 
 int /*<<< orphan*/  yui_file_entry_get_type () ; 

GtkWidget * yui_file_entry_new(GKeyFile * keyfile, const gchar * group, const gchar * key, gint flags, const gchar * label) {
	GtkWidget * entry;
	YuiFileEntry * yfe;
	gchar * entryText;

	entry = GTK_WIDGET(g_object_new(yui_file_entry_get_type(), "spacing", 10,
		"key-file", keyfile, "group", group, "key", key, NULL));
	yfe = YUI_FILE_ENTRY(entry);

	yfe->flags = flags;

	if (label) {
        	gtk_box_pack_start(GTK_BOX(yfe), gtk_label_new_with_mnemonic(label), FALSE, FALSE, 0);
	}

        yfe->entry = gtk_entry_new ();
        gtk_box_pack_start(GTK_BOX(yfe), yfe->entry, TRUE, TRUE, 0);

	if (flags & YUI_FILE_ENTRY_BROWSE) {
	        yfe->button = gtk_button_new_with_mnemonic ("Browse");
        	g_signal_connect(yfe->button, "clicked", G_CALLBACK(yui_file_entry_browse), yfe);
	        gtk_box_pack_start(GTK_BOX(yfe), yfe->button, FALSE, FALSE, 0);
	}

	entryText = g_key_file_get_value(yfe->keyfile, yfe->group, yfe->key, 0);
	if ( !entryText ) entryText = "";
        gtk_entry_set_text(GTK_ENTRY(yfe->entry), entryText );
        g_signal_connect(GTK_ENTRY(yfe->entry), "changed", G_CALLBACK(yui_file_entry_changed), yfe);

	return entry;
}