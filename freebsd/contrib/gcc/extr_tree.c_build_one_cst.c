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
#define  BOOLEAN_TYPE 136 
#define  COMPLEX_TYPE 135 
#define  ENUMERAL_TYPE 134 
#define  INTEGER_TYPE 133 
 int /*<<< orphan*/  NULL_TREE ; 
#define  OFFSET_TYPE 132 
#define  POINTER_TYPE 131 
#define  REAL_TYPE 130 
#define  REFERENCE_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_VECTOR_SUBPARTS (int /*<<< orphan*/ ) ; 
#define  VECTOR_TYPE 128 
 int /*<<< orphan*/  build_complex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst1 ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
build_one_cst (tree type)
{
  switch (TREE_CODE (type))
    {
    case INTEGER_TYPE: case ENUMERAL_TYPE: case BOOLEAN_TYPE:
    case POINTER_TYPE: case REFERENCE_TYPE:
    case OFFSET_TYPE:
      return build_int_cst (type, 1);

    case REAL_TYPE:
      return build_real (type, dconst1);

    case VECTOR_TYPE:
      {
	tree scalar, cst;
	int i;

	scalar = build_one_cst (TREE_TYPE (type));

	/* Create 'vect_cst_ = {cst,cst,...,cst}'  */
	cst = NULL_TREE;
	for (i = TYPE_VECTOR_SUBPARTS (type); --i >= 0; )
	  cst = tree_cons (NULL_TREE, scalar, cst);

	return build_vector (type, cst);
      }

    case COMPLEX_TYPE:
      return build_complex (type,
			    build_one_cst (TREE_TYPE (type)),
			    fold_convert (TREE_TYPE (type), integer_zero_node));

    default:
      gcc_unreachable ();
    }
}