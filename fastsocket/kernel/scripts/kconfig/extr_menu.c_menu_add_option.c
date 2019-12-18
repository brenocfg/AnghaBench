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
struct property {int /*<<< orphan*/  expr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sym; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_DEFAULT ; 
#define  T_OPT_DEFCONFIG_LIST 130 
#define  T_OPT_ENV 129 
#define  T_OPT_MODULES 128 
 TYPE_1__* current_entry ; 
 int /*<<< orphan*/  expr_alloc_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modules_sym ; 
 int /*<<< orphan*/  prop_add_env (char*) ; 
 struct property* prop_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_defconfig_list ; 
 int /*<<< orphan*/  zconf_error (char*) ; 

void menu_add_option(int token, char *arg)
{
	struct property *prop;

	switch (token) {
	case T_OPT_MODULES:
		prop = prop_alloc(P_DEFAULT, modules_sym);
		prop->expr = expr_alloc_symbol(current_entry->sym);
		break;
	case T_OPT_DEFCONFIG_LIST:
		if (!sym_defconfig_list)
			sym_defconfig_list = current_entry->sym;
		else if (sym_defconfig_list != current_entry->sym)
			zconf_error("trying to redefine defconfig symbol");
		break;
	case T_OPT_ENV:
		prop_add_env(arg);
		break;
	}
}