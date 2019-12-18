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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ BASELINK ; 
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_EXTERNAL_LINKAGE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ instantiate_type (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tf_none ; 

__attribute__((used)) static tree
convert_nontype_argument_function (tree type, tree expr)
{
  tree fns = expr;
  tree fn, fn_no_ptr;

  fn = instantiate_type (type, fns, tf_none);
  if (fn == error_mark_node)
    return error_mark_node;

  fn_no_ptr = fn;
  if (TREE_CODE (fn_no_ptr) == ADDR_EXPR)
    fn_no_ptr = TREE_OPERAND (fn_no_ptr, 0);
  if (TREE_CODE (fn_no_ptr) == BASELINK)
    fn_no_ptr = BASELINK_FUNCTIONS (fn_no_ptr);
 
  /* [temp.arg.nontype]/1

     A template-argument for a non-type, non-template template-parameter
     shall be one of:
     [...]
     -- the address of an object or function with external linkage.  */
  if (!DECL_EXTERNAL_LINKAGE_P (fn_no_ptr))
    {
      error ("%qE is not a valid template argument for type %qT "
	     "because function %qD has not external linkage",
	     expr, type, fn_no_ptr);
      return NULL_TREE;
    }

  return fn;
}