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
struct dwarf_section {unsigned long size; int /*<<< orphan*/ * start; scalar_t__ address; } ;
struct TYPE_2__ {struct dwarf_section section; } ;

/* Variables and functions */
 char const* _ (char*) ; 
 TYPE_1__* debug_displays ; 
 size_t str ; 
 int /*<<< orphan*/  warn (char const*,unsigned long) ; 

__attribute__((used)) static const char *
fetch_indirect_string (unsigned long offset)
{
  struct dwarf_section *section = &debug_displays [str].section;

  if (section->start == NULL)
    return _("<no .debug_str section>");

  /* DWARF sections under Mach-O have non-zero addresses.  */
  offset -= section->address;
  if (offset > section->size)
    {
      warn (_("DW_FORM_strp offset too big: %lx\n"), offset);
      return _("<offset is too big>");
    }

  return (const char *) section->start + offset;
}