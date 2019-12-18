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
struct sra_elt {int /*<<< orphan*/  type; int /*<<< orphan*/  element; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RANGE_REF ; 
 int /*<<< orphan*/  ARRAY_REF ; 
#define  ARRAY_TYPE 130 
#define  COMPLEX_TYPE 129 
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_FIELD_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
 int RANGE_EXPR ; 
 int /*<<< orphan*/  REALPART_EXPR ; 
#define  RECORD_TYPE 128 
 int /*<<< orphan*/  TODO_update_smt_usage ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_compatible_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  todoflags ; 

__attribute__((used)) static tree
generate_one_element_ref (struct sra_elt *elt, tree base)
{
  switch (TREE_CODE (TREE_TYPE (base)))
    {
    case RECORD_TYPE:
      {
	tree field = elt->element;

	/* Watch out for compatible records with differing field lists.  */
	if (DECL_FIELD_CONTEXT (field) != TYPE_MAIN_VARIANT (TREE_TYPE (base)))
	  field = find_compatible_field (TREE_TYPE (base), field);

        return build3 (COMPONENT_REF, elt->type, base, field, NULL);
      }

    case ARRAY_TYPE:
      todoflags |= TODO_update_smt_usage;
      if (TREE_CODE (elt->element) == RANGE_EXPR)
	return build4 (ARRAY_RANGE_REF, elt->type, base,
		       TREE_OPERAND (elt->element, 0), NULL, NULL);
      else
	return build4 (ARRAY_REF, elt->type, base, elt->element, NULL, NULL);

    case COMPLEX_TYPE:
      if (elt->element == integer_zero_node)
	return build1 (REALPART_EXPR, elt->type, base);
      else
	return build1 (IMAGPART_EXPR, elt->type, base);

    default:
      gcc_unreachable ();
    }
}