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
struct invariant {int /*<<< orphan*/  invno; TYPE_1__* def; } ;
struct TYPE_2__ {scalar_t__ n_uses; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF_REGNO_FIRST_DEF (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ DF_REGNO_LAST_USE (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int DF_REG_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ VEC_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct invariant*) ; 
 int /*<<< orphan*/  VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ best_gain_for_invariant (struct invariant**,unsigned int*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  invariant_p ; 
 int /*<<< orphan*/  invariants ; 
 int /*<<< orphan*/  set_move_mark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_invariants_to_move (void)
{
  unsigned i, regs_used, n_inv_uses, regs_needed = 0, new_regs;
  struct invariant *inv = NULL;
  unsigned int n_regs = DF_REG_SIZE (df);

  if (!VEC_length (invariant_p, invariants))
    return;

  /* Now something slightly more involved.  First estimate the number of used
     registers.  */
  n_inv_uses = 0;

  /* We do not really do a good job in this estimation; put some initial bound
     here to stand for induction variables etc. that we do not detect.  */
  regs_used = 2;

  for (i = 0; i < n_regs; i++)
    {
      if (!DF_REGNO_FIRST_DEF (df, i) && DF_REGNO_LAST_USE (df, i))
	{
	  /* This is a value that is used but not changed inside loop.  */
	  regs_used++;
	}
    }

  for (i = 0; VEC_iterate (invariant_p, invariants, i, inv); i++)
    {
      if (inv->def)
	n_inv_uses += inv->def->n_uses;
    }

  new_regs = 0;
  while (best_gain_for_invariant (&inv, &regs_needed,
				  new_regs, regs_used, n_inv_uses) > 0)
    {
      set_move_mark (inv->invno);
      new_regs += regs_needed;
    }
}