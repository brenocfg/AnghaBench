#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  (* KeyName ) (int /*<<< orphan*/ ,char*,int) ;scalar_t__ canScan; } ;
struct TYPE_6__ {char* group; int /*<<< orphan*/  keyfile; } ;
struct TYPE_5__ {int /*<<< orphan*/  keyval; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GdkEventKey ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 TYPE_4__* PERCore ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* YUI_INPUT_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_set_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

gboolean yui_input_entry_keypress(GtkWidget * widget, GdkEventKey * event, gpointer name) {
	char tmp[100];

	if (PERCore->canScan) return FALSE;

	PERCore->KeyName(event->keyval, tmp, 100);
	gtk_entry_set_text(GTK_ENTRY(widget), tmp);
	sprintf(tmp, "%s.%s.1", YUI_INPUT_ENTRY(gtk_widget_get_parent(widget))->group, (char *)name);
	g_key_file_set_integer(YUI_INPUT_ENTRY(gtk_widget_get_parent(widget))->keyfile,
		PERCore->Name, tmp, event->keyval);

	return TRUE;
}