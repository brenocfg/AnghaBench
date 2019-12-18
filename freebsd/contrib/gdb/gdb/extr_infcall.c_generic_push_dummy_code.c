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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_breakpoint_from_pc (struct gdbarch*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  gdbarch_frame_align (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_frame_align_p (struct gdbarch*) ; 
 scalar_t__ gdbarch_inner_than (struct gdbarch*,int,int) ; 

__attribute__((used)) static CORE_ADDR
generic_push_dummy_code (struct gdbarch *gdbarch,
			 CORE_ADDR sp, CORE_ADDR funaddr, int using_gcc,
			 struct value **args, int nargs,
			 struct type *value_type,
			 CORE_ADDR *real_pc, CORE_ADDR *bp_addr)
{
  /* Something here to findout the size of a breakpoint and then
     allocate space for it on the stack.  */
  int bplen;
  /* This code assumes frame align.  */
  gdb_assert (gdbarch_frame_align_p (gdbarch));
  /* Force the stack's alignment.  The intent is to ensure that the SP
     is aligned to at least a breakpoint instruction's boundary.  */
  sp = gdbarch_frame_align (gdbarch, sp);
  /* Allocate space for, and then position the breakpoint on the
     stack.  */
  if (gdbarch_inner_than (gdbarch, 1, 2))
    {
      CORE_ADDR bppc = sp;
      gdbarch_breakpoint_from_pc (gdbarch, &bppc, &bplen);
      sp = gdbarch_frame_align (gdbarch, sp - bplen);
      (*bp_addr) = sp;
      /* Should the breakpoint size/location be re-computed here?  */
    }      
  else
    {
      (*bp_addr) = sp;
      gdbarch_breakpoint_from_pc (gdbarch, bp_addr, &bplen);
      sp = gdbarch_frame_align (gdbarch, sp + bplen);
    }
  /* Inferior resumes at the function entry point.  */
  (*real_pc) = funaddr;
  return sp;
}