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
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/ * gpointer ;
typedef  char gchar ;
struct TYPE_2__ {int /*<<< orphan*/  (* KeyName ) (int /*<<< orphan*/ ,char*,int) ;int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkAttachOptions ;
typedef  int /*<<< orphan*/  GKeyFile ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int GTK_EXPAND ; 
 int GTK_FILL ; 
 int /*<<< orphan*/  GTK_MISC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 TYPE_1__* PERCore ; 
 int /*<<< orphan*/  g_key_file_get_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_entry_new () ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_entry_set_width_chars (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gtk_label_new (char const*) ; 
 int /*<<< orphan*/  gtk_misc_set_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  gtk_table_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_resize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  yui_input_entry_focus_in ; 
 int /*<<< orphan*/  yui_input_entry_focus_out ; 
 int /*<<< orphan*/  yui_input_entry_get_type () ; 
 int /*<<< orphan*/  yui_input_entry_keypress ; 

GtkWidget* yui_input_entry_new(GKeyFile * keyfile, const gchar * group, const gchar * keys[]) {
	GtkWidget * widget;
	GtkWidget * label;
	GtkWidget * entry;
	guint keyName;
	int row = 0;

	widget = GTK_WIDGET(g_object_new(yui_input_entry_get_type(), "key-file", keyfile, "group", group, NULL));

	while(keys[row]) {
		char tmp[100];
		gtk_table_resize(GTK_TABLE(widget), row + 1, 2);
		label = gtk_label_new(keys[row]);
  
		gtk_table_attach(GTK_TABLE(widget), label, 0, 1, row , row + 1,
			(GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);

		entry = gtk_entry_new ();
		gtk_entry_set_width_chars(GTK_ENTRY(entry), 10);

		sprintf(tmp, "%s.%s.1", group, keys[row]);
		keyName = g_key_file_get_integer(keyfile, PERCore->Name, tmp, 0);
		if (keyName > 0) {
			char buffer[50];
			PERCore->KeyName(keyName, buffer, 50);
			gtk_entry_set_text(GTK_ENTRY(entry), buffer);
		}

		if (PERCore) {
			//if (PERCore->canScan)
				g_signal_connect(entry, "focus-in-event", G_CALLBACK(yui_input_entry_focus_in), (gpointer) keys[row]);
				g_signal_connect(entry, "focus-out-event", G_CALLBACK(yui_input_entry_focus_out), NULL);
			//else
				g_signal_connect(entry, "key-press-event", G_CALLBACK(yui_input_entry_keypress), (gpointer) keys[row]);
		} else {
			gtk_widget_set_sensitive(entry, FALSE);
		}
  
		gtk_table_attach(GTK_TABLE(widget), entry,  1, 2, row, row + 1,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		row++;
	}

	return widget;
}