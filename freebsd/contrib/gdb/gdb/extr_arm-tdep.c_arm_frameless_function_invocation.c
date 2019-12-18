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

__attribute__((used)) static int
arm_frameless_function_invocation (struct frame_info *fi)
{
  CORE_ADDR func_start, after_prologue;
  int frameless;

  /* Sometimes we have functions that do a little setup (like saving the
     vN registers with the stmdb instruction, but DO NOT set up a frame.
     The symbol table will report this as a prologue.  However, it is
     important not to try to parse these partial frames as frames, or we
     will get really confused.

     So I will demand 3 instructions between the start & end of the
     prologue before I call it a real prologue, i.e. at least
	mov ip, sp,
	stmdb sp!, {}
	sub sp, ip, #4.  */

  func_start = (get_frame_func (fi) + FUNCTION_START_OFFSET);
  after_prologue = SKIP_PROLOGUE (func_start);

  /* There are some frameless functions whose first two instructions
     follow the standard APCS form, in which case after_prologue will
     be func_start + 8.  */

  frameless = (after_prologue < func_start + 12);
  return frameless;
}