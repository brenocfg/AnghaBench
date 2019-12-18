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
struct sra_elt {int dummy; } ;

/* Variables and functions */
#define  ARRAY_RANGE_REF 135 
#define  ARRAY_REF 134 
#define  COMPONENT_REF 133 
#define  IMAGPART_EXPR 132 
 int /*<<< orphan*/  INSERT ; 
#define  PARM_DECL 131 
 int /*<<< orphan*/  RANGE_EXPR ; 
#define  REALPART_EXPR 130 
 int RECORD_TYPE ; 
#define  RESULT_DECL 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_array_bounds_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  is_sra_candidate_decl (int /*<<< orphan*/ ) ; 
 struct sra_elt* lookup_element (struct sra_elt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_in_array_bounds_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sra_elt *
maybe_lookup_element_for_expr (tree expr)
{
  struct sra_elt *elt;
  tree child;

  switch (TREE_CODE (expr))
    {
    case VAR_DECL:
    case PARM_DECL:
    case RESULT_DECL:
      if (is_sra_candidate_decl (expr))
	return lookup_element (NULL, expr, TREE_TYPE (expr), INSERT);
      return NULL;

    case ARRAY_REF:
      /* We can't scalarize variable array indices.  */
      if (in_array_bounds_p (expr))
        child = TREE_OPERAND (expr, 1);
      else
	return NULL;
      break;

    case ARRAY_RANGE_REF:
      /* We can't scalarize variable array indices.  */
      if (range_in_array_bounds_p (expr))
	{
	  tree domain = TYPE_DOMAIN (TREE_TYPE (expr));
	  child = build2 (RANGE_EXPR, integer_type_node,
			  TYPE_MIN_VALUE (domain), TYPE_MAX_VALUE (domain));
	}
      else
	return NULL;
      break;

    case COMPONENT_REF:
      /* Don't look through unions.  */
      if (TREE_CODE (TREE_TYPE (TREE_OPERAND (expr, 0))) != RECORD_TYPE)
	return NULL;
      child = TREE_OPERAND (expr, 1);
      break;

    case REALPART_EXPR:
      child = integer_zero_node;
      break;
    case IMAGPART_EXPR:
      child = integer_one_node;
      break;

    default:
      return NULL;
    }

  elt = maybe_lookup_element_for_expr (TREE_OPERAND (expr, 0));
  if (elt)
    return lookup_element (elt, child, TREE_TYPE (expr), INSERT);
  return NULL;
}