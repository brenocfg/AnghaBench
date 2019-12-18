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
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 135 
#define  TYPE_CODE_ENUM 134 
#define  TYPE_CODE_FUNC 133 
#define  TYPE_CODE_INT 132 
#define  TYPE_CODE_PTR 131 
#define  TYPE_CODE_STRUCT 130 
#define  TYPE_CODE_UNION 129 
#define  TYPE_CODE_VOID 128 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gen_conversion (struct agent_expr*,struct type*,struct type*) ; 
 int /*<<< orphan*/  require_rvalue (struct agent_expr*,struct axs_value*) ; 

__attribute__((used)) static void
gen_cast (struct agent_expr *ax, struct axs_value *value, struct type *type)
{
  /* GCC does allow casts to yield lvalues, so this should be fixed
     before merging these changes into the trunk.  */
  require_rvalue (ax, value);
  /* Dereference typedefs. */
  type = check_typedef (type);

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_PTR:
      /* It's implementation-defined, and I'll bet this is what GCC
         does.  */
      break;

    case TYPE_CODE_ARRAY:
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
    case TYPE_CODE_FUNC:
      error ("Illegal type cast: intended type must be scalar.");

    case TYPE_CODE_ENUM:
      /* We don't have to worry about the size of the value, because
         all our integral values are fully sign-extended, and when
         casting pointers we can do anything we like.  Is there any
         way for us to actually know what GCC actually does with a
         cast like this?  */
      value->type = type;
      break;

    case TYPE_CODE_INT:
      gen_conversion (ax, value->type, type);
      break;

    case TYPE_CODE_VOID:
      /* We could pop the value, and rely on everyone else to check
         the type and notice that this value doesn't occupy a stack
         slot.  But for now, leave the value on the stack, and
         preserve the "value == stack element" assumption.  */
      break;

    default:
      error ("Casts to requested type are not yet implemented.");
    }

  value->type = type;
}