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
struct type {int dummy; } ;
struct axs_value {struct type* type; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_INT ; 
 int /*<<< orphan*/  aop_swap ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
 struct type* builtin_type_int ; 
 int /*<<< orphan*/  gen_conversion (struct agent_expr*,struct type*,struct type*) ; 
 scalar_t__ is_nontrivial_conversion (struct type*,struct type*) ; 
 struct type* max_type (struct type*,struct type*) ; 

__attribute__((used)) static void
gen_usual_arithmetic (struct agent_expr *ax, struct axs_value *value1,
		      struct axs_value *value2)
{
  /* Do the usual binary conversions.  */
  if (TYPE_CODE (value1->type) == TYPE_CODE_INT
      && TYPE_CODE (value2->type) == TYPE_CODE_INT)
    {
      /* The ANSI integral promotions seem to work this way: Order the
         integer types by size, and then by signedness: an n-bit
         unsigned type is considered "wider" than an n-bit signed
         type.  Promote to the "wider" of the two types, and always
         promote at least to int.  */
      struct type *target = max_type (builtin_type_int,
				      max_type (value1->type, value2->type));

      /* Deal with value2, on the top of the stack.  */
      gen_conversion (ax, value2->type, target);

      /* Deal with value1, not on the top of the stack.  Don't
         generate the `swap' instructions if we're not actually going
         to do anything.  */
      if (is_nontrivial_conversion (value1->type, target))
	{
	  ax_simple (ax, aop_swap);
	  gen_conversion (ax, value1->type, target);
	  ax_simple (ax, aop_swap);
	}

      value1->type = value2->type = target;
    }
}