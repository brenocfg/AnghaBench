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
struct axs_value {int kind; void* type; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (void*) ; 
 scalar_t__ TYPE_CODE_FUNC ; 
#define  axs_lvalue_memory 130 
#define  axs_lvalue_register 129 
#define  axs_rvalue 128 
 int /*<<< orphan*/  error (char*) ; 
 void* lookup_pointer_type (void*) ; 

__attribute__((used)) static void
gen_address_of (struct agent_expr *ax, struct axs_value *value)
{
  /* Special case for taking the address of a function.  The ANSI
     standard describes this as a special case, too, so this
     arrangement is not without motivation.  */
  if (TYPE_CODE (value->type) == TYPE_CODE_FUNC)
    /* The value's already an rvalue on the stack, so we just need to
       change the type.  */
    value->type = lookup_pointer_type (value->type);
  else
    switch (value->kind)
      {
      case axs_rvalue:
	error ("Operand of `&' is an rvalue, which has no address.");

      case axs_lvalue_register:
	error ("Operand of `&' is in a register, and has no address.");

      case axs_lvalue_memory:
	value->kind = axs_rvalue;
	value->type = lookup_pointer_type (value->type);
	break;
      }
}