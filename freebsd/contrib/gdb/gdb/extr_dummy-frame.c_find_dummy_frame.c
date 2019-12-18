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
struct dummy_frame {scalar_t__ call_lo; scalar_t__ call_hi; scalar_t__ top; scalar_t__ fp; scalar_t__ sp; struct dummy_frame* next; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct dummy_frame* dummy_frame_stack ; 

__attribute__((used)) static struct dummy_frame *
find_dummy_frame (CORE_ADDR pc, CORE_ADDR fp)
{
  struct dummy_frame *dummyframe;

  for (dummyframe = dummy_frame_stack; dummyframe != NULL;
       dummyframe = dummyframe->next)
    {
      /* Does the PC fall within the dummy frame's breakpoint
         instruction.  If not, discard this one.  */
      if (!(pc >= dummyframe->call_lo && pc < dummyframe->call_hi))
	continue;
      /* Does the FP match?  */
      if (dummyframe->top != 0)
	{
	  /* If the target architecture explicitly saved the
	     top-of-stack before the inferior function call, assume
	     that that same architecture will always pass in an FP
	     (frame base) value that eactly matches that saved TOS.
	     Don't check the saved SP and SP as they can lead to false
	     hits.  */
	  if (fp != dummyframe->top)
	    continue;
	}
      else
	{
	  /* An older target that hasn't explicitly or implicitly
             saved the dummy frame's top-of-stack.  Try matching the
             FP against the saved SP and FP.  NOTE: If you're trying
             to fix a problem with GDB not correctly finding a dummy
             frame, check the comments that go with FRAME_ALIGN() and
             UNWIND_DUMMY_ID().  */
	  if (fp != dummyframe->fp && fp != dummyframe->sp)
	    continue;
	}
      /* The FP matches this dummy frame.  */
      return dummyframe;
    }

  return NULL;
}