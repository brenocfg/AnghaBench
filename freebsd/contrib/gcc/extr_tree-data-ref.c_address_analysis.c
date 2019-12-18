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
typedef  int /*<<< orphan*/  subvar_t ;
struct ptr_info_def {int dummy; } ;
struct data_reference {int dummy; } ;

/* Variables and functions */
#define  ADDR_EXPR 131 
 int INTEGER_CST ; 
#define  MINUS_EXPR 130 
 int /*<<< orphan*/  NULL_TREE ; 
#define  PLUS_EXPR 129 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
#define  SSA_NAME 128 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ALIGN_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  object_analysis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct data_reference**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ptr_info_def**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssize_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssizetype ; 

__attribute__((used)) static tree
address_analysis (tree expr, tree stmt, bool is_read, struct data_reference *dr, 
		  tree *offset, tree *misalign, tree *aligned_to, tree *step)
{
  tree oprnd0, oprnd1, base_address, offset_expr, base_addr0, base_addr1;
  tree address_offset = ssize_int (0), address_misalign = ssize_int (0);
  tree dummy, address_aligned_to = NULL_TREE;
  struct ptr_info_def *dummy1;
  subvar_t dummy2;

  switch (TREE_CODE (expr))
    {
    case PLUS_EXPR:
    case MINUS_EXPR:
      /* EXPR is of form {base +/- offset} (or {offset +/- base}).  */
      oprnd0 = TREE_OPERAND (expr, 0);
      oprnd1 = TREE_OPERAND (expr, 1);

      STRIP_NOPS (oprnd0);
      STRIP_NOPS (oprnd1);
      
      /* Recursively try to find the base of the address contained in EXPR.
	 For offset, the returned base will be NULL.  */
      base_addr0 = address_analysis (oprnd0, stmt, is_read, dr, &address_offset, 
				     &address_misalign, &address_aligned_to, 
				     step);

      base_addr1 = address_analysis (oprnd1, stmt, is_read,  dr, &address_offset, 
				     &address_misalign, &address_aligned_to, 
				     step);

      /* We support cases where only one of the operands contains an 
	 address.  */
      if ((base_addr0 && base_addr1) || (!base_addr0 && !base_addr1))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, 
		    "\neither more than one address or no addresses in expr ");
	      print_generic_expr (dump_file, expr, TDF_SLIM);
	      fprintf (dump_file, "\n");
	    }	
	  return NULL_TREE;
	}

      /* To revert STRIP_NOPS.  */
      oprnd0 = TREE_OPERAND (expr, 0);
      oprnd1 = TREE_OPERAND (expr, 1);
      
      offset_expr = base_addr0 ? 
	fold_convert (ssizetype, oprnd1) : fold_convert (ssizetype, oprnd0);

      /* EXPR is of form {base +/- offset} (or {offset +/- base}). If offset is 
	 a number, we can add it to the misalignment value calculated for base,
	 otherwise, misalignment is NULL.  */
      if (TREE_CODE (offset_expr) == INTEGER_CST && address_misalign)
	{
	  *misalign = size_binop (TREE_CODE (expr), address_misalign, 
				  offset_expr);
	  *aligned_to = address_aligned_to;
	}
      else
	{
	  *misalign = NULL_TREE;
	  *aligned_to = NULL_TREE;
	}

      /* Combine offset (from EXPR {base + offset}) with the offset calculated
	 for base.  */
      *offset = size_binop (TREE_CODE (expr), address_offset, offset_expr);
      return base_addr0 ? base_addr0 : base_addr1;

    case ADDR_EXPR:
      base_address = object_analysis (TREE_OPERAND (expr, 0), stmt, is_read, 
				      &dr, offset, misalign, aligned_to, step, 
				      &dummy, &dummy1, &dummy2);
      return base_address;

    case SSA_NAME:
      if (!POINTER_TYPE_P (TREE_TYPE (expr)))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "\nnot pointer SSA_NAME ");
	      print_generic_expr (dump_file, expr, TDF_SLIM);
	      fprintf (dump_file, "\n");
	    }	
	  return NULL_TREE;
	}
      *aligned_to = ssize_int (TYPE_ALIGN_UNIT (TREE_TYPE (TREE_TYPE (expr))));
      *misalign = ssize_int (0);
      *offset = ssize_int (0);
      *step = ssize_int (0);
      return expr;
      
    default:
      return NULL_TREE;
    }
}