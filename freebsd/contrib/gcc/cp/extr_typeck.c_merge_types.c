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
struct TYPE_2__ {scalar_t__ (* merge_type_attributes ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
#define  ARRAY_TYPE 134 
#define  FUNCTION_TYPE 133 
#define  METHOD_TYPE 132 
 scalar_t__ NULL_TREE ; 
#define  OFFSET_TYPE 131 
#define  POINTER_TYPE 130 
#define  REFERENCE_TYPE 129 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
#define  TYPENAME_TYPE 128 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_FN_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_POINTED_TO_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_RAISES_EXCEPTIONS (scalar_t__) ; 
 scalar_t__ attribute_list_equal (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_cplus_array_type (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_exception_variant (scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_type (scalar_t__,scalar_t__) ; 
 scalar_t__ build_method_type_directly (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_pointer_type (scalar_t__) ; 
 scalar_t__ build_ptrmem_type (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_ptrmemfunc_type (scalar_t__) ; 
 scalar_t__ build_reference_type (scalar_t__) ; 
 scalar_t__ build_type_attribute_variant (scalar_t__,scalar_t__) ; 
 scalar_t__ commonparms (scalar_t__,scalar_t__) ; 
 scalar_t__ cp_build_qualified_type (scalar_t__,int) ; 
 scalar_t__ cp_build_type_attribute_variant (scalar_t__,scalar_t__) ; 
 int cp_type_quals (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ original_type (scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 TYPE_1__ targetm ; 
 scalar_t__ void_type_node ; 

tree
merge_types (tree t1, tree t2)
{
  enum tree_code code1;
  enum tree_code code2;
  tree attributes;

  /* Save time if the two types are the same.  */
  if (t1 == t2)
    return t1;
  if (original_type (t1) == original_type (t2))
    return t1;

  /* If one type is nonsense, use the other.  */
  if (t1 == error_mark_node)
    return t2;
  if (t2 == error_mark_node)
    return t1;

  /* Merge the attributes.  */
  attributes = (*targetm.merge_type_attributes) (t1, t2);

  if (TYPE_PTRMEMFUNC_P (t1))
    t1 = TYPE_PTRMEMFUNC_FN_TYPE (t1);
  if (TYPE_PTRMEMFUNC_P (t2))
    t2 = TYPE_PTRMEMFUNC_FN_TYPE (t2);

  code1 = TREE_CODE (t1);
  code2 = TREE_CODE (t2);

  switch (code1)
    {
    case POINTER_TYPE:
    case REFERENCE_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	tree target = merge_types (TREE_TYPE (t1), TREE_TYPE (t2));
	int quals = cp_type_quals (t1);

	if (code1 == POINTER_TYPE)
	  t1 = build_pointer_type (target);
	else
	  t1 = build_reference_type (target);
	t1 = build_type_attribute_variant (t1, attributes);
	t1 = cp_build_qualified_type (t1, quals);

	if (TREE_CODE (target) == METHOD_TYPE)
	  t1 = build_ptrmemfunc_type (t1);

	return t1;
      }

    case OFFSET_TYPE:
      {
	int quals;
	tree pointee;
	quals = cp_type_quals (t1);
	pointee = merge_types (TYPE_PTRMEM_POINTED_TO_TYPE (t1),
			       TYPE_PTRMEM_POINTED_TO_TYPE (t2));
	t1 = build_ptrmem_type (TYPE_PTRMEM_CLASS_TYPE (t1),
				pointee);
	t1 = cp_build_qualified_type (t1, quals);
	break;
      }

    case ARRAY_TYPE:
      {
	tree elt = merge_types (TREE_TYPE (t1), TREE_TYPE (t2));
	/* Save space: see if the result is identical to one of the args.  */
	if (elt == TREE_TYPE (t1) && TYPE_DOMAIN (t1))
	  return build_type_attribute_variant (t1, attributes);
	if (elt == TREE_TYPE (t2) && TYPE_DOMAIN (t2))
	  return build_type_attribute_variant (t2, attributes);
	/* Merge the element types, and have a size if either arg has one.  */
	t1 = build_cplus_array_type
	  (elt, TYPE_DOMAIN (TYPE_DOMAIN (t1) ? t1 : t2));
	break;
      }

    case FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	tree valtype = merge_types (TREE_TYPE (t1), TREE_TYPE (t2));
	tree p1 = TYPE_ARG_TYPES (t1);
	tree p2 = TYPE_ARG_TYPES (t2);
	tree rval, raises;

	/* Save space: see if the result is identical to one of the args.  */
	if (valtype == TREE_TYPE (t1) && ! p2)
	  return cp_build_type_attribute_variant (t1, attributes);
	if (valtype == TREE_TYPE (t2) && ! p1)
	  return cp_build_type_attribute_variant (t2, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	if (p1 == NULL_TREE || TREE_VALUE (p1) == void_type_node)
	  {
	    rval = build_function_type (valtype, p2);
	    if ((raises = TYPE_RAISES_EXCEPTIONS (t2)))
	      rval = build_exception_variant (rval, raises);
	    return cp_build_type_attribute_variant (rval, attributes);
	  }
	raises = TYPE_RAISES_EXCEPTIONS (t1);
	if (p2 == NULL_TREE || TREE_VALUE (p2) == void_type_node)
	  {
	    rval = build_function_type (valtype, p1);
	    if (raises)
	      rval = build_exception_variant (rval, raises);
	    return cp_build_type_attribute_variant (rval, attributes);
	  }

	rval = build_function_type (valtype, commonparms (p1, p2));
	t1 = build_exception_variant (rval, raises);
	break;
      }

    case METHOD_TYPE:
      {
	/* Get this value the long way, since TYPE_METHOD_BASETYPE
	   is just the main variant of this.  */
	tree basetype = TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (t2)));
	tree raises = TYPE_RAISES_EXCEPTIONS (t1);
	tree t3;

	/* If this was a member function type, get back to the
	   original type of type member function (i.e., without
	   the class instance variable up front.  */
	t1 = build_function_type (TREE_TYPE (t1),
				  TREE_CHAIN (TYPE_ARG_TYPES (t1)));
	t2 = build_function_type (TREE_TYPE (t2),
				  TREE_CHAIN (TYPE_ARG_TYPES (t2)));
	t3 = merge_types (t1, t2);
	t3 = build_method_type_directly (basetype, TREE_TYPE (t3),
					 TYPE_ARG_TYPES (t3));
	t1 = build_exception_variant (t3, raises);
	break;
      }

    case TYPENAME_TYPE:
      /* There is no need to merge attributes into a TYPENAME_TYPE.
	 When the type is instantiated it will have whatever
	 attributes result from the instantiation.  */
      return t1;

    default:;
    }

  if (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
    return t1;
  else if (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
    return t2;
  else
    return cp_build_type_attribute_variant (t1, attributes);
}