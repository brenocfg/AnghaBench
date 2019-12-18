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
struct objfile {int /*<<< orphan*/  section_offsets; } ;
struct TYPE_2__ {scalar_t__ l_paddr; } ;
struct internal_lineno {TYPE_1__ l_addr; } ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int L_LNNO32 (struct internal_lineno*) ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  bfd_coff_swap_lineno_in (int /*<<< orphan*/ ,char*,struct internal_lineno*) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  current_subfile ; 
 char* linetab ; 
 long linetab_offset ; 
 long linetab_size ; 
 int /*<<< orphan*/  local_linesz ; 
 int /*<<< orphan*/  record_line (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  symfile_bfd ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static void
enter_linenos (long file_offset, int first_line,
	       int last_line, struct objfile *objfile)
{
  char *rawptr;
  struct internal_lineno lptr;

  if (!linetab)
    return;
  if (file_offset < linetab_offset)
    {
      complaint (&symfile_complaints,
		 "Line number pointer %ld lower than start of line numbers",
		 file_offset);
      if (file_offset > linetab_size)	/* Too big to be an offset? */
	return;
      file_offset += linetab_offset;	/* Try reading at that linetab offset */
    }

  rawptr = &linetab[file_offset - linetab_offset];

  /* skip first line entry for each function */
  rawptr += local_linesz;
  /* line numbers start at one for the first line of the function */
  first_line--;

  /* If the line number table is full (e.g. 64K lines in COFF debug
     info), the next function's L_LNNO32 might not be zero, so don't
     overstep the table's end in any case.  */
  while (rawptr <= &linetab[0] + linetab_size)
    {
      bfd_coff_swap_lineno_in (symfile_bfd, rawptr, &lptr);
      rawptr += local_linesz;
      /* The next function, or the sentinel, will have L_LNNO32 zero;
	 we exit. */
      if (L_LNNO32 (&lptr) && L_LNNO32 (&lptr) <= last_line)
	record_line (current_subfile, first_line + L_LNNO32 (&lptr),
		     lptr.l_addr.l_paddr
		     + ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile)));
      else
	break;
    }
}