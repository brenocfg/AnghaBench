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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  ARRAY_TYPE 143 
#define  BOOLEAN_TYPE 142 
#define  COMPLEX_TYPE 141 
 scalar_t__ CONTAINS_PLACEHOLDER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FIELD_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_QUALIFIER (int /*<<< orphan*/ ) ; 
#define  ENUMERAL_TYPE 140 
 int const FIELD_DECL ; 
#define  FUNCTION_TYPE 139 
#define  INTEGER_TYPE 138 
#define  METHOD_TYPE 137 
#define  OFFSET_TYPE 136 
#define  POINTER_TYPE 135 
#define  QUAL_UNION_TYPE 134 
#define  REAL_TYPE 133 
#define  RECORD_TYPE 132 
#define  REFERENCE_TYPE 131 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int type_contains_placeholder_p (scalar_t__) ; 

__attribute__((used)) static bool
type_contains_placeholder_1 (tree type)
{
  /* If the size contains a placeholder or the parent type (component type in
     the case of arrays) type involves a placeholder, this type does.  */
  if (CONTAINS_PLACEHOLDER_P (TYPE_SIZE (type))
      || CONTAINS_PLACEHOLDER_P (TYPE_SIZE_UNIT (type))
      || (TREE_TYPE (type) != 0
	  && type_contains_placeholder_p (TREE_TYPE (type))))
    return true;

  /* Now do type-specific checks.  Note that the last part of the check above
     greatly limits what we have to do below.  */
  switch (TREE_CODE (type))
    {
    case VOID_TYPE:
    case COMPLEX_TYPE:
    case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:
    case POINTER_TYPE:
    case OFFSET_TYPE:
    case REFERENCE_TYPE:
    case METHOD_TYPE:
    case FUNCTION_TYPE:
    case VECTOR_TYPE:
      return false;

    case INTEGER_TYPE:
    case REAL_TYPE:
      /* Here we just check the bounds.  */
      return (CONTAINS_PLACEHOLDER_P (TYPE_MIN_VALUE (type))
	      || CONTAINS_PLACEHOLDER_P (TYPE_MAX_VALUE (type)));

    case ARRAY_TYPE:
      /* We're already checked the component type (TREE_TYPE), so just check
	 the index type.  */
      return type_contains_placeholder_p (TYPE_DOMAIN (type));

    case RECORD_TYPE:
    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      {
	tree field;

	for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
	  if (TREE_CODE (field) == FIELD_DECL
	      && (CONTAINS_PLACEHOLDER_P (DECL_FIELD_OFFSET (field))
		  || (TREE_CODE (type) == QUAL_UNION_TYPE
		      && CONTAINS_PLACEHOLDER_P (DECL_QUALIFIER (field)))
		  || type_contains_placeholder_p (TREE_TYPE (field))))
	    return true;

	return false;
      }

    default:
      gcc_unreachable ();
    }
}