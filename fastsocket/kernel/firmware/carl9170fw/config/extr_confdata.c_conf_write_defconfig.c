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
struct symbol {int flags; scalar_t__ type; } ;
struct menu {struct menu* next; struct menu* parent; struct menu* list; struct symbol* sym; } ;
struct TYPE_2__ {struct menu* list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SYMBOL_WRITE ; 
 scalar_t__ S_BOOLEAN ; 
 int /*<<< orphan*/  conf_write_symbol (int /*<<< orphan*/ *,struct symbol*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  kconfig_printer_cb ; 
 int /*<<< orphan*/  menu_is_visible (struct menu*) ; 
 struct symbol* prop_get_symbol (int /*<<< orphan*/ ) ; 
 TYPE_1__ rootmenu ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_calc_value (struct symbol*) ; 
 struct symbol* sym_choice_default (struct symbol*) ; 
 int /*<<< orphan*/  sym_clear_all_valid () ; 
 int /*<<< orphan*/  sym_get_choice_prop (struct symbol*) ; 
 int /*<<< orphan*/  sym_get_string_default (struct symbol*) ; 
 int /*<<< orphan*/  sym_get_string_value (struct symbol*) ; 
 scalar_t__ sym_get_tristate_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_changable (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_choice (struct symbol*) ; 
 scalar_t__ sym_is_choice_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_optional (struct symbol*) ; 
 scalar_t__ yes ; 

int conf_write_defconfig(const char *filename)
{
	struct symbol *sym;
	struct menu *menu;
	FILE *out;

	out = fopen(filename, "w");
	if (!out)
		return 1;

	sym_clear_all_valid();

	/* Traverse all menus to find all relevant symbols */
	menu = rootmenu.list;

	while (menu != NULL)
	{
		sym = menu->sym;
		if (sym == NULL) {
			if (!menu_is_visible(menu))
				goto next_menu;
		} else if (!sym_is_choice(sym)) {
			sym_calc_value(sym);
			if (!(sym->flags & SYMBOL_WRITE))
				goto next_menu;
			sym->flags &= ~SYMBOL_WRITE;
			/* If we cannot change the symbol - skip */
			if (!sym_is_changable(sym))
				goto next_menu;
			/* If symbol equals to default value - skip */
			if (strcmp(sym_get_string_value(sym), sym_get_string_default(sym)) == 0)
				goto next_menu;

			/*
			 * If symbol is a choice value and equals to the
			 * default for a choice - skip.
			 * But only if value is bool and equal to "y" and
			 * choice is not "optional".
			 * (If choice is "optional" then all values can be "n")
			 */
			if (sym_is_choice_value(sym)) {
				struct symbol *cs;
				struct symbol *ds;

				cs = prop_get_symbol(sym_get_choice_prop(sym));
				ds = sym_choice_default(cs);
				if (!sym_is_optional(cs) && sym == ds) {
					if ((sym->type == S_BOOLEAN) &&
					    sym_get_tristate_value(sym) == yes)
						goto next_menu;
				}
			}
			conf_write_symbol(out, sym, &kconfig_printer_cb, NULL);
		}
next_menu:
		if (menu->list != NULL) {
			menu = menu->list;
		}
		else if (menu->next != NULL) {
			menu = menu->next;
		} else {
			while ((menu = menu->parent)) {
				if (menu->next != NULL) {
					menu = menu->next;
					break;
				}
			}
		}
	}
	fclose(out);
	return 0;
}