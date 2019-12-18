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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ADDR_BITS_REMOVE (scalar_t__) ; 
 int MIPS16_INSTLEN ; 
 int MIPS_INSTLEN ; 
 scalar_t__ NO_STOP_QUIETLY ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ VM_MIN_ADDRESS ; 
 scalar_t__ heuristic_fence_post ; 
 scalar_t__ mips_about_to_return (scalar_t__) ; 
 unsigned short mips_fetch_instruction (scalar_t__) ; 
 int /*<<< orphan*/  paddr_nz (scalar_t__) ; 
 scalar_t__ pc_is_mips16 (scalar_t__) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stop_soon ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
heuristic_proc_start (CORE_ADDR pc)
{
  CORE_ADDR start_pc;
  CORE_ADDR fence;
  int instlen;
  int seen_adjsp = 0;

  pc = ADDR_BITS_REMOVE (pc);
  start_pc = pc;
  fence = start_pc - heuristic_fence_post;
  if (start_pc == 0)
    return 0;

  if (heuristic_fence_post == UINT_MAX || fence < VM_MIN_ADDRESS)
    fence = VM_MIN_ADDRESS;

  instlen = pc_is_mips16 (pc) ? MIPS16_INSTLEN : MIPS_INSTLEN;

  /* search back for previous return */
  for (start_pc -= instlen;; start_pc -= instlen)
    if (start_pc < fence)
      {
	/* It's not clear to me why we reach this point when
	   stop_soon, but with this test, at least we
	   don't print out warnings for every child forked (eg, on
	   decstation).  22apr93 rich@cygnus.com.  */
	if (stop_soon == NO_STOP_QUIETLY)
	  {
	    static int blurb_printed = 0;

	    warning
	      ("Warning: GDB can't find the start of the function at 0x%s.",
	       paddr_nz (pc));

	    if (!blurb_printed)
	      {
		/* This actually happens frequently in embedded
		   development, when you first connect to a board
		   and your stack pointer and pc are nowhere in
		   particular.  This message needs to give people
		   in that situation enough information to
		   determine that it's no big deal.  */
		printf_filtered ("\n\
    GDB is unable to find the start of the function at 0x%s\n\
and thus can't determine the size of that function's stack frame.\n\
This means that GDB may be unable to access that stack frame, or\n\
the frames below it.\n\
    This problem is most likely caused by an invalid program counter or\n\
stack pointer.\n\
    However, if you think GDB should simply search farther back\n\
from 0x%s for code which looks like the beginning of a\n\
function, you can increase the range of the search using the `set\n\
heuristic-fence-post' command.\n", paddr_nz (pc), paddr_nz (pc));
		blurb_printed = 1;
	      }
	  }

	return 0;
      }
    else if (pc_is_mips16 (start_pc))
      {
	unsigned short inst;

	/* On MIPS16, any one of the following is likely to be the
	   start of a function:
	   entry
	   addiu sp,-n
	   daddiu sp,-n
	   extend -n followed by 'addiu sp,+n' or 'daddiu sp,+n'  */
	inst = mips_fetch_instruction (start_pc);
	if (((inst & 0xf81f) == 0xe809 && (inst & 0x700) != 0x700)	/* entry */
	    || (inst & 0xff80) == 0x6380	/* addiu sp,-n */
	    || (inst & 0xff80) == 0xfb80	/* daddiu sp,-n */
	    || ((inst & 0xf810) == 0xf010 && seen_adjsp))	/* extend -n */
	  break;
	else if ((inst & 0xff00) == 0x6300	/* addiu sp */
		 || (inst & 0xff00) == 0xfb00)	/* daddiu sp */
	  seen_adjsp = 1;
	else
	  seen_adjsp = 0;
      }
    else if (mips_about_to_return (start_pc))
      {
	start_pc += 2 * MIPS_INSTLEN;	/* skip return, and its delay slot */
	break;
      }

  return start_pc;
}