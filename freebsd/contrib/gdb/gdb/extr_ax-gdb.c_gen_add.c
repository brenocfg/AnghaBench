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
 int /*<<< orphan*/  aop_add ; 
 int /*<<< orphan*/  aop_mul ; 
 int /*<<< orphan*/  aop_swap ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axs_rvalue ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  gen_extend (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_scale (struct agent_expr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_add (struct agent_expr *ax, struct axs_value *value,
	 struct axs_value *value1, struct axs_value *value2, char *name)
{
  /* Is it INT+PTR?  */
  if (TYPE_CODE (value1->type) == TYPE_CODE_INT
      && TYPE_CODE (value2->type) == TYPE_CODE_PTR)
    {
      /* Swap the values and proceed normally.  */
      ax_simple (ax, aop_swap);
      gen_scale (ax, aop_mul, value2->type);
      ax_simple (ax, aop_add);
      gen_extend (ax, value2->type);	/* Catch overflow.  */
      value->type = value2->type;
    }

  /* Is it PTR+INT?  */
  else if (TYPE_CODE (value1->type) == TYPE_CODE_PTR
	   && TYPE_CODE (value2->type) == TYPE_CODE_INT)
    {
      gen_scale (ax, aop_mul, value1->type);
      ax_simple (ax, aop_add);
      gen_extend (ax, value1->type);	/* Catch overflow.  */
      value->type = value1->type;
    }

  /* Must be number + number; the usual binary conversions will have
     brought them both to the same width.  */
  else if (TYPE_CODE (value1->type) == TYPE_CODE_INT
	   && TYPE_CODE (value2->type) == TYPE_CODE_INT)
    {
      ax_simple (ax, aop_add);
      gen_extend (ax, value1->type);	/* Catch overflow.  */
      value->type = value1->type;
    }

  else
    error ("Illegal combination of types in %s.", name);

  value->kind = axs_rvalue;
}