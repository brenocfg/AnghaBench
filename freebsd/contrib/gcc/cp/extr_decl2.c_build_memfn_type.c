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
typedef  int cp_cv_quals ;

/* Variables and functions */
 scalar_t__ METHOD_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (scalar_t__) ; 
 int TYPE_QUAL_RESTRICT ; 
 scalar_t__ TYPE_RAISES_EXCEPTIONS (scalar_t__) ; 
 scalar_t__ build_exception_variant (scalar_t__,scalar_t__) ; 
 scalar_t__ build_method_type_directly (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_build_qualified_type (scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 

tree
build_memfn_type (tree fntype, tree ctype, cp_cv_quals quals)
{
  tree raises;
  int type_quals;

  if (fntype == error_mark_node || ctype == error_mark_node)
    return error_mark_node;

  type_quals = quals & ~TYPE_QUAL_RESTRICT;
  ctype = cp_build_qualified_type (ctype, type_quals);
  fntype = build_method_type_directly (ctype, TREE_TYPE (fntype),
				       (TREE_CODE (fntype) == METHOD_TYPE
					? TREE_CHAIN (TYPE_ARG_TYPES (fntype))
					: TYPE_ARG_TYPES (fntype)));
  raises = TYPE_RAISES_EXCEPTIONS (fntype);
  if (raises)
    fntype = build_exception_variant (fntype, raises);

  return fntype;
}