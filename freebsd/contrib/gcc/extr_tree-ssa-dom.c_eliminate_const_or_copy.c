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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_lhs_or_phi_result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rhs_or_phi_arg (int /*<<< orphan*/ ) ; 
 scalar_t__ has_zero_uses (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_rhs_into_lhs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_stmt_or_phi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
eliminate_const_or_copy (tree t, bitmap interesting_names)
{
  tree lhs = get_lhs_or_phi_result (t);
  tree rhs;
  int version = SSA_NAME_VERSION (lhs);

  /* If the LHS of this statement or PHI has no uses, then we can
     just eliminate it.  This can occur if, for example, the PHI
     was created by block duplication due to threading and its only
     use was in the conditional at the end of the block which was
     deleted.  */
  if (has_zero_uses (lhs))
    {
      bitmap_clear_bit (interesting_names, version);
      remove_stmt_or_phi (t);
      return;
    }

  /* Get the RHS of the assignment or PHI node if the PHI is a
     degenerate.  */
  rhs = get_rhs_or_phi_arg (t);
  if (!rhs)
    {
      bitmap_clear_bit (interesting_names, version);
      return;
    }

  propagate_rhs_into_lhs (t, lhs, rhs, interesting_names);

  /* Note that T may well have been deleted by now, so do
     not access it, instead use the saved version # to clear
     T's entry in the worklist.  */
  bitmap_clear_bit (interesting_names, version);
}