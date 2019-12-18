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
struct sra_elt {int /*<<< orphan*/  element; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  ARRAY_TYPE 130 
#define  COMPLEX_TYPE 129 
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_MODE (int /*<<< orphan*/ ) ; 
 int FIELD_DECL ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
#define  RECORD_TYPE 128 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_unwidened (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_missing_elements_1 (struct sra_elt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_const_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
instantiate_missing_elements (struct sra_elt *elt)
{
  tree type = elt->type;

  switch (TREE_CODE (type))
    {
    case RECORD_TYPE:
      {
	tree f;
	for (f = TYPE_FIELDS (type); f ; f = TREE_CHAIN (f))
	  if (TREE_CODE (f) == FIELD_DECL)
	    {
	      tree field_type = TREE_TYPE (f);

	      /* canonicalize_component_ref() unwidens some bit-field
		 types (not marked as DECL_BIT_FIELD in C++), so we
		 must do the same, lest we may introduce type
		 mismatches.  */
	      if (INTEGRAL_TYPE_P (field_type)
		  && DECL_MODE (f) != TYPE_MODE (field_type))
		field_type = TREE_TYPE (get_unwidened (build3 (COMPONENT_REF,
							       field_type,
							       elt->element,
							       f, NULL_TREE),
						       NULL_TREE));

	      instantiate_missing_elements_1 (elt, f, field_type);
	    }
	break;
      }

    case ARRAY_TYPE:
      {
	tree i, max, subtype;

	i = TYPE_MIN_VALUE (TYPE_DOMAIN (type));
	max = TYPE_MAX_VALUE (TYPE_DOMAIN (type));
	subtype = TREE_TYPE (type);

	while (1)
	  {
	    instantiate_missing_elements_1 (elt, i, subtype);
	    if (tree_int_cst_equal (i, max))
	      break;
	    i = int_const_binop (PLUS_EXPR, i, integer_one_node, true);
	  }

	break;
      }

    case COMPLEX_TYPE:
      type = TREE_TYPE (type);
      instantiate_missing_elements_1 (elt, integer_zero_node, type);
      instantiate_missing_elements_1 (elt, integer_one_node, type);
      break;

    default:
      gcc_unreachable ();
    }
}