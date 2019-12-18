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
 int /*<<< orphan*/  CHREC_LEFT (scalar_t__) ; 
 int /*<<< orphan*/  CHREC_RIGHT (scalar_t__) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
#define  POLYNOMIAL_CHREC 128 
 int TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  evolution_function_is_invariant_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool 
evolution_function_is_affine_p (tree chrec)
{
  if (chrec == NULL_TREE)
    return false;
  
  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      if (evolution_function_is_invariant_p (CHREC_LEFT (chrec), 
					     CHREC_VARIABLE (chrec))
	  && evolution_function_is_invariant_p (CHREC_RIGHT (chrec),
						CHREC_VARIABLE (chrec)))
	return true;
      else
	return false;
      
    default:
      return false;
    }
}