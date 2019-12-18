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
struct TYPE_3__ {int address; int /*<<< orphan*/  quickCombo; int /*<<< orphan*/  store; } ;
typedef  TYPE_1__ YuiMem ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ ) ; 
 int MappedMemoryReadByte (int) ; 
 int /*<<< orphan*/  gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_entry_set_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void yui_mem_update(YuiMem * ym) {
	int i, j;
	GtkTreeIter iter;
	char address[10];
	char dump[30];

	gtk_list_store_clear(ym->store);

	for(i = 0;i < 6;i++) {
		sprintf(address, "%08x", ym->address + (8 * i));
		for(j = 0;j < 8;j++) {
			sprintf(dump + (j * 3), "%02x ", MappedMemoryReadByte(ym->address + (8 * i) + j));
		}

		gtk_list_store_append(ym->store, &iter);
		gtk_list_store_set(GTK_LIST_STORE(ym->store ), &iter, 0, address, 1, dump, -1);
	}

	sprintf( address, "%08X", ym->address );
	gtk_entry_set_text( GTK_ENTRY(gtk_bin_get_child(GTK_BIN(ym->quickCombo))), address );
}