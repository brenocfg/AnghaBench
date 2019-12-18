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
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;

/* Variables and functions */
#define  S_HEX 132 
#define  S_INT 131 
#define  S_STRING 130 
 char* _ (char*) ; 
 int /*<<< orphan*/  check_stdin () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int input_mode ; 
 char* line ; 
#define  oldaskconfig 129 
#define  oldconfig 128 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int sym_get_type (struct symbol*) ; 
 scalar_t__ sym_has_value (struct symbol*) ; 
 int /*<<< orphan*/  sym_is_changable (struct symbol*) ; 
 int /*<<< orphan*/  xfgets (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int conf_askvalue(struct symbol *sym, const char *def)
{
	enum symbol_type type = sym_get_type(sym);

	if (!sym_has_value(sym))
		printf(_("(NEW) "));

	line[0] = '\n';
	line[1] = 0;

	if (!sym_is_changable(sym)) {
		printf("%s\n", def);
		line[0] = '\n';
		line[1] = 0;
		return 0;
	}

	switch (input_mode) {
	case oldconfig:
		if (sym_has_value(sym)) {
			printf("%s\n", def);
			return 0;
		}
		check_stdin();
		/* fall through */
	case oldaskconfig:
		fflush(stdout);
		xfgets(line, 128, stdin);
		return 1;
	default:
		break;
	}

	switch (type) {
	case S_INT:
	case S_HEX:
	case S_STRING:
		printf("%s\n", def);
		return 1;
	default:
		;
	}
	printf("%s", line);
	return 1;
}