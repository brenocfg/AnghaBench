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
struct symbol {char const* name; } ;
struct menu {TYPE_1__* prompt; struct symbol* sym; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conf_askvalue (struct symbol*,char const*) ; 
 char* indent ; 
 int* line ; 
 int /*<<< orphan*/  print_help (struct menu*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  strlen (int*) ; 
 char* sym_get_string_value (struct symbol*) ; 
 scalar_t__ sym_set_string_value (struct symbol*,char const*) ; 

__attribute__((used)) static int conf_string(struct menu *menu)
{
	struct symbol *sym = menu->sym;
	const char *def;

	while (1) {
		printf("%*s%s ", indent - 1, "", _(menu->prompt->text));
		printf("(%s) ", sym->name);
		def = sym_get_string_value(sym);
		if (sym_get_string_value(sym))
			printf("[%s] ", def);
		if (!conf_askvalue(sym, def))
			return 0;
		switch (line[0]) {
		case '\n':
			break;
		case '?':
			/* print help */
			if (line[1] == '\n') {
				print_help(menu);
				def = NULL;
				break;
			}
			/* fall through */
		default:
			line[strlen(line)-1] = 0;
			def = line;
		}
		if (def && sym_set_string_value(sym, def))
			return 0;
	}
}