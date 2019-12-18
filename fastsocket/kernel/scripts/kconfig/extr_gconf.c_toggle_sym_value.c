#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct menu {int /*<<< orphan*/  sym; } ;

/* Variables and functions */
 scalar_t__ FULL_VIEW ; 
 scalar_t__ SINGLE_VIEW ; 
 scalar_t__ SPLIT_VIEW ; 
 int /*<<< orphan*/ * browsed ; 
 int /*<<< orphan*/  display_list () ; 
 int /*<<< orphan*/  display_tree_part () ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  sym_toggle_tristate_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ view_mode ; 

__attribute__((used)) static void toggle_sym_value(struct menu *menu)
{
	if (!menu->sym)
		return;

	sym_toggle_tristate_value(menu->sym);
	if (view_mode == FULL_VIEW)
		update_tree(&rootmenu, NULL);
	else if (view_mode == SPLIT_VIEW) {
		update_tree(browsed, NULL);
		display_list();
	}
	else if (view_mode == SINGLE_VIEW)
		display_tree_part();	//fixme: keep exp/coll
}