#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* variable ;
struct TYPE_7__ {scalar_t__ offset; int /*<<< orphan*/  cur_loc; } ;
struct TYPE_6__ {int n_var_parts; TYPE_2__* var_part; } ;

/* Variables and functions */
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ variable_part_different_p (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static bool
variable_different_p (variable var1, variable var2,
		      bool compare_current_location)
{
  int i;

  if (var1 == var2)
    return false;

  if (var1->n_var_parts != var2->n_var_parts)
    return true;

  for (i = 0; i < var1->n_var_parts; i++)
    {
      if (var1->var_part[i].offset != var2->var_part[i].offset)
	return true;
      if (compare_current_location)
	{
	  if (!((REG_P (var1->var_part[i].cur_loc)
		 && REG_P (var2->var_part[i].cur_loc)
		 && (REGNO (var1->var_part[i].cur_loc)
		     == REGNO (var2->var_part[i].cur_loc)))
		|| rtx_equal_p (var1->var_part[i].cur_loc,
				var2->var_part[i].cur_loc)))
	    return true;
	}
      if (variable_part_different_p (&var1->var_part[i], &var2->var_part[i]))
	return true;
      if (variable_part_different_p (&var2->var_part[i], &var1->var_part[i]))
	return true;
    }
  return false;
}