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
struct value {int dummy; } ;
struct expression {TYPE_1__* elts; } ;
typedef  enum noside { ____Placeholder_noside } noside ;
struct TYPE_2__ {scalar_t__ opcode; } ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 scalar_t__ BINOP_COMMA ; 
 scalar_t__ BINOP_RANGE ; 
 int /*<<< orphan*/  NULL_TYPE ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_CONTENTS_RAW (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  evaluate_subexp (int /*<<< orphan*/ ,struct expression*,int*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ value_as_long (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONGEST
init_array_element (struct value *array, struct value *element,
		    struct expression *exp, int *pos,
		    enum noside noside, LONGEST low_bound, LONGEST high_bound)
{
  LONGEST index;
  int element_size = TYPE_LENGTH (VALUE_TYPE (element));
  if (exp->elts[*pos].opcode == BINOP_COMMA)
    {
      (*pos)++;
      init_array_element (array, element, exp, pos, noside,
			  low_bound, high_bound);
      return init_array_element (array, element,
				 exp, pos, noside, low_bound, high_bound);
    }
  else if (exp->elts[*pos].opcode == BINOP_RANGE)
    {
      LONGEST low, high;
      (*pos)++;
      low = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
      high = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
      if (low < low_bound || high > high_bound)
	error ("tuple range index out of range");
      for (index = low; index <= high; index++)
	{
	  memcpy (VALUE_CONTENTS_RAW (array)
		  + (index - low_bound) * element_size,
		  VALUE_CONTENTS (element), element_size);
	}
    }
  else
    {
      index = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
      if (index < low_bound || index > high_bound)
	error ("tuple index out of range");
      memcpy (VALUE_CONTENTS_RAW (array) + (index - low_bound) * element_size,
	      VALUE_CONTENTS (element), element_size);
    }
  return index;
}