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
struct elim_table {scalar_t__ initial_offset; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  INITIAL_ELIMINATION_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  INITIAL_FRAME_POINTER_OFFSET (scalar_t__) ; 
 size_t NUM_ELIMINABLE_REGS ; 
 int /*<<< orphan*/  num_eliminable ; 
 struct elim_table* reg_eliminate ; 

__attribute__((used)) static bool
verify_initial_elim_offsets (void)
{
  HOST_WIDE_INT t;

  if (!num_eliminable)
    return true;

#ifdef ELIMINABLE_REGS
  {
   struct elim_table *ep;

   for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
     {
       INITIAL_ELIMINATION_OFFSET (ep->from, ep->to, t);
       if (t != ep->initial_offset)
	 return false;
     }
  }
#else
  INITIAL_FRAME_POINTER_OFFSET (t);
  if (t != reg_eliminate[0].initial_offset)
    return false;
#endif

  return true;
}