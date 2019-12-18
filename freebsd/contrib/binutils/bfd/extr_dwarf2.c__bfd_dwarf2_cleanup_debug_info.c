#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dwarf2_debug {int /*<<< orphan*/  dwarf_ranges_buffer; int /*<<< orphan*/  dwarf_line_buffer; int /*<<< orphan*/  dwarf_abbrev_buffer; struct comp_unit* all_comp_units; } ;
struct comp_unit {TYPE_1__* line_table; struct abbrev_info** abbrevs; struct comp_unit* next_unit; } ;
struct abbrev_info {struct abbrev_info* next; int /*<<< orphan*/  attrs; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {struct dwarf2_debug* dwarf2_find_line_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  files; int /*<<< orphan*/  dirs; } ;

/* Variables and functions */
 size_t ABBREV_HASH_SIZE ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
_bfd_dwarf2_cleanup_debug_info (bfd *abfd)
{
  struct comp_unit *each;
  struct dwarf2_debug *stash;

  if (abfd == NULL || elf_tdata (abfd) == NULL)
    return;

  stash = elf_tdata (abfd)->dwarf2_find_line_info;

  if (stash == NULL)
    return;

  for (each = stash->all_comp_units; each; each = each->next_unit)
    {
      struct abbrev_info **abbrevs = each->abbrevs;
      size_t i;

      for (i = 0; i < ABBREV_HASH_SIZE; i++)
	{
	  struct abbrev_info *abbrev = abbrevs[i];

	  while (abbrev)
	    {
	      free (abbrev->attrs);
	      abbrev = abbrev->next;
	    }
	}

      if (each->line_table)
	{
	  free (each->line_table->dirs);
	  free (each->line_table->files);
	}
    }

  free (stash->dwarf_abbrev_buffer);
  free (stash->dwarf_line_buffer);
  free (stash->dwarf_ranges_buffer);
}