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
struct dwarf2_cie {struct dwarf2_cie* next; } ;
struct comp_unit {struct dwarf2_cie* cie; } ;

/* Variables and functions */

__attribute__((used)) static void
add_cie (struct comp_unit *unit, struct dwarf2_cie *cie)
{
  cie->next = unit->cie;
  unit->cie = cie;
}