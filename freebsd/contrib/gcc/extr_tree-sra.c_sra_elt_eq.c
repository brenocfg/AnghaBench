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
struct sra_elt {scalar_t__ parent; scalar_t__ element; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_FIELD_CONTEXT (scalar_t__) ; 
#define  FIELD_DECL 133 
#define  INTEGER_CST 132 
#define  PARM_DECL 131 
#define  RANGE_EXPR 130 
#define  RESULT_DECL 129 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
#define  VAR_DECL 128 
 int fields_compatible_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int tree_int_cst_equal (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
sra_elt_eq (const void *x, const void *y)
{
  const struct sra_elt *a = x;
  const struct sra_elt *b = y;
  tree ae, be;

  if (a->parent != b->parent)
    return false;

  ae = a->element;
  be = b->element;

  if (ae == be)
    return true;
  if (TREE_CODE (ae) != TREE_CODE (be))
    return false;

  switch (TREE_CODE (ae))
    {
    case VAR_DECL:
    case PARM_DECL:
    case RESULT_DECL:
      /* These are all pointer unique.  */
      return false;

    case INTEGER_CST:
      /* Integers are not pointer unique, so compare their values.  */
      return tree_int_cst_equal (ae, be);

    case RANGE_EXPR:
      return
	tree_int_cst_equal (TREE_OPERAND (ae, 0), TREE_OPERAND (be, 0))
	&& tree_int_cst_equal (TREE_OPERAND (ae, 1), TREE_OPERAND (be, 1));

    case FIELD_DECL:
      /* Fields are unique within a record, but not between
	 compatible records.  */
      if (DECL_FIELD_CONTEXT (ae) == DECL_FIELD_CONTEXT (be))
	return false;
      return fields_compatible_p (ae, be);

    default:
      gcc_unreachable ();
    }
}