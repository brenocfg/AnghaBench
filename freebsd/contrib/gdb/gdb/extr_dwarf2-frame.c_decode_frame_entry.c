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
struct comp_unit {char* dwarf_frame_buffer; int dwarf_frame_size; TYPE_2__* dwarf_frame_section; } ;
typedef  int ptrdiff_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__* owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* decode_frame_entry_1 (struct comp_unit*,char*,int) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static char *
decode_frame_entry (struct comp_unit *unit, char *start, int eh_frame_p)
{
  enum { NONE, ALIGN4, ALIGN8, FAIL } workaround = NONE;
  char *ret;
  const char *msg;
  ptrdiff_t start_offset;

  while (1)
    {
      ret = decode_frame_entry_1 (unit, start, eh_frame_p);
      if (ret != NULL)
	break;

      /* We have corrupt input data of some form.  */

      /* ??? Try, weakly, to work around compiler/assembler/linker bugs
	 and mismatches wrt padding and alignment of debug sections.  */
      /* Note that there is no requirement in the standard for any
	 alignment at all in the frame unwind sections.  Testing for
	 alignment before trying to interpret data would be incorrect.

	 However, GCC traditionally arranged for frame sections to be
	 sized such that the FDE length and CIE fields happen to be
	 aligned (in theory, for performance).  This, unfortunately,
	 was done with .align directives, which had the side effect of
	 forcing the section to be aligned by the linker.

	 This becomes a problem when you have some other producer that
	 creates frame sections that are not as strictly aligned.  That
	 produces a hole in the frame info that gets filled by the 
	 linker with zeros.

	 The GCC behaviour is arguably a bug, but it's effectively now
	 part of the ABI, so we're now stuck with it, at least at the
	 object file level.  A smart linker may decide, in the process
	 of compressing duplicate CIE information, that it can rewrite
	 the entire output section without this extra padding.  */

      start_offset = start - unit->dwarf_frame_buffer;
      if (workaround < ALIGN4 && (start_offset & 3) != 0)
	{
	  start += 4 - (start_offset & 3);
	  workaround = ALIGN4;
	  continue;
	}
      if (workaround < ALIGN8 && (start_offset & 7) != 0)
	{
	  start += 8 - (start_offset & 7);
	  workaround = ALIGN8;
	  continue;
	}

      /* Nothing left to try.  Arrange to return as if we've consumed
	 the entire input section.  Hopefully we'll get valid info from
	 the other of .debug_frame/.eh_frame.  */
      workaround = FAIL;
      ret = unit->dwarf_frame_buffer + unit->dwarf_frame_size;
      break;
    }

  switch (workaround)
    {
    case NONE:
      break;

    case ALIGN4:
      complaint (&symfile_complaints,
		 "Corrupt data in %s:%s; align 4 workaround apparently succeeded",
		 unit->dwarf_frame_section->owner->filename,
		 unit->dwarf_frame_section->name);
      break;

    case ALIGN8:
      complaint (&symfile_complaints,
		 "Corrupt data in %s:%s; align 8 workaround apparently succeeded",
		 unit->dwarf_frame_section->owner->filename,
		 unit->dwarf_frame_section->name);
      break;

    default:
      complaint (&symfile_complaints,
		 "Corrupt data in %s:%s",
		 unit->dwarf_frame_section->owner->filename,
		 unit->dwarf_frame_section->name);
      break;
    }

  return ret;
}