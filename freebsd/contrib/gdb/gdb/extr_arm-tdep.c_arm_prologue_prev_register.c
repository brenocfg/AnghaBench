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
struct arm_prologue_cache {int /*<<< orphan*/  saved_regs; int /*<<< orphan*/  prev_sp; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int ARM_LR_REGNUM ; 
 int ARM_PC_REGNUM ; 
 int ARM_SP_REGNUM ; 
 void* arm_make_prologue_cache (struct frame_info*) ; 
 int not_lval ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trad_frame_prev_register (struct frame_info*,int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *,int*,void*) ; 

__attribute__((used)) static void
arm_prologue_prev_register (struct frame_info *next_frame,
			    void **this_cache,
			    int prev_regnum,
			    int *optimized,
			    enum lval_type *lvalp,
			    CORE_ADDR *addrp,
			    int *realnump,
			    void *valuep)
{
  struct arm_prologue_cache *cache;

  if (*this_cache == NULL)
    *this_cache = arm_make_prologue_cache (next_frame);
  cache = *this_cache;

  /* If we are asked to unwind the PC, then we need to return the LR
     instead.  The saved value of PC points into this frame's
     prologue, not the next frame's resume location.  */
  if (prev_regnum == ARM_PC_REGNUM)
    prev_regnum = ARM_LR_REGNUM;

  /* SP is generally not saved to the stack, but this frame is
     identified by NEXT_FRAME's stack pointer at the time of the call.
     The value was already reconstructed into PREV_SP.  */
  if (prev_regnum == ARM_SP_REGNUM)
    {
      *lvalp = not_lval;
      if (valuep)
	store_unsigned_integer (valuep, 4, cache->prev_sp);
      return;
    }

  trad_frame_prev_register (next_frame, cache->saved_regs, prev_regnum,
			    optimized, lvalp, addrp, realnump, valuep);
}