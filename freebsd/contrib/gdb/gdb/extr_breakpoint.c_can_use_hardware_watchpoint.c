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
struct value {scalar_t__ lval; scalar_t__ modifiable; struct value* next; } ;
struct type {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_REGION_OK_FOR_HW_WATCHPOINT (scalar_t__,int) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_LAZY (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  can_use_hw_watchpoints ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 scalar_t__ lval_memory ; 
 scalar_t__ lval_register ; 
 scalar_t__ not_lval ; 

__attribute__((used)) static int
can_use_hardware_watchpoint (struct value *v)
{
  int found_memory_cnt = 0;
  struct value *head = v;

  /* Did the user specifically forbid us to use hardware watchpoints? */
  if (!can_use_hw_watchpoints)
    return 0;

  /* Make sure that the value of the expression depends only upon
     memory contents, and values computed from them within GDB.  If we
     find any register references or function calls, we can't use a
     hardware watchpoint.

     The idea here is that evaluating an expression generates a series
     of values, one holding the value of every subexpression.  (The
     expression a*b+c has five subexpressions: a, b, a*b, c, and
     a*b+c.)  GDB's values hold almost enough information to establish
     the criteria given above --- they identify memory lvalues,
     register lvalues, computed values, etcetera.  So we can evaluate
     the expression, and then scan the chain of values that leaves
     behind to decide whether we can detect any possible change to the
     expression's final value using only hardware watchpoints.

     However, I don't think that the values returned by inferior
     function calls are special in any way.  So this function may not
     notice that an expression involving an inferior function call
     can't be watched with hardware watchpoints.  FIXME.  */
  for (; v; v = v->next)
    {
      if (VALUE_LVAL (v) == lval_memory)
	{
	  if (VALUE_LAZY (v))
	    /* A lazy memory lvalue is one that GDB never needed to fetch;
	       we either just used its address (e.g., `a' in `a.b') or
	       we never needed it at all (e.g., `a' in `a,b').  */
	    ;
	  else
	    {
	      /* Ahh, memory we actually used!  Check if we can cover
                 it with hardware watchpoints.  */
	      struct type *vtype = check_typedef (VALUE_TYPE (v));

	      /* We only watch structs and arrays if user asked for it
		 explicitly, never if they just happen to appear in a
		 middle of some value chain.  */
	      if (v == head
		  || (TYPE_CODE (vtype) != TYPE_CODE_STRUCT
		      && TYPE_CODE (vtype) != TYPE_CODE_ARRAY))
		{
		  CORE_ADDR vaddr = VALUE_ADDRESS (v) + VALUE_OFFSET (v);
		  int       len   = TYPE_LENGTH (VALUE_TYPE (v));

		  if (!TARGET_REGION_OK_FOR_HW_WATCHPOINT (vaddr, len))
		    return 0;
		  else
		    found_memory_cnt++;
		}
	    }
	}
      else if (v->lval != not_lval && v->modifiable == 0)
	return 0;	/* ??? What does this represent? */
      else if (v->lval == lval_register)
	return 0;	/* cannot watch a register with a HW watchpoint */
    }

  /* The expression itself looks suitable for using a hardware
     watchpoint, but give the target machine a chance to reject it.  */
  return found_memory_cnt;
}