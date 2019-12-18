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
typedef  int tristate ;
struct symbol {char* name; } ;
struct menu {TYPE_1__* prompt; struct symbol* sym; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_askvalue (struct symbol*,int /*<<< orphan*/ ) ; 
 char* indent ; 
 int* line ; 
 scalar_t__ menu_has_help (struct menu*) ; 
#define  mod 130 
#define  no 129 
 int /*<<< orphan*/  print_help (struct menu*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  strcmp (int*,char*) ; 
 int /*<<< orphan*/  strip (int*) ; 
 int /*<<< orphan*/  sym_get_string_value (struct symbol*) ; 
 int sym_get_tristate_value (struct symbol*) ; 
 int sym_get_type (struct symbol*) ; 
 scalar_t__ sym_set_tristate_value (struct symbol*,int) ; 
 scalar_t__ sym_tristate_within_range (struct symbol*,int const) ; 
#define  yes 128 

__attribute__((used)) static int conf_sym(struct menu *menu)
{
	struct symbol *sym = menu->sym;
	int type;
	tristate oldval, newval;

	while (1) {
		printf("%*s%s ", indent - 1, "", _(menu->prompt->text));
		if (sym->name)
			printf("(%s) ", sym->name);
		type = sym_get_type(sym);
		putchar('[');
		oldval = sym_get_tristate_value(sym);
		switch (oldval) {
		case no:
			putchar('N');
			break;
		case mod:
			putchar('M');
			break;
		case yes:
			putchar('Y');
			break;
		}
		if (oldval != no && sym_tristate_within_range(sym, no))
			printf("/n");
		if (oldval != mod && sym_tristate_within_range(sym, mod))
			printf("/m");
		if (oldval != yes && sym_tristate_within_range(sym, yes))
			printf("/y");
		if (menu_has_help(menu))
			printf("/?");
		printf("] ");
		if (!conf_askvalue(sym, sym_get_string_value(sym)))
			return 0;
		strip(line);

		switch (line[0]) {
		case 'n':
		case 'N':
			newval = no;
			if (!line[1] || !strcmp(&line[1], "o"))
				break;
			continue;
		case 'm':
		case 'M':
			newval = mod;
			if (!line[1])
				break;
			continue;
		case 'y':
		case 'Y':
			newval = yes;
			if (!line[1] || !strcmp(&line[1], "es"))
				break;
			continue;
		case 0:
			newval = oldval;
			break;
		case '?':
			goto help;
		default:
			continue;
		}
		if (sym_set_tristate_value(sym, newval))
			return 0;
help:
		print_help(menu);
	}
}