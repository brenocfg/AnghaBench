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
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct axs_value {int kind; int /*<<< orphan*/  type; TYPE_1__ u; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax_reg (struct agent_expr*,int /*<<< orphan*/ ) ; 
#define  axs_lvalue_memory 130 
#define  axs_lvalue_register 129 
#define  axs_rvalue 128 
 int /*<<< orphan*/  gen_extend (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_fetch (struct agent_expr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
require_rvalue (struct agent_expr *ax, struct axs_value *value)
{
  switch (value->kind)
    {
    case axs_rvalue:
      /* It's already an rvalue.  */
      break;

    case axs_lvalue_memory:
      /* The top of stack is the address of the object.  Dereference.  */
      gen_fetch (ax, value->type);
      break;

    case axs_lvalue_register:
      /* There's nothing on the stack, but value->u.reg is the
         register number containing the value.

         When we add floating-point support, this is going to have to
         change.  What about SPARC register pairs, for example?  */
      ax_reg (ax, value->u.reg);
      gen_extend (ax, value->type);
      break;
    }

  value->kind = axs_rvalue;
}