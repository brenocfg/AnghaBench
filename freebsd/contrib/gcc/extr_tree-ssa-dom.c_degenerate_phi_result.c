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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ PHI_ARG_DEF (scalar_t__,int) ; 
 int PHI_NUM_ARGS (scalar_t__) ; 
 scalar_t__ PHI_RESULT (scalar_t__) ; 
 int /*<<< orphan*/  operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
degenerate_phi_result (tree phi)
{
  tree lhs = PHI_RESULT (phi);
  tree val = NULL;
  int i;

  /* Ignoring arguments which are the same as LHS, if all the remaining
     arguments are the same, then the PHI is a degenerate and has the
     value of that common argument.  */
  for (i = 0; i < PHI_NUM_ARGS (phi); i++)
    {
      tree arg = PHI_ARG_DEF (phi, i);

      if (arg == lhs)
	continue;
      else if (!val)
	val = arg;
      else if (!operand_equal_p (arg, val, 0))
	break;
    }
  return (i == PHI_NUM_ARGS (phi) ? val : NULL);
}