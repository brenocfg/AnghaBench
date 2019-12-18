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
typedef  int tree ;
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/ * stmt_vec_info ;
typedef  int /*<<< orphan*/  loop_vec_info ;
typedef  enum vect_def_type { ____Placeholder_vect_def_type } vect_def_type ;

/* Variables and functions */
 struct loop* LOOP_VINFO_LOOP (int /*<<< orphan*/ ) ; 
 int NULL_TREE ; 
 int PHI_ARG_DEF_FROM_EDGE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHI_NODE ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  STMT_VINFO_LOOP_VINFO (int /*<<< orphan*/ *) ; 
 int STMT_VINFO_VECTYPE (int /*<<< orphan*/ *) ; 
 int STMT_VINFO_VEC_STMT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  TREE_CODE (int) ; 
 int TREE_OPERAND (int,int /*<<< orphan*/ ) ; 
 int TYPE_VECTOR_SUBPARTS (int) ; 
 int build_constructor_from_list (int,int) ; 
 int build_vector (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int get_initial_def_for_reduction (int,int,int*) ; 
 int /*<<< orphan*/  internal_error (char*) ; 
 int /*<<< orphan*/  loop_preheader_edge (struct loop*) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int tree_cons (int,int,int) ; 
#define  vect_constant_def 132 
 int /*<<< orphan*/  vect_dump ; 
#define  vect_induction_def 131 
 int vect_init_vector (int,int) ; 
#define  vect_invariant_def 130 
 int vect_is_simple_use (int,int /*<<< orphan*/ ,int*,int*,int*) ; 
#define  vect_loop_def 129 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 
#define  vect_reduction_def 128 
 int /*<<< orphan*/ * vinfo_for_stmt (int) ; 

__attribute__((used)) static tree
vect_get_vec_def_for_operand (tree op, tree stmt, tree *scalar_def)
{
  tree vec_oprnd;
  tree vec_stmt;
  tree def_stmt;
  stmt_vec_info def_stmt_info = NULL;
  stmt_vec_info stmt_vinfo = vinfo_for_stmt (stmt);
  tree vectype = STMT_VINFO_VECTYPE (stmt_vinfo);
  int nunits = TYPE_VECTOR_SUBPARTS (vectype);
  loop_vec_info loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_vinfo);
  struct loop *loop = LOOP_VINFO_LOOP (loop_vinfo);
  tree vec_inv;
  tree vec_cst;
  tree t = NULL_TREE;
  tree def;
  int i;
  enum vect_def_type dt;
  bool is_simple_use;

  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "vect_get_vec_def_for_operand: ");
      print_generic_expr (vect_dump, op, TDF_SLIM);
    }

  is_simple_use = vect_is_simple_use (op, loop_vinfo, &def_stmt, &def, &dt);
  gcc_assert (is_simple_use);
  if (vect_print_dump_info (REPORT_DETAILS))
    {
      if (def)
        {
          fprintf (vect_dump, "def =  ");
          print_generic_expr (vect_dump, def, TDF_SLIM);
        }
      if (def_stmt)
        {
          fprintf (vect_dump, "  def_stmt =  ");
          print_generic_expr (vect_dump, def_stmt, TDF_SLIM);
        }
    }

  switch (dt)
    {
    /* Case 1: operand is a constant.  */
    case vect_constant_def:
      {
	if (scalar_def) 
	  *scalar_def = op;

        /* Create 'vect_cst_ = {cst,cst,...,cst}'  */
        if (vect_print_dump_info (REPORT_DETAILS))
          fprintf (vect_dump, "Create vector_cst. nunits = %d", nunits);

        for (i = nunits - 1; i >= 0; --i)
          {
            t = tree_cons (NULL_TREE, op, t);
          }
        vec_cst = build_vector (vectype, t);
        return vect_init_vector (stmt, vec_cst);
      }

    /* Case 2: operand is defined outside the loop - loop invariant.  */
    case vect_invariant_def:
      {
	if (scalar_def) 
	  *scalar_def = def;

        /* Create 'vec_inv = {inv,inv,..,inv}'  */
        if (vect_print_dump_info (REPORT_DETAILS))
          fprintf (vect_dump, "Create vector_inv.");

        for (i = nunits - 1; i >= 0; --i)
          {
            t = tree_cons (NULL_TREE, def, t);
          }

	/* FIXME: use build_constructor directly.  */
        vec_inv = build_constructor_from_list (vectype, t);
        return vect_init_vector (stmt, vec_inv);
      }

    /* Case 3: operand is defined inside the loop.  */
    case vect_loop_def:
      {
	if (scalar_def) 
	  *scalar_def = def_stmt;

        /* Get the def from the vectorized stmt.  */
        def_stmt_info = vinfo_for_stmt (def_stmt);
        vec_stmt = STMT_VINFO_VEC_STMT (def_stmt_info);
        gcc_assert (vec_stmt);
        vec_oprnd = TREE_OPERAND (vec_stmt, 0);
        return vec_oprnd;
      }

    /* Case 4: operand is defined by a loop header phi - reduction  */
    case vect_reduction_def:
      {
        gcc_assert (TREE_CODE (def_stmt) == PHI_NODE);

        /* Get the def before the loop  */
        op = PHI_ARG_DEF_FROM_EDGE (def_stmt, loop_preheader_edge (loop));
        return get_initial_def_for_reduction (stmt, op, scalar_def);
     }

    /* Case 5: operand is defined by loop-header phi - induction.  */
    case vect_induction_def:
      {
        if (vect_print_dump_info (REPORT_DETAILS))
          fprintf (vect_dump, "induction - unsupported.");
        internal_error ("no support for induction"); /* FORNOW */
      }

    default:
      gcc_unreachable ();
    }
}