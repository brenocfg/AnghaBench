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
struct line_subseg {struct line_entry** ptail; struct line_entry* head; struct line_subseg* next; } ;
struct line_seg {struct line_seg* next; struct line_subseg* head; } ;
struct line_entry {int dummy; } ;
typedef  int /*<<< orphan*/ * segT ;

/* Variables and functions */
 int DWARF2_ADDR_SIZE (int /*<<< orphan*/ ) ; 
 int SEC_DEBUGGING ; 
 int SEC_READONLY ; 
 struct line_seg* all_segs ; 
 int /*<<< orphan*/  assert (struct line_seg*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  out_debug_abbrev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_debug_aranges (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_debug_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_debug_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_debug_ranges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  seg_not_empty_p (int /*<<< orphan*/ *) ; 
 int sizeof_address ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/ * subseg_new (char*,int /*<<< orphan*/ ) ; 

void
dwarf2_finish (void)
{
  segT line_seg;
  struct line_seg *s;
  segT info_seg;
  int emit_other_sections = 0;

  info_seg = bfd_get_section_by_name (stdoutput, ".debug_info");
  emit_other_sections = info_seg == NULL || !seg_not_empty_p (info_seg);

  if (!all_segs && emit_other_sections)
    /* There is no line information and no non-empty .debug_info
       section.  */
    return;

  /* Calculate the size of an address for the target machine.  */
  sizeof_address = DWARF2_ADDR_SIZE (stdoutput);

  /* Create and switch to the line number section.  */
  line_seg = subseg_new (".debug_line", 0);
  bfd_set_section_flags (stdoutput, line_seg, SEC_READONLY | SEC_DEBUGGING);

  /* For each subsection, chain the debug entries together.  */
  for (s = all_segs; s; s = s->next)
    {
      struct line_subseg *ss = s->head;
      struct line_entry **ptail = ss->ptail;

      while ((ss = ss->next) != NULL)
	{
	  *ptail = ss->head;
	  ptail = ss->ptail;
	}
    }

  out_debug_line (line_seg);

  /* If this is assembler generated line info, and there is no
     debug_info already, we need .debug_info and .debug_abbrev
     sections as well.  */
  if (emit_other_sections)
    {
      segT abbrev_seg;
      segT aranges_seg;
      segT ranges_seg;

      assert (all_segs);
      
      info_seg = subseg_new (".debug_info", 0);
      abbrev_seg = subseg_new (".debug_abbrev", 0);
      aranges_seg = subseg_new (".debug_aranges", 0);

      bfd_set_section_flags (stdoutput, info_seg,
			     SEC_READONLY | SEC_DEBUGGING);
      bfd_set_section_flags (stdoutput, abbrev_seg,
			     SEC_READONLY | SEC_DEBUGGING);
      bfd_set_section_flags (stdoutput, aranges_seg,
			     SEC_READONLY | SEC_DEBUGGING);

      record_alignment (aranges_seg, ffs (2 * sizeof_address) - 1);

      if (all_segs->next == NULL)
	ranges_seg = NULL;
      else
	{
	  ranges_seg = subseg_new (".debug_ranges", 0);
	  bfd_set_section_flags (stdoutput, ranges_seg, 
				 SEC_READONLY | SEC_DEBUGGING);
	  record_alignment (ranges_seg, ffs (2 * sizeof_address) - 1);
	  out_debug_ranges (ranges_seg);
	}

      out_debug_aranges (aranges_seg, info_seg);
      out_debug_abbrev (abbrev_seg);
      out_debug_info (info_seg, abbrev_seg, line_seg, ranges_seg);
    }
}