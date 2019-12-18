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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int mmxsse_to_integer; int fp_move; int sse_move; int mmx_move; } ;

/* Variables and functions */
 scalar_t__ CLASS_MAX_NREGS (int,int) ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MAYBE_FLOAT_CLASS_P (int) ; 
 scalar_t__ MAYBE_MMX_CLASS_P (int) ; 
 scalar_t__ MAYBE_SSE_CLASS_P (int) ; 
 int /*<<< orphan*/  MEMORY_MOVE_COST (int,int,int) ; 
 scalar_t__ MMX_CLASS_P (int) ; 
 scalar_t__ SSE_CLASS_P (int) ; 
 TYPE_1__* ix86_cost ; 
 scalar_t__ ix86_secondary_memory_needed (int,int,int,int /*<<< orphan*/ ) ; 

int
ix86_register_move_cost (enum machine_mode mode, enum reg_class class1,
			 enum reg_class class2)
{
  /* In case we require secondary memory, compute cost of the store followed
     by load.  In order to avoid bad register allocation choices, we need
     for this to be *at least* as high as the symmetric MEMORY_MOVE_COST.  */

  if (ix86_secondary_memory_needed (class1, class2, mode, 0))
    {
      int cost = 1;

      cost += MAX (MEMORY_MOVE_COST (mode, class1, 0),
		   MEMORY_MOVE_COST (mode, class1, 1));
      cost += MAX (MEMORY_MOVE_COST (mode, class2, 0),
		   MEMORY_MOVE_COST (mode, class2, 1));

      /* In case of copying from general_purpose_register we may emit multiple
         stores followed by single load causing memory size mismatch stall.
         Count this as arbitrarily high cost of 20.  */
      if (CLASS_MAX_NREGS (class1, mode) > CLASS_MAX_NREGS (class2, mode))
	cost += 20;

      /* In the case of FP/MMX moves, the registers actually overlap, and we
	 have to switch modes in order to treat them differently.  */
      if ((MMX_CLASS_P (class1) && MAYBE_FLOAT_CLASS_P (class2))
          || (MMX_CLASS_P (class2) && MAYBE_FLOAT_CLASS_P (class1)))
	cost += 20;

      return cost;
    }

  /* Moves between SSE/MMX and integer unit are expensive.  */
  if (MMX_CLASS_P (class1) != MMX_CLASS_P (class2)
      || SSE_CLASS_P (class1) != SSE_CLASS_P (class2))
    return ix86_cost->mmxsse_to_integer;
  if (MAYBE_FLOAT_CLASS_P (class1))
    return ix86_cost->fp_move;
  if (MAYBE_SSE_CLASS_P (class1))
    return ix86_cost->sse_move;
  if (MAYBE_MMX_CLASS_P (class1))
    return ix86_cost->mmx_move;
  return 2;
}