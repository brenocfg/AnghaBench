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
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ TREE_READONLY ;

/* Variables and functions */
 int ALIGNOF_EXPR ; 
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ METHOD_TYPE ; 
 int SIZEOF_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE (scalar_t__) ; 
 scalar_t__ build_min (int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ c_sizeof_or_alignof_type (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  complete_type (scalar_t__) ; 
 int dependent_type_p (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 TYPE_1__* operator_name_info ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ size_one_node ; 
 int /*<<< orphan*/  size_type_node ; 
 scalar_t__ warn_pointer_arith ; 

tree
cxx_sizeof_or_alignof_type (tree type, enum tree_code op, bool complain)
{
  tree value;
  bool dependent_p;

  gcc_assert (op == SIZEOF_EXPR || op == ALIGNOF_EXPR);
  if (type == error_mark_node)
    return error_mark_node;

  type = non_reference (type);
  if (TREE_CODE (type) == METHOD_TYPE)
    {
      if (complain && (pedantic || warn_pointer_arith))
	pedwarn ("invalid application of %qs to a member function", 
		 operator_name_info[(int) op].name);
      value = size_one_node;
    }

  dependent_p = dependent_type_p (type);
  if (!dependent_p)
    complete_type (type);
  if (dependent_p
      /* VLA types will have a non-constant size.  In the body of an
	 uninstantiated template, we don't need to try to compute the
	 value, because the sizeof expression is not an integral
	 constant expression in that case.  And, if we do try to
	 compute the value, we'll likely end up with SAVE_EXPRs, which
	 the template substitution machinery does not expect to see.  */
      || (processing_template_decl 
	  && COMPLETE_TYPE_P (type)
	  && TREE_CODE (TYPE_SIZE (type)) != INTEGER_CST))
    {
      value = build_min (op, size_type_node, type);
      TREE_READONLY (value) = 1;
      return value;
    }

  return c_sizeof_or_alignof_type (complete_type (type),
				   op == SIZEOF_EXPR,
				   complain);
}