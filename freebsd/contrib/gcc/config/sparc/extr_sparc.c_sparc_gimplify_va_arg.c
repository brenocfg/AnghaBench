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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 int BITS_PER_WORD ; 
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 size_t BUILT_IN_MEMCPY ; 
 scalar_t__ BYTES_BIG_ENDIAN ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TARGET_ARCH64 ; 
 int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_fold_addr_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_va_arg_indirect_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fb_rvalue ; 
 int /*<<< orphan*/  fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * implicit_built_in_decls ; 
 int int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_val ; 
 scalar_t__ pass_by_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  size_int (int) ; 
 int /*<<< orphan*/  ssize_int (int) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
sparc_gimplify_va_arg (tree valist, tree type, tree *pre_p, tree *post_p)
{
  HOST_WIDE_INT size, rsize, align;
  tree addr, incr;
  bool indirect;
  tree ptrtype = build_pointer_type (type);

  if (pass_by_reference (NULL, TYPE_MODE (type), type, false))
    {
      indirect = true;
      size = rsize = UNITS_PER_WORD;
      align = 0;
    }
  else
    {
      indirect = false;
      size = int_size_in_bytes (type);
      rsize = (size + UNITS_PER_WORD - 1) & -UNITS_PER_WORD;
      align = 0;
    
      if (TARGET_ARCH64)
	{
	  /* For SPARC64, objects requiring 16-byte alignment get it.  */
	  if (TYPE_ALIGN (type) >= 2 * (unsigned) BITS_PER_WORD)
	    align = 2 * UNITS_PER_WORD;

	  /* SPARC-V9 ABI states that structures up to 16 bytes in size
	     are left-justified in their slots.  */
	  if (AGGREGATE_TYPE_P (type))
	    {
	      if (size == 0)
		size = rsize = UNITS_PER_WORD;
	      else
		size = rsize;
	    }
	}
    }

  incr = valist;
  if (align)
    {
      incr = fold (build2 (PLUS_EXPR, ptr_type_node, incr,
			   ssize_int (align - 1)));
      incr = fold (build2 (BIT_AND_EXPR, ptr_type_node, incr,
			   ssize_int (-align)));
    }

  gimplify_expr (&incr, pre_p, post_p, is_gimple_val, fb_rvalue);
  addr = incr;

  if (BYTES_BIG_ENDIAN && size < rsize)
    addr = fold (build2 (PLUS_EXPR, ptr_type_node, incr,
			 ssize_int (rsize - size)));

  if (indirect)
    {
      addr = fold_convert (build_pointer_type (ptrtype), addr);
      addr = build_va_arg_indirect_ref (addr);
    }
  /* If the address isn't aligned properly for the type,
     we may need to copy to a temporary.  
     FIXME: This is inefficient.  Usually we can do this
     in registers.  */
  else if (align == 0
	   && TYPE_ALIGN (type) > BITS_PER_WORD)
    {
      tree tmp = create_tmp_var (type, "va_arg_tmp");
      tree dest_addr = build_fold_addr_expr (tmp);

      tree copy = build_function_call_expr
	(implicit_built_in_decls[BUILT_IN_MEMCPY],
	 tree_cons (NULL_TREE, dest_addr,
		    tree_cons (NULL_TREE, addr,
			       tree_cons (NULL_TREE, size_int (rsize),
					  NULL_TREE))));

      gimplify_and_add (copy, pre_p);
      addr = dest_addr;
    }
  else
    addr = fold_convert (ptrtype, addr);

  incr = fold (build2 (PLUS_EXPR, ptr_type_node, incr, ssize_int (rsize)));
  incr = build2 (MODIFY_EXPR, ptr_type_node, valist, incr);
  gimplify_and_add (incr, post_p);

  return build_va_arg_indirect_ref (addr);
}