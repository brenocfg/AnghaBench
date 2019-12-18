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
struct symbol {int dummy; } ;
struct gstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  dialog_clear () ; 
 char* dialog_input_result ; 
 int dialog_inputbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  free (struct symbol**) ; 
 struct gstr get_relations_str (struct symbol**) ; 
 int /*<<< orphan*/  search_help ; 
 int /*<<< orphan*/  show_helptext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_textbox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_free (struct gstr*) ; 
 int /*<<< orphan*/  str_get (struct gstr*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 struct symbol** sym_re_search (char*) ; 

__attribute__((used)) static void search_conf(void)
{
	struct symbol **sym_arr;
	struct gstr res;
	char *dialog_input;
	int dres;
again:
	dialog_clear();
	dres = dialog_inputbox(_("Search Configuration Parameter"),
			      _("Enter CONFIG_ (sub)string to search for "
				"(with or without \"CONFIG\")"),
			      10, 75, "");
	switch (dres) {
	case 0:
		break;
	case 1:
		show_helptext(_("Search Configuration"), search_help);
		goto again;
	default:
		return;
	}

	/* strip CONFIG_ if necessary */
	dialog_input = dialog_input_result;
	if (strncasecmp(dialog_input_result, "CONFIG_", 7) == 0)
		dialog_input += 7;

	sym_arr = sym_re_search(dialog_input);
	res = get_relations_str(sym_arr);
	free(sym_arr);
	show_textbox(_("Search Results"), str_get(&res), 0, 0);
	str_free(&res);
}