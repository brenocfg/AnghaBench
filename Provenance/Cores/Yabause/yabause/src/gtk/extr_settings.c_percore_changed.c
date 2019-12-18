#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpointer ;
struct TYPE_8__ {char* value; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_1__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PerDeInit () ; 
 int /*<<< orphan*/  PerInit (int) ; 
 TYPE_1__* g_list_next (TYPE_1__*) ; 
 size_t gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 
 TYPE_3__* percores ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  yui_input_entry_update (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void percore_changed(GtkWidget * widget, gpointer data) {
	const char * core_s = percores[gtk_combo_box_get_active(GTK_COMBO_BOX(widget))].value;
	GList * entrylist = data;
	int core;
	sscanf(core_s, "%d", &core);

	PerDeInit();
	PerInit(core);

	while(entrylist) {
		yui_input_entry_update(entrylist->data);
		entrylist = g_list_next(entrylist);
	}
}