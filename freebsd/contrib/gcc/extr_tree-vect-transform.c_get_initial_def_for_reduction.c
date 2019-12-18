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
typedef  int /*<<< orphan*/  stmt_vec_info ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  DOT_PROD_EXPR 132 
 int GET_MODE_NUNITS (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
#define  MAX_EXPR 131 
#define  MIN_EXPR 130 
 int /*<<< orphan*/  NULL_TREE ; 
#define  PLUS_EXPR 129 
 scalar_t__ REAL_CST ; 
 scalar_t__ SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMT_VINFO_VECTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
#define  WIDEN_SUM_EXPR 128 
 int /*<<< orphan*/  build_constructor_from_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst0 ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_init_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vinfo_for_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_initial_def_for_reduction (tree stmt, tree init_val, tree *scalar_def)
{
  stmt_vec_info stmt_vinfo = vinfo_for_stmt (stmt);
  tree vectype = STMT_VINFO_VECTYPE (stmt_vinfo);
  int nunits = GET_MODE_NUNITS (TYPE_MODE (vectype));
  int nelements;
  enum tree_code code = TREE_CODE (TREE_OPERAND (stmt, 1));
  tree type = TREE_TYPE (init_val);
  tree def;
  tree vec, t = NULL_TREE;
  bool need_epilog_adjust;
  int i;

  gcc_assert (INTEGRAL_TYPE_P (type) || SCALAR_FLOAT_TYPE_P (type));

  switch (code)
  {
  case WIDEN_SUM_EXPR:
  case DOT_PROD_EXPR:
  case PLUS_EXPR:
    if (INTEGRAL_TYPE_P (type))
      def = build_int_cst (type, 0);
    else
      def = build_real (type, dconst0);

#ifdef ADJUST_IN_EPILOG
    /* All the 'nunits' elements are set to 0. The final result will be
       adjusted by 'init_val' at the loop epilog.  */
    nelements = nunits;
    need_epilog_adjust = true;
#else
    /* 'nunits - 1' elements are set to 0; The last element is set to 
        'init_val'.  No further adjustments at the epilog are needed.  */
    nelements = nunits - 1;
    need_epilog_adjust = false;
#endif
    break;

  case MIN_EXPR:
  case MAX_EXPR:
    def = init_val;
    nelements = nunits;
    need_epilog_adjust = false;
    break;

  default:
    gcc_unreachable ();
  }

  for (i = nelements - 1; i >= 0; --i)
    t = tree_cons (NULL_TREE, def, t);

  if (nelements == nunits - 1)
    {
      /* Set the last element of the vector.  */
      t = tree_cons (NULL_TREE, init_val, t);
      nelements += 1;
    }
  gcc_assert (nelements == nunits);
  
  if (TREE_CODE (init_val) == INTEGER_CST || TREE_CODE (init_val) == REAL_CST)
    vec = build_vector (vectype, t);
  else
    vec = build_constructor_from_list (vectype, t);
    
  if (!need_epilog_adjust)
    *scalar_def = NULL_TREE;
  else
    *scalar_def = init_val;

  return vect_init_vector (stmt, vec);
}