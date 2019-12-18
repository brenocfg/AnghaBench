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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/ * parray; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 unsigned int CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current_loops ; 
 scalar_t__ evolution_function_is_constant_p (int /*<<< orphan*/ ) ; 
 scalar_t__ expr_invariant_in_loop_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
evolution_function_is_invariant_rec_p (tree chrec, int loopnum)
{
  if (evolution_function_is_constant_p (chrec))
    return true;

  if (TREE_CODE (chrec) == SSA_NAME 
      && expr_invariant_in_loop_p (current_loops->parray[loopnum],
				   chrec))
    return true;

  if (TREE_CODE (chrec) == POLYNOMIAL_CHREC)
    {
      if (CHREC_VARIABLE (chrec) == (unsigned) loopnum
	  || !evolution_function_is_invariant_rec_p (CHREC_RIGHT (chrec),
						     loopnum)
	  || !evolution_function_is_invariant_rec_p (CHREC_LEFT (chrec),
						     loopnum))
	return false;
      return true;
    }

  switch (TREE_CODE_LENGTH (TREE_CODE (chrec)))
    {
    case 2:
      if (!evolution_function_is_invariant_rec_p (TREE_OPERAND (chrec, 1),
						  loopnum))
	return false;
      
    case 1:
      if (!evolution_function_is_invariant_rec_p (TREE_OPERAND (chrec, 0),
						  loopnum))
	return false;
      return true;

    default:
      return false;
    }

  return false;
}