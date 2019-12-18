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
typedef  int /*<<< orphan*/  rtx ;
typedef  int TREE_SIDE_EFFECTS ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  BLKmode ; 
 int /*<<< orphan*/  BLOCK_OP_NORMAL ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int TREE_CHAIN (int) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_TYPE (int) ; 
 int TREE_VALUE (int) ; 
 int /*<<< orphan*/  TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_block_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_expr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_alias_set (int) ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stabilize_va_list (int,int) ; 
 int /*<<< orphan*/  va_list_type_node ; 

__attribute__((used)) static rtx
expand_builtin_va_copy (tree arglist)
{
  tree dst, src, t;

  dst = TREE_VALUE (arglist);
  src = TREE_VALUE (TREE_CHAIN (arglist));

  dst = stabilize_va_list (dst, 1);
  src = stabilize_va_list (src, 0);

  if (TREE_CODE (va_list_type_node) != ARRAY_TYPE)
    {
      t = build2 (MODIFY_EXPR, va_list_type_node, dst, src);
      TREE_SIDE_EFFECTS (t) = 1;
      expand_expr (t, const0_rtx, VOIDmode, EXPAND_NORMAL);
    }
  else
    {
      rtx dstb, srcb, size;

      /* Evaluate to pointers.  */
      dstb = expand_expr (dst, NULL_RTX, Pmode, EXPAND_NORMAL);
      srcb = expand_expr (src, NULL_RTX, Pmode, EXPAND_NORMAL);
      size = expand_expr (TYPE_SIZE_UNIT (va_list_type_node), NULL_RTX,
			  VOIDmode, EXPAND_NORMAL);

      dstb = convert_memory_address (Pmode, dstb);
      srcb = convert_memory_address (Pmode, srcb);

      /* "Dereference" to BLKmode memories.  */
      dstb = gen_rtx_MEM (BLKmode, dstb);
      set_mem_alias_set (dstb, get_alias_set (TREE_TYPE (TREE_TYPE (dst))));
      set_mem_align (dstb, TYPE_ALIGN (va_list_type_node));
      srcb = gen_rtx_MEM (BLKmode, srcb);
      set_mem_alias_set (srcb, get_alias_set (TREE_TYPE (TREE_TYPE (src))));
      set_mem_align (srcb, TYPE_ALIGN (va_list_type_node));

      /* Copy.  */
      emit_block_move (dstb, srcb, size, BLOCK_OP_NORMAL);
    }

  return const0_rtx;
}