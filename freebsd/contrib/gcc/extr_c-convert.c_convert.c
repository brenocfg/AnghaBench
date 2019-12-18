#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_4__ {scalar_t__ (* types_compatible_p ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_3__ {char* (* invalid_conversion ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int BLOCK_POINTER_TYPE ; 
 int BOOLEAN_TYPE ; 
 int COMPLEX_TYPE ; 
 int ENUMERAL_TYPE ; 
 scalar_t__ ERROR_MARK ; 
 int INTEGER_TYPE ; 
 int POINTER_TYPE ; 
 int REAL_TYPE ; 
 int RECORD_TYPE ; 
 int REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int UNION_TYPE ; 
 int VECTOR_TYPE ; 
 scalar_t__ VOID_TYPE ; 
 scalar_t__ c_objc_common_truthvalue_conversion (scalar_t__) ; 
 int /*<<< orphan*/  convert_to_block_pointer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_complex (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_integer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_pointer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_real (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  convert_to_vector (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  error (char const*,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold (int /*<<< orphan*/ ) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 char* stub1 (scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__) ; 
 TYPE_1__ targetm ; 

tree
convert (tree type, tree expr)
{
  tree e = expr;
  enum tree_code code = TREE_CODE (type);
  const char *invalid_conv_diag;

  if (type == error_mark_node
      || expr == error_mark_node
      || TREE_TYPE (expr) == error_mark_node)
    return error_mark_node;

  if ((invalid_conv_diag
       = targetm.invalid_conversion (TREE_TYPE (expr), type)))
    {
      error (invalid_conv_diag, "");
      return error_mark_node;
    }

  if (type == TREE_TYPE (expr))
    return expr;

  if (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (TREE_TYPE (expr)))
    return fold_convert (type, expr);
  if (TREE_CODE (TREE_TYPE (expr)) == ERROR_MARK)
    return error_mark_node;
  if (TREE_CODE (TREE_TYPE (expr)) == VOID_TYPE)
    {
      error ("void value not ignored as it ought to be");
      return error_mark_node;
    }
  if (code == VOID_TYPE)
    return fold_convert (type, e);
  if (code == INTEGER_TYPE || code == ENUMERAL_TYPE)
    return fold (convert_to_integer (type, e));
  if (code == BOOLEAN_TYPE)
    return fold_convert (type, c_objc_common_truthvalue_conversion (expr));
  if (code == POINTER_TYPE || code == REFERENCE_TYPE)
    return fold (convert_to_pointer (type, e));
  /* APPLE LOCAL begin blocks (C++ ck) */
  if (code == BLOCK_POINTER_TYPE)
    return fold (convert_to_block_pointer (type, e));
  /* APPLE LOCAL end blocks (C++ ck) */
  if (code == REAL_TYPE)
    return fold (convert_to_real (type, e));
  if (code == COMPLEX_TYPE)
    return fold (convert_to_complex (type, e));
  if (code == VECTOR_TYPE)
    return fold (convert_to_vector (type, e));
  if ((code == RECORD_TYPE || code == UNION_TYPE)
      && lang_hooks.types_compatible_p (type, TREE_TYPE (expr)))
      return e;

  error ("conversion to non-scalar type requested");
  return error_mark_node;
}