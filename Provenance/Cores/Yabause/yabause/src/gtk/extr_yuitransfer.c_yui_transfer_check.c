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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int mode; int /*<<< orphan*/  transfer_button; int /*<<< orphan*/  to_entry; int /*<<< orphan*/  from_entry; int /*<<< orphan*/  file_entry; } ;
typedef  TYPE_1__ YuiTransfer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  YUI_TRANSFER_LOAD 130 
#define  YUI_TRANSFER_LOAD_EXEC 129 
#define  YUI_TRANSFER_STORE 128 
 char* gtk_entry_get_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_transfer_check(YuiTransfer * yt) {
	gboolean ok = FALSE;

	if (*gtk_entry_get_text(GTK_ENTRY(yt->file_entry)) != '\0') {
		switch(yt->mode) {
			case YUI_TRANSFER_LOAD:
			case YUI_TRANSFER_LOAD_EXEC:
				if (*gtk_entry_get_text(GTK_ENTRY(yt->from_entry)) != '\0') {
					ok = TRUE;
				}
				break;
			case YUI_TRANSFER_STORE:
				if ((*gtk_entry_get_text(GTK_ENTRY(yt->from_entry)) != '\0') && (*gtk_entry_get_text(GTK_ENTRY(yt->to_entry)) != '\0')) {
					ok = TRUE;
				}
				break;
		}
	}

	gtk_widget_set_sensitive(yt->transfer_button, ok);
}