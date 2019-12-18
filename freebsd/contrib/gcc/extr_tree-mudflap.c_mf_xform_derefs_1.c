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
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
#define  ARRAY_RANGE_REF 133 
#define  ARRAY_REF 132 
 int /*<<< orphan*/  BITS_PER_UNIT ; 
#define  BIT_FIELD_REF 131 
 int /*<<< orphan*/  CEIL_DIV_EXPR ; 
#define  COMPONENT_REF 130 
 int /*<<< orphan*/  DECL_BIT_FIELD_TYPE (scalar_t__) ; 
 scalar_t__ DECL_SIZE_UNIT (scalar_t__) ; 
#define  INDIRECT_REF 129 
 int /*<<< orphan*/  INDIRECT_REF_P (scalar_t__) ; 
 int const INTEGER_CST ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int const PARM_DECL ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int const RESULT_DECL ; 
 int const STRING_CST ; 
#define  TARGET_MEM_REF 128 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TRUNC_DIV_EXPR ; 
 int /*<<< orphan*/  TRUNC_MOD_EXPR ; 
 scalar_t__ TYPE_SIZE_UNIT (scalar_t__) ; 
 int const VAR_DECL ; 
 scalar_t__ bitsize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitsizetype ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ byte_position (scalar_t__) ; 
 scalar_t__ convert (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ flag_mudflap_ignore_reads ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ integer_one_node ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  mf_build_check_statement_for (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mf_decl_eligible_p (scalar_t__) ; 
 scalar_t__ mf_marked_p (scalar_t__) ; 
 int /*<<< orphan*/  mf_uintptr_type ; 
 int /*<<< orphan*/  ptr_type_node ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sizetype ; 
 scalar_t__ tree_mem_ref_addr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mf_xform_derefs_1 (block_stmt_iterator *iter, tree *tp,
                   location_t *locus, tree dirflag)
{
  tree type, base, limit, addr, size, t;

  /* Don't instrument read operations.  */
  if (dirflag == integer_zero_node && flag_mudflap_ignore_reads)
    return;

  /* Don't instrument marked nodes.  */
  if (mf_marked_p (*tp))
    return;

  t = *tp;
  type = TREE_TYPE (t);

  if (type == error_mark_node)
    return;

  size = TYPE_SIZE_UNIT (type);

  switch (TREE_CODE (t))
    {
    case ARRAY_REF:
    case COMPONENT_REF:
      {
        /* This is trickier than it may first appear.  The reason is
           that we are looking at expressions from the "inside out" at
           this point.  We may have a complex nested aggregate/array
           expression (e.g. "a.b[i].c"), maybe with an indirection as
           the leftmost operator ("p->a.b.d"), where instrumentation
           is necessary.  Or we may have an innocent "a.b.c"
           expression that must not be instrumented.  We need to
           recurse all the way down the nesting structure to figure it
           out: looking just at the outer node is not enough.  */          
        tree var;
        int component_ref_only = (TREE_CODE (t) == COMPONENT_REF);
	/* If we have a bitfield component reference, we must note the
	   innermost addressable object in ELT, from which we will
	   construct the byte-addressable bounds of the bitfield.  */
	tree elt = NULL_TREE;
	int bitfield_ref_p = (TREE_CODE (t) == COMPONENT_REF
			      && DECL_BIT_FIELD_TYPE (TREE_OPERAND (t, 1)));

        /* Iterate to the top of the ARRAY_REF/COMPONENT_REF
           containment hierarchy to find the outermost VAR_DECL.  */
        var = TREE_OPERAND (t, 0);
        while (1)
          {
	    if (bitfield_ref_p && elt == NULL_TREE
		&& (TREE_CODE (var) == ARRAY_REF || TREE_CODE (var) == COMPONENT_REF))
	      elt = var;
	
            if (TREE_CODE (var) == ARRAY_REF)
              {
                component_ref_only = 0;
                var = TREE_OPERAND (var, 0);
              }
            else if (TREE_CODE (var) == COMPONENT_REF)
              var = TREE_OPERAND (var, 0);
            else if (INDIRECT_REF_P (var))
              {
		base = TREE_OPERAND (var, 0);
                break;
              }
            else 
              {
                gcc_assert (TREE_CODE (var) == VAR_DECL 
                            || TREE_CODE (var) == PARM_DECL
                            || TREE_CODE (var) == RESULT_DECL
                            || TREE_CODE (var) == STRING_CST);
                /* Don't instrument this access if the underlying
                   variable is not "eligible".  This test matches
                   those arrays that have only known-valid indexes,
                   and thus are not labeled TREE_ADDRESSABLE.  */
                if (! mf_decl_eligible_p (var) || component_ref_only)
                  return;
                else
		  {
		    base = build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (var)), var);
		    break;
		  }
              }
          }

        /* Handle the case of ordinary non-indirection structure
           accesses.  These have only nested COMPONENT_REF nodes (no
           INDIRECT_REF), but pass through the above filter loop.
           Note that it's possible for such a struct variable to match
           the eligible_p test because someone else might take its
           address sometime.  */

        /* We need special processing for bitfield components, because
           their addresses cannot be taken.  */
        if (bitfield_ref_p)
          {
            tree field = TREE_OPERAND (t, 1);

            if (TREE_CODE (DECL_SIZE_UNIT (field)) == INTEGER_CST)
              size = DECL_SIZE_UNIT (field);
            
	    if (elt)
	      elt = build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (elt)), elt);
            addr = fold_convert (ptr_type_node, elt ? elt : base);
            addr = fold_build2 (PLUS_EXPR, ptr_type_node,
				addr, fold_convert (ptr_type_node,
						    byte_position (field)));
          }
        else
          addr = build1 (ADDR_EXPR, build_pointer_type (type), t);

        limit = fold_build2 (MINUS_EXPR, mf_uintptr_type,
                             fold_build2 (PLUS_EXPR, mf_uintptr_type,
					  convert (mf_uintptr_type, addr),
					  size),
                             integer_one_node);
      }
      break;

    case INDIRECT_REF:
      addr = TREE_OPERAND (t, 0);
      base = addr;
      limit = fold_build2 (MINUS_EXPR, ptr_type_node,
                           fold_build2 (PLUS_EXPR, ptr_type_node, base, size),
                           integer_one_node);
      break;

    case TARGET_MEM_REF:
      addr = tree_mem_ref_addr (ptr_type_node, t);
      base = addr;
      limit = fold_build2 (MINUS_EXPR, ptr_type_node,
			   fold_build2 (PLUS_EXPR, ptr_type_node, base, size),
			   build_int_cst (ptr_type_node, 1));
      break;

    case ARRAY_RANGE_REF:
      warning (0, "mudflap checking not yet implemented for ARRAY_RANGE_REF");
      return;

    case BIT_FIELD_REF:
      /* ??? merge with COMPONENT_REF code above? */
      {
        tree ofs, rem, bpu;

        /* If we're not dereferencing something, then the access
           must be ok.  */
        if (TREE_CODE (TREE_OPERAND (t, 0)) != INDIRECT_REF)
          return;

        bpu = bitsize_int (BITS_PER_UNIT);
        ofs = convert (bitsizetype, TREE_OPERAND (t, 2));
        rem = size_binop (TRUNC_MOD_EXPR, ofs, bpu);
        ofs = size_binop (TRUNC_DIV_EXPR, ofs, bpu);

        size = convert (bitsizetype, TREE_OPERAND (t, 1));
        size = size_binop (PLUS_EXPR, size, rem);
        size = size_binop (CEIL_DIV_EXPR, size, bpu);
        size = convert (sizetype, size);

        addr = TREE_OPERAND (TREE_OPERAND (t, 0), 0);
        addr = convert (ptr_type_node, addr);
        addr = fold_build2 (PLUS_EXPR, ptr_type_node, addr, ofs);

        base = addr;
        limit = fold_build2 (MINUS_EXPR, ptr_type_node,
                             fold_build2 (PLUS_EXPR, ptr_type_node, base, size),
                             integer_one_node);
      }
      break;

    default:
      return;
    }

  mf_build_check_statement_for (base, limit, iter, locus, dirflag);
}