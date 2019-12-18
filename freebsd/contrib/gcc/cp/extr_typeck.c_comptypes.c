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
struct TYPE_2__ {int (* comp_type_attributes ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
#define  ARRAY_TYPE 143 
#define  BLOCK_POINTER_TYPE 142 
#define  BOUND_TEMPLATE_TEMPLATE_PARM 141 
 int COMPARE_BASE ; 
 int COMPARE_DERIVED ; 
 int COMPARE_REDECLARATION ; 
 int COMPARE_STRICT ; 
#define  COMPLEX_TYPE 140 
 int /*<<< orphan*/  DECL_TEMPLATE_PARMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DERIVED_FROM_P (scalar_t__,scalar_t__) ; 
#define  FUNCTION_TYPE 139 
 int const INTEGER_TYPE ; 
#define  METHOD_TYPE 138 
#define  OFFSET_TYPE 137 
#define  POINTER_TYPE 136 
#define  RECORD_TYPE 135 
#define  REFERENCE_TYPE 134 
#define  TEMPLATE_TEMPLATE_PARM 133 
 int /*<<< orphan*/  TEMPLATE_TEMPLATE_PARM_TEMPLATE_DECL (scalar_t__) ; 
 int /*<<< orphan*/  TEMPLATE_TYPE_IDX (scalar_t__) ; 
 int /*<<< orphan*/  TEMPLATE_TYPE_LEVEL (scalar_t__) ; 
#define  TEMPLATE_TYPE_PARM 132 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TYPENAME_TYPE 131 
 int /*<<< orphan*/  TYPENAME_TYPE_FULLNAME (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ TYPE_FOR_JAVA (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_IDENTIFIER (scalar_t__) ; 
 scalar_t__ TYPE_IS_SIZETYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_OFFSET_BASETYPE (scalar_t__) ; 
 scalar_t__ TYPE_ORIG_SIZE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_FN_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_QUALS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_REF_CAN_ALIAS_ALL (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_TI_ARGS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_TI_TEMPLATE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_VECTOR_SUBPARTS (scalar_t__) ; 
#define  UNBOUND_CLASS_TEMPLATE 130 
#define  UNION_TYPE 129 
#define  VECTOR_TYPE 128 
 int /*<<< orphan*/  comp_array_types (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  comp_template_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comp_template_parms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compparms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_tree_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ resolve_typename_type (scalar_t__,int) ; 
 int /*<<< orphan*/  same_type_ignoring_top_level_qualifiers_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  same_type_p (scalar_t__,scalar_t__) ; 
 int stub1 (scalar_t__,scalar_t__) ; 
 TYPE_1__ targetm ; 

bool
comptypes (tree t1, tree t2, int strict)
{
  if (t1 == t2)
    return true;

  /* Suppress errors caused by previously reported errors.  */
  if (t1 == error_mark_node || t2 == error_mark_node)
    return false;

  gcc_assert (TYPE_P (t1) && TYPE_P (t2));

  /* TYPENAME_TYPEs should be resolved if the qualifying scope is the
     current instantiation.  */
  if (TREE_CODE (t1) == TYPENAME_TYPE)
    {
      tree resolved = resolve_typename_type (t1, /*only_current_p=*/true);

      if (resolved != error_mark_node)
	t1 = resolved;
    }

  if (TREE_CODE (t2) == TYPENAME_TYPE)
    {
      tree resolved = resolve_typename_type (t2, /*only_current_p=*/true);

      if (resolved != error_mark_node)
	t2 = resolved;
    }

  /* If either type is the internal version of sizetype, use the
     language version.  */
  if (TREE_CODE (t1) == INTEGER_TYPE && TYPE_IS_SIZETYPE (t1)
      && TYPE_ORIG_SIZE_TYPE (t1))
    t1 = TYPE_ORIG_SIZE_TYPE (t1);

  if (TREE_CODE (t2) == INTEGER_TYPE && TYPE_IS_SIZETYPE (t2)
      && TYPE_ORIG_SIZE_TYPE (t2))
    t2 = TYPE_ORIG_SIZE_TYPE (t2);

  if (TYPE_PTRMEMFUNC_P (t1))
    t1 = TYPE_PTRMEMFUNC_FN_TYPE (t1);
  if (TYPE_PTRMEMFUNC_P (t2))
    t2 = TYPE_PTRMEMFUNC_FN_TYPE (t2);

  /* Different classes of types can't be compatible.  */
  if (TREE_CODE (t1) != TREE_CODE (t2))
    return false;

  /* Qualifiers must match.  For array types, we will check when we
     recur on the array element types.  */
  if (TREE_CODE (t1) != ARRAY_TYPE
      && TYPE_QUALS (t1) != TYPE_QUALS (t2))
    return false;
  if (TYPE_FOR_JAVA (t1) != TYPE_FOR_JAVA (t2))
    return false;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  if (TREE_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    return true;

  /* Compare the types.  Break out if they could be the same.  */
  switch (TREE_CODE (t1))
    {
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
      if (TEMPLATE_TYPE_IDX (t1) != TEMPLATE_TYPE_IDX (t2)
	  || TEMPLATE_TYPE_LEVEL (t1) != TEMPLATE_TYPE_LEVEL (t2))
	return false;
      if (!comp_template_parms
	  (DECL_TEMPLATE_PARMS (TEMPLATE_TEMPLATE_PARM_TEMPLATE_DECL (t1)),
	   DECL_TEMPLATE_PARMS (TEMPLATE_TEMPLATE_PARM_TEMPLATE_DECL (t2))))
	return false;
      if (TREE_CODE (t1) == TEMPLATE_TEMPLATE_PARM)
	break;
      /* Don't check inheritance.  */
      strict = COMPARE_STRICT;
      /* Fall through.  */

    case RECORD_TYPE:
    case UNION_TYPE:
      if (TYPE_TEMPLATE_INFO (t1) && TYPE_TEMPLATE_INFO (t2)
	  && (TYPE_TI_TEMPLATE (t1) == TYPE_TI_TEMPLATE (t2)
	      || TREE_CODE (t1) == BOUND_TEMPLATE_TEMPLATE_PARM)
	  && comp_template_args (TYPE_TI_ARGS (t1), TYPE_TI_ARGS (t2)))
	break;

      if ((strict & COMPARE_BASE) && DERIVED_FROM_P (t1, t2))
	break;
      else if ((strict & COMPARE_DERIVED) && DERIVED_FROM_P (t2, t1))
	break;

      return false;

    case OFFSET_TYPE:
      if (!comptypes (TYPE_OFFSET_BASETYPE (t1), TYPE_OFFSET_BASETYPE (t2),
		      strict & ~COMPARE_REDECLARATION))
	return false;
      if (!same_type_p (TREE_TYPE (t1), TREE_TYPE (t2)))
	return false;
      break;

      /* APPLE LOCAL begin blocks 6040305 */
      case BLOCK_POINTER_TYPE:
	 if (TREE_CODE (t2) == BLOCK_POINTER_TYPE)
	 {
	   tree pt1 = TREE_TYPE (t1);
	   tree pt2 = TREE_TYPE (t2);
	   if (!same_type_ignoring_top_level_qualifiers_p (TREE_TYPE (pt1),
							  TREE_TYPE (pt2)))
	     return false;
	   if (!compparms (TYPE_ARG_TYPES (pt1), TYPE_ARG_TYPES (pt2)))
	     return false;
	   break;
	 }
	 /* APPLE LOCAL end blocks 6040305 */

    case POINTER_TYPE:
    case REFERENCE_TYPE:
      if (TYPE_MODE (t1) != TYPE_MODE (t2)
	  || TYPE_REF_CAN_ALIAS_ALL (t1) != TYPE_REF_CAN_ALIAS_ALL (t2)
	  || !same_type_p (TREE_TYPE (t1), TREE_TYPE (t2)))
	return false;
      break;

    case METHOD_TYPE:
    case FUNCTION_TYPE:
      if (!same_type_p (TREE_TYPE (t1), TREE_TYPE (t2)))
	return false;
      if (!compparms (TYPE_ARG_TYPES (t1), TYPE_ARG_TYPES (t2)))
	return false;
      break;

    case ARRAY_TYPE:
      /* Target types must match incl. qualifiers.  */
      if (!comp_array_types (t1, t2, !!(strict & COMPARE_REDECLARATION)))
	return false;
      break;

    case TEMPLATE_TYPE_PARM:
      if (TEMPLATE_TYPE_IDX (t1) != TEMPLATE_TYPE_IDX (t2)
	  || TEMPLATE_TYPE_LEVEL (t1) != TEMPLATE_TYPE_LEVEL (t2))
	return false;
      break;

    case TYPENAME_TYPE:
      if (!cp_tree_equal (TYPENAME_TYPE_FULLNAME (t1),
			  TYPENAME_TYPE_FULLNAME (t2)))
	return false;
      if (!same_type_p (TYPE_CONTEXT (t1), TYPE_CONTEXT (t2)))
	return false;
      break;

    case UNBOUND_CLASS_TEMPLATE:
      if (!cp_tree_equal (TYPE_IDENTIFIER (t1), TYPE_IDENTIFIER (t2)))
	return false;
      if (!same_type_p (TYPE_CONTEXT (t1), TYPE_CONTEXT (t2)))
	return false;
      break;

    case COMPLEX_TYPE:
      if (!same_type_p (TREE_TYPE (t1), TREE_TYPE (t2)))
	return false;
      break;

    case VECTOR_TYPE:
      if (TYPE_VECTOR_SUBPARTS (t1) != TYPE_VECTOR_SUBPARTS (t2)
	  || !same_type_p (TREE_TYPE (t1), TREE_TYPE (t2)))
	return false;
      break;

    default:
      return false;
    }

  /* If we get here, we know that from a target independent POV the
     types are the same.  Make sure the target attributes are also
     the same.  */
  return targetm.comp_type_attributes (t1, t2);
}