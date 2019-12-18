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
typedef  int /*<<< orphan*/  dwarf_t ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  scalar_t__ Dwarf_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_declaration ; 
 scalar_t__ die_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
die_isdecl(dwarf_t *dw, Dwarf_Die die)
{
	Dwarf_Bool val;

	return (die_bool(dw, die, DW_AT_declaration, &val, 0) && val);
}