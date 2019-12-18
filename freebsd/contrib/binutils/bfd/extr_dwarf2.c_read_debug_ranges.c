#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dwarf2_debug {int /*<<< orphan*/  dwarf_ranges_buffer; int /*<<< orphan*/  syms; int /*<<< orphan*/  dwarf_ranges_size; } ;
struct comp_unit {int /*<<< orphan*/ * abfd; struct dwarf2_debug* stash; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_simple_get_relocated_section_contents (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
read_debug_ranges (struct comp_unit *unit)
{
  struct dwarf2_debug *stash = unit->stash;
  if (! stash->dwarf_ranges_buffer)
    {
      bfd *abfd = unit->abfd;
      asection *msec;

      msec = bfd_get_section_by_name (abfd, ".debug_ranges");
      if (! msec)
	{
	  (*_bfd_error_handler) (_("Dwarf Error: Can't find .debug_ranges section."));
	  bfd_set_error (bfd_error_bad_value);
	  return FALSE;
	}

      stash->dwarf_ranges_size = msec->size;
      stash->dwarf_ranges_buffer
	= bfd_simple_get_relocated_section_contents (abfd, msec, NULL,
						     stash->syms);
      if (! stash->dwarf_ranges_buffer)
	return FALSE;
    }
  return TRUE;
}