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
struct dwarf_section {scalar_t__ size; scalar_t__ address; int /*<<< orphan*/ * start; } ;
typedef  enum dwarf_section_display_enum { ____Placeholder_dwarf_section_display_enum } dwarf_section_display_enum ;
struct TYPE_2__ {struct dwarf_section section; } ;

/* Variables and functions */
 TYPE_1__* debug_displays ; 
 int /*<<< orphan*/  free (char*) ; 

void
free_debug_section (enum dwarf_section_display_enum debug)
{
  struct dwarf_section *section = &debug_displays [debug].section;

  if (section->start == NULL)
    return;

  free ((char *) section->start);
  section->start = NULL;
  section->address = 0;
  section->size = 0;
}