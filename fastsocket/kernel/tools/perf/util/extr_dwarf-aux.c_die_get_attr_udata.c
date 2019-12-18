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
typedef  int /*<<< orphan*/  Dwarf_Word ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * dwarf_attr (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ dwarf_formudata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int die_get_attr_udata(Dwarf_Die *tp_die, unsigned int attr_name,
			      Dwarf_Word *result)
{
	Dwarf_Attribute attr;

	if (dwarf_attr(tp_die, attr_name, &attr) == NULL ||
	    dwarf_formudata(&attr, result) != 0)
		return -ENOENT;

	return 0;
}