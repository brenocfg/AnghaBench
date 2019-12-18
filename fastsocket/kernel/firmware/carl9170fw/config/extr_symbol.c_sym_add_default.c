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
struct property {int /*<<< orphan*/  expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_DEFAULT ; 
 int /*<<< orphan*/  SYMBOL_CONST ; 
 int /*<<< orphan*/  expr_alloc_symbol (int /*<<< orphan*/ ) ; 
 struct property* prop_alloc (int /*<<< orphan*/ ,struct symbol*) ; 
 int /*<<< orphan*/  sym_lookup (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_add_default(struct symbol *sym, const char *def)
{
	struct property *prop = prop_alloc(P_DEFAULT, sym);

	prop->expr = expr_alloc_symbol(sym_lookup(def, SYMBOL_CONST));
}