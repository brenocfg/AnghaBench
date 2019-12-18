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
struct gdbarch_tdep {scalar_t__ vm_min_address; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ NO_STOP_QUIETLY ; 
 scalar_t__ UINT_MAX ; 
 unsigned int alpha_read_insn (scalar_t__) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 scalar_t__ get_pc_function_start (scalar_t__) ; 
 scalar_t__ heuristic_fence_post ; 
 int /*<<< orphan*/  paddr_nz (scalar_t__) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 scalar_t__ stop_soon ; 
 int /*<<< orphan*/  warning (char*,...) ; 

__attribute__((used)) static CORE_ADDR
alpha_heuristic_proc_start (CORE_ADDR pc)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  CORE_ADDR last_non_nop = pc;
  CORE_ADDR fence = pc - heuristic_fence_post;
  CORE_ADDR orig_pc = pc;
  CORE_ADDR func;

  if (pc == 0)
    return 0;

  /* First see if we can find the start of the function from minimal
     symbol information.  This can succeed with a binary that doesn't
     have debug info, but hasn't been stripped.  */
  func = get_pc_function_start (pc);
  if (func)
    return func;

  if (heuristic_fence_post == UINT_MAX
      || fence < tdep->vm_min_address)
    fence = tdep->vm_min_address;

  /* Search back for previous return; also stop at a 0, which might be
     seen for instance before the start of a code section.  Don't include
     nops, since this usually indicates padding between functions.  */
  for (pc -= 4; pc >= fence; pc -= 4)
    {
      unsigned int insn = alpha_read_insn (pc);
      switch (insn)
	{
	case 0:			/* invalid insn */
	case 0x6bfa8001:	/* ret $31,($26),1 */
	  return last_non_nop;

	case 0x2ffe0000:	/* unop: ldq_u $31,0($30) */
	case 0x47ff041f:	/* nop: bis $31,$31,$31 */
	  break;

	default:
	  last_non_nop = pc;
	  break;
	}
    }

  /* It's not clear to me why we reach this point when stopping quietly,
     but with this test, at least we don't print out warnings for every
     child forked (eg, on decstation).  22apr93 rich@cygnus.com.  */
  if (stop_soon == NO_STOP_QUIETLY)
    {
      static int blurb_printed = 0;

      if (fence == tdep->vm_min_address)
	warning ("Hit beginning of text section without finding");
      else
	warning ("Hit heuristic-fence-post without finding");
      warning ("enclosing function for address 0x%s", paddr_nz (orig_pc));

      if (!blurb_printed)
	{
	  printf_filtered ("\
This warning occurs if you are debugging a function without any symbols\n\
(for example, in a stripped executable).  In that case, you may wish to\n\
increase the size of the search with the `set heuristic-fence-post' command.\n\
\n\
Otherwise, you told GDB there was a function where there isn't one, or\n\
(more likely) you have encountered a bug in GDB.\n");
	  blurb_printed = 1;
	}
    }

  return 0;
}