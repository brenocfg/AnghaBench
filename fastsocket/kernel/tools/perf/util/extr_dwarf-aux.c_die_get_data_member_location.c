#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ atom; scalar_t__ number; } ;
typedef  scalar_t__ Dwarf_Word ;
typedef  TYPE_1__ Dwarf_Op ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_data_member_location ; 
 scalar_t__ DW_OP_plus_uconst ; 
 int ENOENT ; 
 int ENOTSUP ; 
 int /*<<< orphan*/ * dwarf_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_formudata (int /*<<< orphan*/ *,scalar_t__*) ; 
 int dwarf_getlocation (int /*<<< orphan*/ *,TYPE_1__**,size_t*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,size_t) ; 

int die_get_data_member_location(Dwarf_Die *mb_die, Dwarf_Word *offs)
{
	Dwarf_Attribute attr;
	Dwarf_Op *expr;
	size_t nexpr;
	int ret;

	if (dwarf_attr(mb_die, DW_AT_data_member_location, &attr) == NULL)
		return -ENOENT;

	if (dwarf_formudata(&attr, offs) != 0) {
		/* DW_AT_data_member_location should be DW_OP_plus_uconst */
		ret = dwarf_getlocation(&attr, &expr, &nexpr);
		if (ret < 0 || nexpr == 0)
			return -ENOENT;

		if (expr[0].atom != DW_OP_plus_uconst || nexpr != 1) {
			pr_debug("Unable to get offset:Unexpected OP %x (%zd)\n",
				 expr[0].atom, nexpr);
			return -ENOTSUP;
		}
		*offs = (Dwarf_Word)expr[0].number;
	}
	return 0;
}