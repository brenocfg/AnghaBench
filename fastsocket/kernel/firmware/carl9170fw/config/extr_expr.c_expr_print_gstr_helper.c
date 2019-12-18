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
struct symbol {scalar_t__ type; } ;
struct gstr {unsigned int max_width; char* s; } ;

/* Variables and functions */
 scalar_t__ S_UNKNOWN ; 
 int /*<<< orphan*/  str_append (struct gstr*,char const*) ; 
 int /*<<< orphan*/  str_printf (struct gstr*,char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 char* sym_get_string_value (struct symbol*) ; 

__attribute__((used)) static void expr_print_gstr_helper(void *data, struct symbol *sym, const char *str)
{
	struct gstr *gs = (struct gstr*)data;
	const char *sym_str = NULL;

	if (sym)
		sym_str = sym_get_string_value(sym);

	if (gs->max_width) {
		unsigned extra_length = strlen(str);
		const char *last_cr = strrchr(gs->s, '\n');
		unsigned last_line_length;

		if (sym_str)
			extra_length += 4 + strlen(sym_str);

		if (!last_cr)
			last_cr = gs->s;

		last_line_length = strlen(gs->s) - (last_cr - gs->s);

		if ((last_line_length + extra_length) > gs->max_width)
			str_append(gs, "\\\n");
	}

	str_append(gs, str);
	if (sym && sym->type != S_UNKNOWN)
		str_printf(gs, " [=%s]", sym_str);
}