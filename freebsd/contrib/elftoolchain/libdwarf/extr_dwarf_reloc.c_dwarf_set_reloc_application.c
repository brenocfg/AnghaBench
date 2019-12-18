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
struct TYPE_2__ {int applyreloc; } ;

/* Variables and functions */
 TYPE_1__ _libdwarf ; 

int
dwarf_set_reloc_application(int apply)
{
	int oldapply;

	oldapply = _libdwarf.applyreloc;
	_libdwarf.applyreloc = apply;

	return (oldapply);
}