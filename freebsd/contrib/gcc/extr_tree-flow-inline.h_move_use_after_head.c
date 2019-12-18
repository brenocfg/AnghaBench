#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* use_operand_p ;
struct TYPE_10__ {struct TYPE_10__* next; } ;

/* Variables and functions */
 scalar_t__ USE_FROM_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  delink_imm_use (TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  link_imm_use_to_list (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static inline use_operand_p
move_use_after_head (use_operand_p use_p, use_operand_p head, 
		      use_operand_p last_p)
{
  gcc_assert (USE_FROM_PTR (use_p) == USE_FROM_PTR (head));
  /* Skip head when we find it.  */
  if (use_p != head)
    {
      /* If use_p is already linked in after last_p, continue.  */
      if (last_p->next == use_p)
	last_p = use_p;
      else
	{
	  /* Delink from current location, and link in at last_p.  */
	  delink_imm_use (use_p);
	  link_imm_use_to_list (use_p, last_p);
	  last_p = use_p;
	}
    }
  return last_p;
}