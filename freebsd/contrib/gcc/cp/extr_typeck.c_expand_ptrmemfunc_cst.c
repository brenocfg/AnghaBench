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
 int /*<<< orphan*/  BINFO_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_VINDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_VIRTUAL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  PTRMEM_CST_MEMBER (int /*<<< orphan*/ ) ; 
 int TARGET_PTRMEMFUNC_VBIT_LOCATION ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_OBJECT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binfo_or_else (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_addr_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_delta_difference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_type_node ; 
#define  ptrmemfunc_vbit_in_delta 129 
#define  ptrmemfunc_vbit_in_pfn 128 
 int /*<<< orphan*/  vtable_entry_type ; 

void
expand_ptrmemfunc_cst (tree cst, tree *delta, tree *pfn)
{
  tree type = TREE_TYPE (cst);
  tree fn = PTRMEM_CST_MEMBER (cst);
  tree ptr_class, fn_class;

  gcc_assert (TREE_CODE (fn) == FUNCTION_DECL);

  /* The class that the function belongs to.  */
  fn_class = DECL_CONTEXT (fn);

  /* The class that we're creating a pointer to member of.  */
  ptr_class = TYPE_PTRMEMFUNC_OBJECT_TYPE (type);

  /* First, calculate the adjustment to the function's class.  */
  *delta = get_delta_difference (fn_class, ptr_class, /*force=*/0,
				 /*c_cast_p=*/0);

  if (!DECL_VIRTUAL_P (fn))
    *pfn = convert (TYPE_PTRMEMFUNC_FN_TYPE (type), build_addr_func (fn));
  else
    {
      /* If we're dealing with a virtual function, we have to adjust 'this'
	 again, to point to the base which provides the vtable entry for
	 fn; the call will do the opposite adjustment.  */
      tree orig_class = DECL_CONTEXT (fn);
      tree binfo = binfo_or_else (orig_class, fn_class);
      *delta = build2 (PLUS_EXPR, TREE_TYPE (*delta),
		       *delta, BINFO_OFFSET (binfo));
      *delta = fold_if_not_in_template (*delta);

      /* We set PFN to the vtable offset at which the function can be
	 found, plus one (unless ptrmemfunc_vbit_in_delta, in which
	 case delta is shifted left, and then incremented).  */
      *pfn = DECL_VINDEX (fn);
      *pfn = build2 (MULT_EXPR, integer_type_node, *pfn,
		     TYPE_SIZE_UNIT (vtable_entry_type));
      *pfn = fold_if_not_in_template (*pfn);

      switch (TARGET_PTRMEMFUNC_VBIT_LOCATION)
	{
	case ptrmemfunc_vbit_in_pfn:
	  *pfn = build2 (PLUS_EXPR, integer_type_node, *pfn,
			 integer_one_node);
	  *pfn = fold_if_not_in_template (*pfn);
	  break;

	case ptrmemfunc_vbit_in_delta:
	  *delta = build2 (LSHIFT_EXPR, TREE_TYPE (*delta),
			   *delta, integer_one_node);
	  *delta = fold_if_not_in_template (*delta);
	  *delta = build2 (PLUS_EXPR, TREE_TYPE (*delta),
			   *delta, integer_one_node);
	  *delta = fold_if_not_in_template (*delta);
	  break;

	default:
	  gcc_unreachable ();
	}

      *pfn = build_nop (TYPE_PTRMEMFUNC_FN_TYPE (type), *pfn);
      *pfn = fold_if_not_in_template (*pfn);
    }
}