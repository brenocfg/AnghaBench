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
struct dwarf2_cie {scalar_t__ cie_pointer; struct dwarf2_cie* next; } ;
struct comp_unit {struct dwarf2_cie* cie; } ;
typedef  scalar_t__ ULONGEST ;

/* Variables and functions */

__attribute__((used)) static struct dwarf2_cie *
find_cie (struct comp_unit *unit, ULONGEST cie_pointer)
{
  struct dwarf2_cie *cie = unit->cie;

  while (cie)
    {
      if (cie->cie_pointer == cie_pointer)
	return cie;

      cie = cie->next;
    }

  return NULL;
}