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
struct symbol {int dummy; } ;
struct menu {TYPE_1__* prompt; void* data; struct symbol* sym; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ERRDISPLAYTOOSMALL ; 
 int KEY_ESC ; 
 int /*<<< orphan*/  P_MENU ; 
 char* _ (char const*) ; 
 int /*<<< orphan*/  build_conf (struct menu*) ; 
 int /*<<< orphan*/  child_count ; 
 int /*<<< orphan*/  conf_choice (struct menu*) ; 
 int /*<<< orphan*/  conf_load () ; 
 int /*<<< orphan*/  conf_save () ; 
 int /*<<< orphan*/  conf_string (struct menu*) ; 
 struct menu* current_menu ; 
 int /*<<< orphan*/  dialog_clear () ; 
 int dialog_menu (char*,char*,struct menu*,int*) ; 
 int /*<<< orphan*/  item_activate_selected () ; 
 struct menu* item_data () ; 
 int /*<<< orphan*/  item_is_tag (char) ; 
 int /*<<< orphan*/  item_make (char*) ; 
 int /*<<< orphan*/  item_reset () ; 
 int /*<<< orphan*/  item_set_tag (char) ; 
 scalar_t__ item_tag () ; 
 char* mconf_readme ; 
 char* menu_get_prompt (struct menu*) ; 
 char* menu_instructions ; 
 int /*<<< orphan*/  mod ; 
 int /*<<< orphan*/  no ; 
 struct menu rootmenu ; 
 int /*<<< orphan*/  search_conf () ; 
 int /*<<< orphan*/  setmod_text ; 
 int /*<<< orphan*/  show_help (struct menu*) ; 
 int /*<<< orphan*/  show_helptext (char*,char*) ; 
 int /*<<< orphan*/  show_textbox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  single_menu_mode ; 
 int /*<<< orphan*/  sym_get_tristate_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_choice (struct symbol*) ; 
 int /*<<< orphan*/  sym_set_tristate_value (struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_toggle_tristate_value (struct symbol*) ; 
 int /*<<< orphan*/  yes ; 

__attribute__((used)) static void conf(struct menu *menu)
{
	struct menu *submenu;
	const char *prompt = menu_get_prompt(menu);
	struct symbol *sym;
	struct menu *active_menu = NULL;
	int res;
	int s_scroll = 0;

	while (1) {
		item_reset();
		current_menu = menu;
		build_conf(menu);
		if (!child_count)
			break;
		if (menu == &rootmenu) {
			item_make("--- ");
			item_set_tag(':');
			item_make(_("    Load an Alternate Configuration File"));
			item_set_tag('L');
			item_make(_("    Save an Alternate Configuration File"));
			item_set_tag('S');
		}
		dialog_clear();
		res = dialog_menu(prompt ? _(prompt) : _("Main Menu"),
				  _(menu_instructions),
				  active_menu, &s_scroll);
		if (res == 1 || res == KEY_ESC || res == -ERRDISPLAYTOOSMALL)
			break;
		if (!item_activate_selected())
			continue;
		if (!item_tag())
			continue;

		submenu = item_data();
		active_menu = item_data();
		if (submenu)
			sym = submenu->sym;
		else
			sym = NULL;

		switch (res) {
		case 0:
			switch (item_tag()) {
			case 'm':
				if (single_menu_mode)
					submenu->data = (void *) (long) !submenu->data;
				else
					conf(submenu);
				break;
			case 't':
				if (sym_is_choice(sym) && sym_get_tristate_value(sym) == yes)
					conf_choice(submenu);
				else if (submenu->prompt->type == P_MENU)
					conf(submenu);
				break;
			case 's':
				conf_string(submenu);
				break;
			case 'L':
				conf_load();
				break;
			case 'S':
				conf_save();
				break;
			}
			break;
		case 2:
			if (sym)
				show_help(submenu);
			else
				show_helptext(_("README"), _(mconf_readme));
			break;
		case 3:
			if (item_is_tag('t')) {
				if (sym_set_tristate_value(sym, yes))
					break;
				if (sym_set_tristate_value(sym, mod))
					show_textbox(NULL, setmod_text, 6, 74);
			}
			break;
		case 4:
			if (item_is_tag('t'))
				sym_set_tristate_value(sym, no);
			break;
		case 5:
			if (item_is_tag('t'))
				sym_set_tristate_value(sym, mod);
			break;
		case 6:
			if (item_is_tag('t'))
				sym_toggle_tristate_value(sym);
			else if (item_is_tag('m'))
				conf(submenu);
			break;
		case 7:
			search_conf();
			break;
		}
	}
}