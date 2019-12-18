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
struct symbol {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ S_HEX ; 
 scalar_t__ S_INT ; 
 scalar_t__ S_UNKNOWN ; 
 scalar_t__ sym_string_valid (struct symbol*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int menu_range_valid_sym(struct symbol *sym, struct symbol *sym2)
{
	return sym2->type == S_INT || sym2->type == S_HEX ||
	       (sym2->type == S_UNKNOWN && sym_string_valid(sym, sym2->name));
}