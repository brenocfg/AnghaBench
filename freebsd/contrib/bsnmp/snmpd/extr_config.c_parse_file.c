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
struct lmodule {int dummy; } ;

/* Variables and functions */
 scalar_t__ TOK_ASSIGN ; 
 scalar_t__ TOK_EOF ; 
 char TOK_EOL ; 
 char TOK_QASSIGN ; 
 char TOK_STR ; 
 int _POSIX2_LINE_MAX ; 
 scalar_t__ gettoken () ; 
 int /*<<< orphan*/  parse_assign (char*) ; 
 int /*<<< orphan*/  parse_define (char*) ; 
 int /*<<< orphan*/  parse_include () ; 
 int /*<<< orphan*/  parse_section (struct lmodule const*) ; 
 int /*<<< orphan*/  report (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strval ; 
 char token ; 

__attribute__((used)) static void
parse_file(const struct lmodule *mod)
{
	char varname[_POSIX2_LINE_MAX];

	while (gettoken() != TOK_EOF) {
		if (token == TOK_EOL)
			/* empty line */
			continue;
		if (token == '%') {
			gettoken();
			parse_section(mod);
		} else if (token == '.') {
			if (gettoken() != TOK_STR)
				report("keyword expected after '.'");
			if (strcmp(strval, "include") == 0)
				parse_include();
			else
				report("unknown keyword '%s'", strval);
		} else if (token == TOK_STR) {
			strcpy(varname, strval);
			if (gettoken() == TOK_ASSIGN || token == TOK_QASSIGN)
				parse_define(varname);
			else
				parse_assign(varname);
		}
		if (token != TOK_EOL)
			report("eol expected");
	}
}