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
typedef  int /*<<< orphan*/ * lambda_linear_expression ;

/* Variables and functions */
 scalar_t__* LLE_COEFFICIENTS (int /*<<< orphan*/ *) ; 
 scalar_t__ LLE_CONSTANT (int /*<<< orphan*/ *) ; 
 scalar_t__ LLE_DENOMINATOR (int /*<<< orphan*/ *) ; 
 scalar_t__* LLE_INVARIANT_COEFFICIENTS (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
lle_equal (lambda_linear_expression lle1, lambda_linear_expression lle2,
	   int depth, int invariants)
{
  int i;

  if (lle1 == NULL || lle2 == NULL)
    return false;
  if (LLE_CONSTANT (lle1) != LLE_CONSTANT (lle2))
    return false;
  if (LLE_DENOMINATOR (lle1) != LLE_DENOMINATOR (lle2))
    return false;
  for (i = 0; i < depth; i++)
    if (LLE_COEFFICIENTS (lle1)[i] != LLE_COEFFICIENTS (lle2)[i])
      return false;
  for (i = 0; i < invariants; i++)
    if (LLE_INVARIANT_COEFFICIENTS (lle1)[i] !=
	LLE_INVARIANT_COEFFICIENTS (lle2)[i])
      return false;
  return true;
}