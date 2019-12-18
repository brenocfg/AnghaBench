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
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  bitsizetype ; 
 scalar_t__ constructor_index ; 
 scalar_t__ constructor_max_index ; 
 scalar_t__ constructor_range_stack ; 
 scalar_t__ constructor_type ; 
 scalar_t__ convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  designator_depth ; 
 int designator_erroneous ; 
 int /*<<< orphan*/  error_init (char*) ; 
 int /*<<< orphan*/  push_range_stack (scalar_t__) ; 
 scalar_t__ set_designator (int) ; 
 scalar_t__ tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int tree_int_cst_sgn (scalar_t__) ; 

void
set_init_index (tree first, tree last)
{
  if (set_designator (1))
    return;

  designator_erroneous = 1;

  if (!INTEGRAL_TYPE_P (TREE_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (TREE_TYPE (last))))
    {
      error_init ("array index in initializer not of integer type");
      return;
    }

  if (TREE_CODE (first) != INTEGER_CST)
    error_init ("nonconstant array index in initializer");
  else if (last != 0 && TREE_CODE (last) != INTEGER_CST)
    error_init ("nonconstant array index in initializer");
  else if (TREE_CODE (constructor_type) != ARRAY_TYPE)
    error_init ("array index in non-array initializer");
  else if (tree_int_cst_sgn (first) == -1)
    error_init ("array index in initializer exceeds array bounds");
  else if (constructor_max_index
	   && tree_int_cst_lt (constructor_max_index, first))
    error_init ("array index in initializer exceeds array bounds");
  else
    {
      constructor_index = convert (bitsizetype, first);

      if (last)
	{
	  if (tree_int_cst_equal (first, last))
	    last = 0;
	  else if (tree_int_cst_lt (last, first))
	    {
	      error_init ("empty index range in initializer");
	      last = 0;
	    }
	  else
	    {
	      last = convert (bitsizetype, last);
	      if (constructor_max_index != 0
		  && tree_int_cst_lt (constructor_max_index, last))
		{
		  error_init ("array index range in initializer exceeds array bounds");
		  last = 0;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      if (constructor_range_stack || last)
	push_range_stack (last);
    }
}