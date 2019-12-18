#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tristate ;
struct TYPE_6__ {scalar_t__ val; } ;
struct symbol {int type; TYPE_2__ curr; } ;
struct TYPE_5__ {int const tri; } ;
struct TYPE_7__ {TYPE_1__ curr; } ;

/* Variables and functions */
#define  S_BOOLEAN 132 
#define  S_TRISTATE 131 
#define  mod 130 
 TYPE_3__* modules_sym ; 
#define  no 129 
 int /*<<< orphan*/  sym_calc_value (TYPE_3__*) ; 
 int /*<<< orphan*/  sym_get_tristate_value (struct symbol*) ; 
#define  yes 128 

const char *sym_get_string_value(struct symbol *sym)
{
	tristate val;

	switch (sym->type) {
	case S_BOOLEAN:
	case S_TRISTATE:
		val = sym_get_tristate_value(sym);
		switch (val) {
		case no:
			return "n";
		case mod:
			sym_calc_value(modules_sym);
			return (modules_sym->curr.tri == no) ? "n" : "m";
		case yes:
			return "y";
		}
		break;
	default:
		;
	}
	return (const char *)sym->curr.val;
}