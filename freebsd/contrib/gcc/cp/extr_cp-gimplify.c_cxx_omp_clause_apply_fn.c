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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REF ; 
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NE_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_PURPOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_ARG_TYPES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_SIZE_UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * boolean_type_node ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_and_jump (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * build_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_fold_addr_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_default_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_artificial_label () ; 
 int /*<<< orphan*/ * create_tmp_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nreverse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  size_zero_node ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * void_list_node ; 
 int /*<<< orphan*/ * void_type_node ; 

__attribute__((used)) static tree
cxx_omp_clause_apply_fn (tree fn, tree arg1, tree arg2)
{
  tree defparm, parm;
  int i;

  if (fn == NULL)
    return NULL;

  defparm = TREE_CHAIN (TYPE_ARG_TYPES (TREE_TYPE (fn)));
  if (arg2)
    defparm = TREE_CHAIN (defparm);

  if (TREE_CODE (TREE_TYPE (arg1)) == ARRAY_TYPE)
    {
      tree inner_type = TREE_TYPE (arg1);
      tree start1, end1, p1;
      tree start2 = NULL, p2 = NULL;
      tree ret = NULL, lab, t;

      start1 = arg1;
      start2 = arg2;
      do
	{
	  inner_type = TREE_TYPE (inner_type);
	  start1 = build4 (ARRAY_REF, inner_type, start1,
			   size_zero_node, NULL, NULL);
	  if (arg2)
	    start2 = build4 (ARRAY_REF, inner_type, start2,
			     size_zero_node, NULL, NULL);
	}
      while (TREE_CODE (inner_type) == ARRAY_TYPE);
      start1 = build_fold_addr_expr (start1);
      if (arg2)
	start2 = build_fold_addr_expr (start2);

      end1 = TYPE_SIZE_UNIT (TREE_TYPE (arg1));
      end1 = fold_convert (TREE_TYPE (start1), end1);
      end1 = build2 (PLUS_EXPR, TREE_TYPE (start1), start1, end1);

      p1 = create_tmp_var (TREE_TYPE (start1), NULL);
      t = build2 (MODIFY_EXPR, void_type_node, p1, start1);
      append_to_statement_list (t, &ret);

      if (arg2)
	{
	  p2 = create_tmp_var (TREE_TYPE (start2), NULL);
	  t = build2 (MODIFY_EXPR, void_type_node, p2, start2);
	  append_to_statement_list (t, &ret);
	}

      lab = create_artificial_label ();
      t = build1 (LABEL_EXPR, void_type_node, lab);
      append_to_statement_list (t, &ret);

      t = tree_cons (NULL, p1, NULL);
      if (arg2)
	t = tree_cons (NULL, p2, t);
      /* Handle default arguments.  */
      i = 1 + (arg2 != NULL);
      for (parm = defparm; parm != void_list_node; parm = TREE_CHAIN (parm))
	t = tree_cons (NULL, convert_default_arg (TREE_VALUE (parm),
						  TREE_PURPOSE (parm),
						  fn, i++), t);
      t = build_call (fn, nreverse (t));
      append_to_statement_list (t, &ret);

      t = fold_convert (TREE_TYPE (p1), TYPE_SIZE_UNIT (inner_type));
      t = build2 (PLUS_EXPR, TREE_TYPE (p1), p1, t);
      t = build2 (MODIFY_EXPR, void_type_node, p1, t);
      append_to_statement_list (t, &ret);

      if (arg2)
	{
	  t = fold_convert (TREE_TYPE (p2), TYPE_SIZE_UNIT (inner_type));
	  t = build2 (PLUS_EXPR, TREE_TYPE (p2), p2, t);
	  t = build2 (MODIFY_EXPR, void_type_node, p2, t);
	  append_to_statement_list (t, &ret);
	}

      t = build2 (NE_EXPR, boolean_type_node, p1, end1);
      t = build3 (COND_EXPR, void_type_node, t, build_and_jump (&lab), NULL);
      append_to_statement_list (t, &ret);

      return ret;
    }
  else
    {
      tree t = tree_cons (NULL, build_fold_addr_expr (arg1), NULL);
      if (arg2)
	t = tree_cons (NULL, build_fold_addr_expr (arg2), t);
      /* Handle default arguments.  */
      i = 1 + (arg2 != NULL);
      for (parm = defparm; parm != void_list_node; parm = TREE_CHAIN (parm))
	t = tree_cons (NULL, convert_default_arg (TREE_VALUE (parm),
						  TREE_PURPOSE (parm),
						  fn, i++), t);
      return build_call (fn, nreverse (t));
    }
}