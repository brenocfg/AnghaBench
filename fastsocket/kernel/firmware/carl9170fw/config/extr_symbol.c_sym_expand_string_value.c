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

/* Variables and functions */
 int SYMBOL_MAXLENGTH ; 
 scalar_t__ isalnum (char const) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 int /*<<< orphan*/  sym_calc_value (struct symbol*) ; 
 struct symbol* sym_find (char*) ; 
 char* sym_get_string_value (struct symbol*) ; 

const char *sym_expand_string_value(const char *in)
{
	const char *src;
	char *res;
	size_t reslen;

	reslen = strlen(in) + 1;
	res = malloc(reslen);
	res[0] = '\0';

	while ((src = strchr(in, '$'))) {
		char *p, name[SYMBOL_MAXLENGTH];
		const char *symval = "";
		struct symbol *sym;
		size_t newlen;

		strncat(res, in, src - in);
		src++;

		p = name;
		while (isalnum(*src) || *src == '_')
			*p++ = *src++;
		*p = '\0';

		sym = sym_find(name);
		if (sym != NULL) {
			sym_calc_value(sym);
			symval = sym_get_string_value(sym);
		}

		newlen = strlen(res) + strlen(symval) + strlen(src) + 1;
		if (newlen > reslen) {
			reslen = newlen;
			res = realloc(res, reslen);
		}

		strcat(res, symval);
		in = src;
	}
	strcat(res, in);

	return res;
}