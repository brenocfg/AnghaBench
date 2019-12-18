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
typedef  int /*<<< orphan*/  rtx ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ BITS_PER_UNIT ; 
 int /*<<< orphan*/  BLKmode ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ CONVERT_EXPR ; 
 int /*<<< orphan*/  DECL_BIT_FIELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DECL_FIELD_BIT_OFFSET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DECL_FIELD_OFFSET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 int /*<<< orphan*/ * MEM_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_OFFSET (int /*<<< orphan*/ ) ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ NOP_EXPR ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ SAVE_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_SIZE_UNIT (int /*<<< orphan*/ *) ; 
 scalar_t__ VIEW_CONVERT_EXPR ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expand_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_mode ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mem_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_low_cst (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static rtx
get_memory_rtx (tree exp, tree len)
{
  rtx addr = expand_expr (exp, NULL_RTX, ptr_mode, EXPAND_NORMAL);
  rtx mem = gen_rtx_MEM (BLKmode, memory_address (BLKmode, addr));

  /* Get an expression we can use to find the attributes to assign to MEM.
     If it is an ADDR_EXPR, use the operand.  Otherwise, dereference it if
     we can.  First remove any nops.  */
  while ((TREE_CODE (exp) == NOP_EXPR || TREE_CODE (exp) == CONVERT_EXPR
	  || TREE_CODE (exp) == NON_LVALUE_EXPR)
	 && POINTER_TYPE_P (TREE_TYPE (TREE_OPERAND (exp, 0))))
    exp = TREE_OPERAND (exp, 0);

  if (TREE_CODE (exp) == ADDR_EXPR)
    exp = TREE_OPERAND (exp, 0);
  else if (POINTER_TYPE_P (TREE_TYPE (exp)))
    exp = build1 (INDIRECT_REF, TREE_TYPE (TREE_TYPE (exp)), exp);
  else
    exp = NULL;

  /* Honor attributes derived from exp, except for the alias set
     (as builtin stringops may alias with anything) and the size
     (as stringops may access multiple array elements).  */
  if (exp)
    {
      set_mem_attributes (mem, exp, 0);

      /* Allow the string and memory builtins to overflow from one
	 field into another, see http://gcc.gnu.org/PR23561.
	 Thus avoid COMPONENT_REFs in MEM_EXPR unless we know the whole
	 memory accessed by the string or memory builtin will fit
	 within the field.  */
      if (MEM_EXPR (mem) && TREE_CODE (MEM_EXPR (mem)) == COMPONENT_REF)
	{
	  tree mem_expr = MEM_EXPR (mem);
	  HOST_WIDE_INT offset = -1, length = -1;
	  tree inner = exp;

	  while (TREE_CODE (inner) == ARRAY_REF
		 || TREE_CODE (inner) == NOP_EXPR
		 || TREE_CODE (inner) == CONVERT_EXPR
		 || TREE_CODE (inner) == NON_LVALUE_EXPR
		 || TREE_CODE (inner) == VIEW_CONVERT_EXPR
		 || TREE_CODE (inner) == SAVE_EXPR)
	    inner = TREE_OPERAND (inner, 0);

	  gcc_assert (TREE_CODE (inner) == COMPONENT_REF);

	  if (MEM_OFFSET (mem)
	      && GET_CODE (MEM_OFFSET (mem)) == CONST_INT)
	    offset = INTVAL (MEM_OFFSET (mem));

	  if (offset >= 0 && len && host_integerp (len, 0))
	    length = tree_low_cst (len, 0);

	  while (TREE_CODE (inner) == COMPONENT_REF)
	    {
	      tree field = TREE_OPERAND (inner, 1);
	      gcc_assert (! DECL_BIT_FIELD (field));
	      gcc_assert (TREE_CODE (mem_expr) == COMPONENT_REF);
	      gcc_assert (field == TREE_OPERAND (mem_expr, 1));

	      if (length >= 0
		  && TYPE_SIZE_UNIT (TREE_TYPE (inner))
		  && host_integerp (TYPE_SIZE_UNIT (TREE_TYPE (inner)), 0))
		{
		  HOST_WIDE_INT size
		    = tree_low_cst (TYPE_SIZE_UNIT (TREE_TYPE (inner)), 0);
		  /* If we can prove the memory starting at XEXP (mem, 0)
		     and ending at XEXP (mem, 0) + LENGTH will fit into
		     this field, we can keep that COMPONENT_REF in MEM_EXPR.  */
		  if (offset <= size
		      && length <= size
		      && offset + length <= size)
		    break;
		}

	      if (offset >= 0
		  && host_integerp (DECL_FIELD_OFFSET (field), 0))
		offset += tree_low_cst (DECL_FIELD_OFFSET (field), 0)
			  + tree_low_cst (DECL_FIELD_BIT_OFFSET (field), 1)
			    / BITS_PER_UNIT;
	      else
		{
		  offset = -1;
		  length = -1;
		}

	      mem_expr = TREE_OPERAND (mem_expr, 0);
	      inner = TREE_OPERAND (inner, 0);
	    }

	  if (mem_expr == NULL)
	    offset = -1;
	  if (mem_expr != MEM_EXPR (mem))
	    {
	      set_mem_expr (mem, mem_expr);
	      set_mem_offset (mem, offset >= 0 ? GEN_INT (offset) : NULL_RTX);
	    }
	}
      set_mem_alias_set (mem, 0);
      set_mem_size (mem, NULL_RTX);
    }

  return mem;
}