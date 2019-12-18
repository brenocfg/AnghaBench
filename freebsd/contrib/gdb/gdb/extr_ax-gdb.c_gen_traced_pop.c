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
struct axs_value {int kind; TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aop_pop ; 
 int /*<<< orphan*/  aop_trace ; 
 int /*<<< orphan*/  ax_const_l (struct agent_expr*,int) ; 
 int /*<<< orphan*/  ax_reg (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
#define  axs_lvalue_memory 130 
#define  axs_lvalue_register 129 
#define  axs_rvalue 128 
 scalar_t__ trace_kludge ; 

__attribute__((used)) static void
gen_traced_pop (struct agent_expr *ax, struct axs_value *value)
{
  if (trace_kludge)
    switch (value->kind)
      {
      case axs_rvalue:
	/* We don't trace rvalues, just the lvalues necessary to
	   produce them.  So just dispose of this value.  */
	ax_simple (ax, aop_pop);
	break;

      case axs_lvalue_memory:
	{
	  int length = TYPE_LENGTH (value->type);

	  /* There's no point in trying to use a trace_quick bytecode
	     here, since "trace_quick SIZE pop" is three bytes, whereas
	     "const8 SIZE trace" is also three bytes, does the same
	     thing, and the simplest code which generates that will also
	     work correctly for objects with large sizes.  */
	  ax_const_l (ax, length);
	  ax_simple (ax, aop_trace);
	}
	break;

      case axs_lvalue_register:
	/* We need to mention the register somewhere in the bytecode,
	   so ax_reqs will pick it up and add it to the mask of
	   registers used.  */
	ax_reg (ax, value->u.reg);
	ax_simple (ax, aop_pop);
	break;
      }
  else
    /* If we're not tracing, just pop the value.  */
    ax_simple (ax, aop_pop);
}