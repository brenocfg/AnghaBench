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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ CONSTRUCTOR ; 
 int CONSTRUCTOR_ELTS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_LIST ; 
 int VEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* VEC_index (int /*<<< orphan*/ ,int,size_t) ; 
 size_t VEC_length (int /*<<< orphan*/ ,int) ; 
 int any_value_dependent_elements_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constructor_elt ; 
 int elts ; 
 int /*<<< orphan*/  gc ; 
 int value_dependent_expression_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
value_dependent_init_p (tree init)
{
  if (TREE_CODE (init) == TREE_LIST)
    /* A parenthesized initializer, e.g.: int i (3, 2); ? */
    return any_value_dependent_elements_p (init);
  else if (TREE_CODE (init) == CONSTRUCTOR)
  /* A brace-enclosed initializer, e.g.: int i = { 3 }; ? */
    {
      VEC(constructor_elt, gc) *elts;
      size_t nelts;
      size_t i;

      elts = CONSTRUCTOR_ELTS (init);
      nelts = VEC_length (constructor_elt, elts);
      for (i = 0; i < nelts; ++i)
	if (value_dependent_init_p (VEC_index (constructor_elt,
					       elts, i)->value))
	  return true;
    }
  else
    /* It must be a simple expression, e.g., int i = 3;  */
    return value_dependent_expression_p (init);
  
  return false;
}