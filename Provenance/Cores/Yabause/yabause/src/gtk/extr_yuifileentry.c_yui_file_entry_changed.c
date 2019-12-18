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
struct TYPE_3__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  key; int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; } ;
typedef  TYPE_1__ YuiFileEntry ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_get_text (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_file_entry_changed(GtkWidget * entry, YuiFileEntry * yfe) {
        g_key_file_set_value(yfe->keyfile, yfe->group, yfe->key, gtk_entry_get_text(GTK_ENTRY(yfe->entry)));
}