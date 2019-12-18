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
struct symbol {scalar_t__ name; } ;
struct menu {struct symbol* sym; } ;
struct gstr {int dummy; } ;

/* Variables and functions */
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_symbol_str (struct gstr*,struct symbol*) ; 
 int /*<<< orphan*/  menu_get_help (struct menu*) ; 
 scalar_t__ menu_has_help (struct menu*) ; 
 char* nohelp_text ; 
 int /*<<< orphan*/  str_append (struct gstr*,char*) ; 
 int /*<<< orphan*/  str_printf (struct gstr*,char*,scalar_t__) ; 

void menu_get_ext_help(struct menu *menu, struct gstr *help)
{
	struct symbol *sym = menu->sym;

	if (menu_has_help(menu)) {
		if (sym->name) {
			str_printf(help, "CONFIG_%s:\n\n", sym->name);
			str_append(help, _(menu_get_help(menu)));
			str_append(help, "\n");
		}
	} else {
		str_append(help, nohelp_text);
	}
	if (sym)
		get_symbol_str(help, sym);
}