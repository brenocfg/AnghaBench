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
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  abi_version_at_least (int) ; 
 int /*<<< orphan*/  cp_tree_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ fold (scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_dependent_expression_p (scalar_t__) ; 

__attribute__((used)) static bool
comp_array_types (tree t1, tree t2, bool allow_redeclaration)
{
  tree d1;
  tree d2;
  tree max1, max2;

  if (t1 == t2)
    return true;

  /* The type of the array elements must be the same.  */
  if (!same_type_p (TREE_TYPE (t1), TREE_TYPE (t2)))
    return false;

  d1 = TYPE_DOMAIN (t1);
  d2 = TYPE_DOMAIN (t2);

  if (d1 == d2)
    return true;

  /* If one of the arrays is dimensionless, and the other has a
     dimension, they are of different types.  However, it is valid to
     write:

       extern int a[];
       int a[3];

     by [basic.link]:

       declarations for an array object can specify
       array types that differ by the presence or absence of a major
       array bound (_dcl.array_).  */
  if (!d1 || !d2)
    return allow_redeclaration;

  /* Check that the dimensions are the same.  */

  if (!cp_tree_equal (TYPE_MIN_VALUE (d1), TYPE_MIN_VALUE (d2)))
    return false;
  max1 = TYPE_MAX_VALUE (d1);
  max2 = TYPE_MAX_VALUE (d2);
  if (processing_template_decl && !abi_version_at_least (2)
      && !value_dependent_expression_p (max1)
      && !value_dependent_expression_p (max2))
    {
      /* With abi-1 we do not fold non-dependent array bounds, (and
	 consequently mangle them incorrectly).  We must therefore
	 fold them here, to verify the domains have the same
	 value.  */
      max1 = fold (max1);
      max2 = fold (max2);
    }

  if (!cp_tree_equal (max1, max2))
    return false;

  return true;
}