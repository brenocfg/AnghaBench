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
typedef  enum agent_op { ____Placeholder_agent_op } agent_op ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int) ; 
 int /*<<< orphan*/  axs_rvalue ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  gen_extend (struct agent_expr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen_binop (struct agent_expr *ax, struct axs_value *value,
	   struct axs_value *value1, struct axs_value *value2, enum agent_op op,
	   enum agent_op op_unsigned, int may_carry, char *name)
{
  /* We only handle INT op INT.  */
  if ((TYPE_CODE (value1->type) != TYPE_CODE_INT)
      || (TYPE_CODE (value2->type) != TYPE_CODE_INT))
    error ("Illegal combination of types in %s.", name);

  ax_simple (ax,
	     TYPE_UNSIGNED (value1->type) ? op_unsigned : op);
  if (may_carry)
    gen_extend (ax, value1->type);	/* catch overflow */
  value->type = value1->type;
  value->kind = axs_rvalue;
}