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
typedef  int /*<<< orphan*/  tdesc_t ;
typedef  int /*<<< orphan*/  dwarf_t ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int /*<<< orphan*/ * die_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_attr_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tdesc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tdesc_t *
die_lookup_pass1(dwarf_t *dw, Dwarf_Die die, Dwarf_Half name)
{
	Dwarf_Off ref = die_attr_ref(dw, die, name);
	tdesc_t *tdp;

	if ((tdp = tdesc_lookup(dw, ref)) != NULL)
		return (tdp);

	return (die_add(dw, ref));
}