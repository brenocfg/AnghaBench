#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {char* group; int /*<<< orphan*/  keyfile; } ;
typedef  TYPE_1__ YuiInputEntry ;
struct TYPE_11__ {int /*<<< orphan*/  (* KeyName ) (scalar_t__,char*,int) ;int /*<<< orphan*/  Name; } ;
struct TYPE_10__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  GtkEntry ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 TYPE_7__* PERCore ; 
 scalar_t__ g_key_file_get_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* g_list_next (TYPE_2__*) ; 
 TYPE_2__* gtk_container_get_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ *,char*) ; 
 char* gtk_label_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,char*,int) ; 

void yui_input_entry_update(YuiInputEntry * yie) {
	GList * wlist = gtk_container_get_children(GTK_CONTAINER(yie));
	u32 key;
	GtkEntry * entry = NULL;
	char tmp[100];

	while(wlist) {
		if (strcmp(gtk_widget_get_name(wlist->data), "GtkEntry") == 0) {
			entry = wlist->data;
		}
		if (strcmp(gtk_widget_get_name(wlist->data), "GtkLabel") == 0) {
			sprintf(tmp, "%s.%s.1", yie->group, gtk_label_get_text(wlist->data));
                	key = g_key_file_get_integer(yie->keyfile, PERCore->Name, tmp, 0);
			if (key > 0) {
				PERCore->KeyName(key, tmp, 100);
				gtk_entry_set_text(entry, tmp);
			} else {
				gtk_entry_set_text(entry, "");
			}
		}
		wlist = g_list_next(wlist);
	}
}