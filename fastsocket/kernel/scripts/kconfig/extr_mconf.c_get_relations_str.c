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
 int /*<<< orphan*/  get_symbol_str (struct gstr*,struct symbol*) ; 
 int /*<<< orphan*/  str_append (struct gstr*,int /*<<< orphan*/ ) ; 
 struct gstr str_new () ; 

__attribute__((used)) static struct gstr get_relations_str(struct symbol **sym_arr)
{
	struct symbol *sym;
	struct gstr res = str_new();
	int i;

	for (i = 0; sym_arr && (sym = sym_arr[i]); i++)
		get_symbol_str(&res, sym);
	if (!i)
		str_append(&res, _("No matches found.\n"));
	return res;
}