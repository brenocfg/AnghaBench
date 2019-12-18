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
typedef  char* tree ;
struct TYPE_2__ {char* (* merge_type_attributes ) (char*,char*) ;} ;

/* Variables and functions */
 scalar_t__ CLASS_TYPE_P (char*) ; 
 scalar_t__ DERIVED_FROM_P (char*,char*) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_TYPE (char*) ; 
 scalar_t__ TYPE_PTRFN_P (char*) ; 
 char* TYPE_PTRMEM_CLASS_TYPE (char*) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (char*) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (char*) ; 
 int TYPE_QUALS (char*) ; 
 scalar_t__ VOID_TYPE_P (char*) ; 
 char* build_pointer_type (char*) ; 
 char* build_ptrmem_type (char*,int /*<<< orphan*/ ) ; 
 char* build_type_attribute_variant (char*,char*) ; 
 scalar_t__ c_dialect_objc () ; 
 char* composite_pointer_type_r (char*,char*,char const*) ; 
 char* cp_build_qualified_type (char*,int) ; 
 int cp_type_quals (char*) ; 
 int /*<<< orphan*/  error (char*,char const*,char*,char*) ; 
 char* error_mark_node ; 
 scalar_t__ null_ptr_cst_p (char*) ; 
 char* objc_common_type (char*,char*) ; 
 scalar_t__ objc_have_common_type (char*,char*,int,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,char const*) ; 
 int /*<<< orphan*/  same_type_ignoring_top_level_qualifiers_p (char*,char*) ; 
 int /*<<< orphan*/  same_type_p (char*,char*) ; 
 char* stub1 (char*,char*) ; 
 TYPE_1__ targetm ; 
 char* void_type_node ; 

tree
composite_pointer_type (tree t1, tree t2, tree arg1, tree arg2,
			const char* location)
{
  tree class1;
  tree class2;

  /* [expr.rel]

     If one operand is a null pointer constant, the composite pointer
     type is the type of the other operand.  */
  if (null_ptr_cst_p (arg1))
    return t2;
  if (null_ptr_cst_p (arg2))
    return t1;

  /* We have:

       [expr.rel]

       If one of the operands has type "pointer to cv1 void*", then
       the other has type "pointer to cv2T", and the composite pointer
       type is "pointer to cv12 void", where cv12 is the union of cv1
       and cv2.

    If either type is a pointer to void, make sure it is T1.  */
  if (TREE_CODE (t2) == POINTER_TYPE && VOID_TYPE_P (TREE_TYPE (t2)))
    {
      tree t;
      t = t1;
      t1 = t2;
      t2 = t;
    }

  /* Now, if T1 is a pointer to void, merge the qualifiers.  */
  if (TREE_CODE (t1) == POINTER_TYPE && VOID_TYPE_P (TREE_TYPE (t1)))
    {
      tree attributes;
      tree result_type;

      if (pedantic && TYPE_PTRFN_P (t2))
	pedwarn ("ISO C++ forbids %s between pointer of type %<void *%> "
		 "and pointer-to-function", location);
      result_type
	= cp_build_qualified_type (void_type_node,
				   (cp_type_quals (TREE_TYPE (t1))
				    | cp_type_quals (TREE_TYPE (t2))));
      result_type = build_pointer_type (result_type);
      /* Merge the attributes.  */
      attributes = (*targetm.merge_type_attributes) (t1, t2);
      return build_type_attribute_variant (result_type, attributes);
    }

  if (c_dialect_objc () && TREE_CODE (t1) == POINTER_TYPE
      && TREE_CODE (t2) == POINTER_TYPE)
    {
      /* APPLE LOCAL radar 4229905 - radar 6231433 */
      if (objc_have_common_type (t1, t2, -3, NULL_TREE, location))
      /* APPLE LOCAL 4154928 */
	return objc_common_type (t1, t2);
    }

  /* [expr.eq] permits the application of a pointer conversion to
     bring the pointers to a common type.  */
  if (TREE_CODE (t1) == POINTER_TYPE && TREE_CODE (t2) == POINTER_TYPE
      && CLASS_TYPE_P (TREE_TYPE (t1))
      && CLASS_TYPE_P (TREE_TYPE (t2))
      && !same_type_ignoring_top_level_qualifiers_p (TREE_TYPE (t1),
						     TREE_TYPE (t2)))
    {
      class1 = TREE_TYPE (t1);
      class2 = TREE_TYPE (t2);

      if (DERIVED_FROM_P (class1, class2))
	t2 = (build_pointer_type
	      (cp_build_qualified_type (class1, TYPE_QUALS (class2))));
      else if (DERIVED_FROM_P (class2, class1))
	t1 = (build_pointer_type
	      (cp_build_qualified_type (class2, TYPE_QUALS (class1))));
      else
	{
	  error ("%s between distinct pointer types %qT and %qT "
		 "lacks a cast", location, t1, t2);
	  return error_mark_node;
	}
    }
  /* [expr.eq] permits the application of a pointer-to-member
     conversion to change the class type of one of the types.  */
  else if (TYPE_PTR_TO_MEMBER_P (t1)
	   && !same_type_p (TYPE_PTRMEM_CLASS_TYPE (t1),
			    TYPE_PTRMEM_CLASS_TYPE (t2)))
    {
      class1 = TYPE_PTRMEM_CLASS_TYPE (t1);
      class2 = TYPE_PTRMEM_CLASS_TYPE (t2);

      if (DERIVED_FROM_P (class1, class2))
	t1 = build_ptrmem_type (class2, TYPE_PTRMEM_POINTED_TO_TYPE (t1));
      else if (DERIVED_FROM_P (class2, class1))
	t2 = build_ptrmem_type (class1, TYPE_PTRMEM_POINTED_TO_TYPE (t2));
      else
	{
	  error ("%s between distinct pointer-to-member types %qT and %qT "
		 "lacks a cast", location, t1, t2);
	  return error_mark_node;
	}
    }
  /* APPLE LOCAL begin blocks 6065211 */
  else if (TREE_CODE (t1) != TREE_CODE (t2))
    {
      error ("%s between distinct pointer types %qT and %qT "
	     "lacks a cast", location, t1, t2);
      return error_mark_node;
    }
  /* APPLE LOCAL end blocks 6065211 */

  return composite_pointer_type_r (t1, t2, location);
}