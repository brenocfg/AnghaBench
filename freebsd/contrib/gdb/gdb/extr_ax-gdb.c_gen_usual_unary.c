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
struct axs_value {struct type* type; void* kind; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 132 
#define  TYPE_CODE_ENUM 131 
#define  TYPE_CODE_FUNC 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 void* axs_rvalue ; 
 struct type* builtin_type_int ; 
 void* lookup_pointer_type (struct type*) ; 
 int /*<<< orphan*/  require_rvalue (struct agent_expr*,struct axs_value*) ; 

__attribute__((used)) static void
gen_usual_unary (struct agent_expr *ax, struct axs_value *value)
{
  /* We don't have to generate any code for the usual integral
     conversions, since values are always represented as full-width on
     the stack.  Should we tweak the type?  */

  /* Some types require special handling.  */
  switch (TYPE_CODE (value->type))
    {
      /* Functions get converted to a pointer to the function.  */
    case TYPE_CODE_FUNC:
      value->type = lookup_pointer_type (value->type);
      value->kind = axs_rvalue;	/* Should always be true, but just in case.  */
      break;

      /* Arrays get converted to a pointer to their first element, and
         are no longer an lvalue.  */
    case TYPE_CODE_ARRAY:
      {
	struct type *elements = TYPE_TARGET_TYPE (value->type);
	value->type = lookup_pointer_type (elements);
	value->kind = axs_rvalue;
	/* We don't need to generate any code; the address of the array
	   is also the address of its first element.  */
      }
      break;

      /* Don't try to convert structures and unions to rvalues.  Let the
         consumer signal an error.  */
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      return;

      /* If the value is an enum, call it an integer.  */
    case TYPE_CODE_ENUM:
      value->type = builtin_type_int;
      break;
    }

  /* If the value is an lvalue, dereference it.  */
  require_rvalue (ax, value);
}