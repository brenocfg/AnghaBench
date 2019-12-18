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
struct axs_value {int /*<<< orphan*/  kind; int /*<<< orphan*/  type; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aop_div_unsigned ; 
 int /*<<< orphan*/  aop_mul ; 
 int /*<<< orphan*/  aop_sub ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axs_rvalue ; 
 int /*<<< orphan*/  builtin_type_long ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gen_extend (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_scale (struct agent_expr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_sub (struct agent_expr *ax, struct axs_value *value,
	 struct axs_value *value1, struct axs_value *value2)
{
  if (TYPE_CODE (value1->type) == TYPE_CODE_PTR)
    {
      /* Is it PTR - INT?  */
      if (TYPE_CODE (value2->type) == TYPE_CODE_INT)
	{
	  gen_scale (ax, aop_mul, value1->type);
	  ax_simple (ax, aop_sub);
	  gen_extend (ax, value1->type);	/* Catch overflow.  */
	  value->type = value1->type;
	}

      /* Is it PTR - PTR?  Strictly speaking, the types ought to
         match, but this is what the normal GDB expression evaluator
         tests for.  */
      else if (TYPE_CODE (value2->type) == TYPE_CODE_PTR
	       && (TYPE_LENGTH (TYPE_TARGET_TYPE (value1->type))
		   == TYPE_LENGTH (TYPE_TARGET_TYPE (value2->type))))
	{
	  ax_simple (ax, aop_sub);
	  gen_scale (ax, aop_div_unsigned, value1->type);
	  value->type = builtin_type_long;	/* FIXME --- should be ptrdiff_t */
	}
      else
	error ("\
First argument of `-' is a pointer, but second argument is neither\n\
an integer nor a pointer of the same type.");
    }

  /* Must be number + number.  */
  else if (TYPE_CODE (value1->type) == TYPE_CODE_INT
	   && TYPE_CODE (value2->type) == TYPE_CODE_INT)
    {
      ax_simple (ax, aop_sub);
      gen_extend (ax, value1->type);	/* Catch overflow.  */
      value->type = value1->type;
    }

  else
    error ("Illegal combination of types in subtraction.");

  value->kind = axs_rvalue;
}