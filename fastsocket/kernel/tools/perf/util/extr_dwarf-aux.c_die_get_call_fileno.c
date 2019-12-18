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
typedef  scalar_t__ Dwarf_Sword ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_call_file ; 
 int ENOENT ; 
 scalar_t__ die_get_attr_sdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int die_get_call_fileno(Dwarf_Die *in_die)
{
	Dwarf_Sword idx;

	if (die_get_attr_sdata(in_die, DW_AT_call_file, &idx) == 0)
		return (int)idx;
	else
		return -ENOENT;
}