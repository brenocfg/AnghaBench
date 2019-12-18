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
struct type_hash {scalar_t__ hash; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  ARRAY_TYPE 143 
#define  BOOLEAN_TYPE 142 
#define  COMPLEX_TYPE 141 
#define  ENUMERAL_TYPE 140 
#define  FUNCTION_TYPE 139 
#define  INTEGER_TYPE 138 
#define  METHOD_TYPE 137 
#define  OFFSET_TYPE 136 
#define  POINTER_TYPE 135 
#define  QUAL_UNION_TYPE 134 
#define  REAL_TYPE 133 
#define  RECORD_TYPE 132 
#define  REFERENCE_TYPE 131 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_LIST ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_METHOD_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OFFSET_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_VALUES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_VECTOR_SUBPARTS (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  attribute_list_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_list_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
type_hash_eq (const void *va, const void *vb)
{
  const struct type_hash *a = va, *b = vb;

  /* First test the things that are the same for all types.  */
  if (a->hash != b->hash
      || TREE_CODE (a->type) != TREE_CODE (b->type)
      || TREE_TYPE (a->type) != TREE_TYPE (b->type)
      || !attribute_list_equal (TYPE_ATTRIBUTES (a->type),
				 TYPE_ATTRIBUTES (b->type))
      || TYPE_ALIGN (a->type) != TYPE_ALIGN (b->type)
      || TYPE_MODE (a->type) != TYPE_MODE (b->type))
    return 0;

  switch (TREE_CODE (a->type))
    {
    case VOID_TYPE:
    case COMPLEX_TYPE:
    case POINTER_TYPE:
    case REFERENCE_TYPE:
      return 1;

    case VECTOR_TYPE:
      return TYPE_VECTOR_SUBPARTS (a->type) == TYPE_VECTOR_SUBPARTS (b->type);

    case ENUMERAL_TYPE:
      if (TYPE_VALUES (a->type) != TYPE_VALUES (b->type)
	  && !(TYPE_VALUES (a->type)
	       && TREE_CODE (TYPE_VALUES (a->type)) == TREE_LIST
	       && TYPE_VALUES (b->type)
	       && TREE_CODE (TYPE_VALUES (b->type)) == TREE_LIST
	       && type_list_equal (TYPE_VALUES (a->type),
				   TYPE_VALUES (b->type))))
	return 0;

      /* ... fall through ... */

    case INTEGER_TYPE:
    case REAL_TYPE:
    case BOOLEAN_TYPE:
      return ((TYPE_MAX_VALUE (a->type) == TYPE_MAX_VALUE (b->type)
	       || tree_int_cst_equal (TYPE_MAX_VALUE (a->type),
				      TYPE_MAX_VALUE (b->type)))
	      && (TYPE_MIN_VALUE (a->type) == TYPE_MIN_VALUE (b->type)
		  || tree_int_cst_equal (TYPE_MIN_VALUE (a->type),
					 TYPE_MIN_VALUE (b->type))));

    case OFFSET_TYPE:
      return TYPE_OFFSET_BASETYPE (a->type) == TYPE_OFFSET_BASETYPE (b->type);

    case METHOD_TYPE:
      return (TYPE_METHOD_BASETYPE (a->type) == TYPE_METHOD_BASETYPE (b->type)
	      && (TYPE_ARG_TYPES (a->type) == TYPE_ARG_TYPES (b->type)
		  || (TYPE_ARG_TYPES (a->type)
		      && TREE_CODE (TYPE_ARG_TYPES (a->type)) == TREE_LIST
		      && TYPE_ARG_TYPES (b->type)
		      && TREE_CODE (TYPE_ARG_TYPES (b->type)) == TREE_LIST
		      && type_list_equal (TYPE_ARG_TYPES (a->type),
					  TYPE_ARG_TYPES (b->type)))));

    case ARRAY_TYPE:
      return TYPE_DOMAIN (a->type) == TYPE_DOMAIN (b->type);

    case RECORD_TYPE:
    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      return (TYPE_FIELDS (a->type) == TYPE_FIELDS (b->type)
	      || (TYPE_FIELDS (a->type)
		  && TREE_CODE (TYPE_FIELDS (a->type)) == TREE_LIST
		  && TYPE_FIELDS (b->type)
		  && TREE_CODE (TYPE_FIELDS (b->type)) == TREE_LIST
		  && type_list_equal (TYPE_FIELDS (a->type),
				      TYPE_FIELDS (b->type))));

    case FUNCTION_TYPE:
      return (TYPE_ARG_TYPES (a->type) == TYPE_ARG_TYPES (b->type)
	      || (TYPE_ARG_TYPES (a->type)
		  && TREE_CODE (TYPE_ARG_TYPES (a->type)) == TREE_LIST
		  && TYPE_ARG_TYPES (b->type)
		  && TREE_CODE (TYPE_ARG_TYPES (b->type)) == TREE_LIST
		  && type_list_equal (TYPE_ARG_TYPES (a->type),
				      TYPE_ARG_TYPES (b->type))));

    default:
      return 0;
    }
}