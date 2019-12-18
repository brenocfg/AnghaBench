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
 int /*<<< orphan*/  str_append (struct gstr*,char const*) ; 
 int /*<<< orphan*/  str_printf (struct gstr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_get_string_value (struct symbol*) ; 

__attribute__((used)) static void expr_print_gstr_helper(void *data, struct symbol *sym, const char *str)
{
	str_append((struct gstr*)data, str);
	if (sym)
		str_printf((struct gstr*)data, " [=%s]", sym_get_string_value(sym));
}