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
struct frame_info {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ FUNCTION_START_OFFSET ; 
 scalar_t__ SKIP_PROLOGUE (scalar_t__) ; 
 scalar_t__ get_frame_func (struct frame_info*) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 

int
legacy_frameless_look_for_prologue (struct frame_info *frame)
{
  CORE_ADDR func_start;

  func_start = get_frame_func (frame);
  if (func_start)
    {
      func_start += FUNCTION_START_OFFSET;
      /* NOTE: cagney/2004-02-09: Eliminated per-architecture
         PROLOGUE_FRAMELESS_P call as architectures with custom
         implementations had all been deleted.  Eventually even this
         function can go - GDB no longer tries to differentiate
         between framed, frameless and stackless functions.  They are
         all now considered equally evil :-^.  */
      /* If skipping the prologue ends up skips nothing, there must be
         no prologue and hence no code creating a frame.  There for
         the function is "frameless" :-/.  */
      return func_start == SKIP_PROLOGUE (func_start);
    }
  else if (get_frame_pc (frame) == 0)
    /* A frame with a zero PC is usually created by dereferencing a
       NULL function pointer, normally causing an immediate core dump
       of the inferior. Mark function as frameless, as the inferior
       has no chance of setting up a stack frame.  */
    return 1;
  else
    /* If we can't find the start of the function, we don't really
       know whether the function is frameless, but we should be able
       to get a reasonable (i.e. best we can do under the
       circumstances) backtrace by saying that it isn't.  */
    return 0;
}