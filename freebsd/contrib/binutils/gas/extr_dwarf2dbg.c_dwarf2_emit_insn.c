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
struct dwarf2_line_info {int flags; } ;

/* Variables and functions */
 scalar_t__ DEBUG_DWARF2 ; 
 int DWARF2_FLAG_BASIC_BLOCK ; 
 int DWARF2_FLAG_EPILOGUE_BEGIN ; 
 int DWARF2_FLAG_PROLOGUE_END ; 
 scalar_t__ FALSE ; 
 struct dwarf2_line_info current ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  dwarf2_gen_line_info (scalar_t__,struct dwarf2_line_info*) ; 
 int /*<<< orphan*/  dwarf2_where (struct dwarf2_line_info*) ; 
 scalar_t__ frag_now_fix () ; 
 scalar_t__ loc_directive_seen ; 

void
dwarf2_emit_insn (int size)
{
  struct dwarf2_line_info loc;

  if (loc_directive_seen)
    {
      /* Use the last location established by a .loc directive, not
	 the value returned by dwarf2_where().  That calls as_where()
	 which will return either the logical input file name (foo.c)
	or the physical input file name (foo.s) and not the file name
	specified in the most recent .loc directive (eg foo.h).  */
      loc = current;

      /* Unless we generate DWARF2 debugging information for each
	 assembler line, we only emit one line symbol for one LOC.  */
      if (debug_type != DEBUG_DWARF2)
	loc_directive_seen = FALSE;
    }
  else if (debug_type != DEBUG_DWARF2)
    return;
  else
    dwarf2_where (&loc);

  dwarf2_gen_line_info (frag_now_fix () - size, &loc);

  current.flags &= ~(DWARF2_FLAG_BASIC_BLOCK
		     | DWARF2_FLAG_PROLOGUE_END
		     | DWARF2_FLAG_EPILOGUE_BEGIN);
}