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
struct elim_table {int /*<<< orphan*/  initial_offset; int /*<<< orphan*/  offset; int /*<<< orphan*/  previous_offset; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int /*<<< orphan*/  INITIAL_ELIMINATION_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIAL_FRAME_POINTER_OFFSET (int /*<<< orphan*/ ) ; 
 size_t NUM_ELIMINABLE_REGS ; 
 scalar_t__ num_not_at_initial_offset ; 
 struct elim_table* reg_eliminate ; 

__attribute__((used)) static void
set_initial_elim_offsets (void)
{
  struct elim_table *ep = reg_eliminate;

#ifdef ELIMINABLE_REGS
  for (; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
    {
      INITIAL_ELIMINATION_OFFSET (ep->from, ep->to, ep->initial_offset);
      ep->previous_offset = ep->offset = ep->initial_offset;
    }
#else
  INITIAL_FRAME_POINTER_OFFSET (ep->initial_offset);
  ep->previous_offset = ep->offset = ep->initial_offset;
#endif

  num_not_at_initial_offset = 0;
}