#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;
struct TYPE_5__ {struct TYPE_5__* parent; TYPE_1__* prompt; } ;
struct TYPE_4__ {int type; } ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int P_MENU ; 
 int P_UNKNOWN ; 
 int /*<<< orphan*/  back_btn ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  display_tree_part () ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ rootmenu ; 

void on_back_clicked(GtkButton * button, gpointer user_data)
{
	enum prop_type ptype;

	current = current->parent;
	ptype = current->prompt ? current->prompt->type : P_UNKNOWN;
	if (ptype != P_MENU)
		current = current->parent;
	display_tree_part();

	if (current == &rootmenu)
		gtk_widget_set_sensitive(back_btn, FALSE);
}