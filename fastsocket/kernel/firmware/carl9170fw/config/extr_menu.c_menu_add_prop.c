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
struct TYPE_2__ {int /*<<< orphan*/  expr; } ;
struct property {char* text; TYPE_1__ visible; struct expr* expr; struct menu* menu; } ;
struct menu {struct property* prompt; int /*<<< orphan*/  visibility; struct menu* parent; int /*<<< orphan*/  sym; } ;
struct expr {int dummy; } ;
typedef  enum prop_type { ____Placeholder_prop_type } prop_type ;

/* Variables and functions */
 int P_PROMPT ; 
 struct menu* current_entry ; 
 int /*<<< orphan*/  expr_alloc_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  menu_check_dep (struct expr*) ; 
 struct property* prop_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_warn (struct property*,char*) ; 
 struct menu rootmenu ; 

struct property *menu_add_prop(enum prop_type type, char *prompt, struct expr *expr, struct expr *dep)
{
	struct property *prop = prop_alloc(type, current_entry->sym);

	prop->menu = current_entry;
	prop->expr = expr;
	prop->visible.expr = menu_check_dep(dep);

	if (prompt) {
		if (isspace(*prompt)) {
			prop_warn(prop, "leading whitespace ignored");
			while (isspace(*prompt))
				prompt++;
		}
		if (current_entry->prompt && current_entry != &rootmenu)
			prop_warn(prop, "prompt redefined");

		/* Apply all upper menus' visibilities to actual prompts. */
		if(type == P_PROMPT) {
			struct menu *menu = current_entry;

			while ((menu = menu->parent) != NULL) {
				if (!menu->visibility)
					continue;
				prop->visible.expr
					= expr_alloc_and(prop->visible.expr,
							 menu->visibility);
			}
		}

		current_entry->prompt = prop;
	}
	prop->text = prompt;

	return prop;
}