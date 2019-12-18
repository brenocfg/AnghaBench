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
typedef  char* tree ;

/* Variables and functions */
 scalar_t__ CLASSTYPE_PURE_VIRTUALS (char*) ; 
 scalar_t__ CLASS_TYPE_P (char*) ; 
 char* TREE_TYPE (char*) ; 
 int /*<<< orphan*/  complete_ptr_ref_or_void_ptr_p (char*,char*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 

__attribute__((used)) static bool
is_admissible_throw_operand (tree expr)
{
  tree type = TREE_TYPE (expr);

  /* 15.1/4 [...] The type of the throw-expression shall not be an
	    incomplete type, or a pointer or a reference to an incomplete
	    type, other than void*, const void*, volatile void*, or
	    const volatile void*.  Except for these restriction and the
	    restrictions on type matching mentioned in 15.3, the operand
	    of throw is treated exactly as a function argument in a call
	    (5.2.2) or the operand of a return statement.  */
  if (!complete_ptr_ref_or_void_ptr_p (type, expr))
    return false;

  /* 10.4/3 An abstract class shall not be used as a parameter type,
	    as a function return type or as type of an explicit
	    conversion.  */
  else if (CLASS_TYPE_P (type) && CLASSTYPE_PURE_VIRTUALS (type))
    {
      error ("expression %qE of abstract class type %qT cannot "
	     "be used in throw-expression", expr, type);
      return false;
    }

  return true;
}