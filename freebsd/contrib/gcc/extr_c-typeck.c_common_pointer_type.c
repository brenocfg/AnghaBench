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
struct TYPE_2__ {scalar_t__ (* merge_type_attributes ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ BLOCK_POINTER_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int TYPE_QUALS (scalar_t__) ; 
 scalar_t__ build_block_pointer_type (scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_type_attribute_variant (scalar_t__,scalar_t__) ; 
 scalar_t__ c_build_qualified_type (scalar_t__,int) ; 
 scalar_t__ composite_type (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static tree
common_pointer_type (tree t1, tree t2)
{
  tree attributes;
  tree pointed_to_1, mv1;
  tree pointed_to_2, mv2;
  tree target;

  /* Save time if the two types are the same.  */

  if (t1 == t2) return t1;

  /* If one type is nonsense, use the other.  */
  if (t1 == error_mark_node)
    return t2;
  if (t2 == error_mark_node)
    return t1;

  /* APPLE LOCAL begin blocks 6065211 */
  gcc_assert ((TREE_CODE (t1) == POINTER_TYPE
	       && TREE_CODE (t2) == POINTER_TYPE)
	      || (TREE_CODE (t1) == BLOCK_POINTER_TYPE
		  && TREE_CODE (t2) == BLOCK_POINTER_TYPE));
  /* APPLE LOCAL end blocks 6065211 */

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  Do not lose qualifiers on
     array element types by taking the TYPE_MAIN_VARIANT.  */
  mv1 = pointed_to_1 = TREE_TYPE (t1);
  mv2 = pointed_to_2 = TREE_TYPE (t2);
  if (TREE_CODE (mv1) != ARRAY_TYPE)
    mv1 = TYPE_MAIN_VARIANT (pointed_to_1);
  if (TREE_CODE (mv2) != ARRAY_TYPE)
    mv2 = TYPE_MAIN_VARIANT (pointed_to_2);
  target = composite_type (mv1, mv2);
  /* APPLE LOCAL begin blocks 6065211 */
  t1 = c_build_qualified_type (target,
			       TYPE_QUALS (pointed_to_1) |
			       TYPE_QUALS (pointed_to_2));
  if (TREE_CODE (t2) == BLOCK_POINTER_TYPE)
    t1 = build_block_pointer_type (t1);
  else
    t1 = build_pointer_type (t1);
  /* APPLE LOCAL end blocks 6065211 */
  return build_type_attribute_variant (t1, attributes);
}