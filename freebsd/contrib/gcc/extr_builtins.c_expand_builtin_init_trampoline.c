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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BLKmode ; 
 int /*<<< orphan*/  BLOCK_OP_NORMAL ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIALIZE_TRAMPOLINE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  TRAMPOLINE_ALIGNMENT ; 
 int /*<<< orphan*/  TRAMPOLINE_SIZE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  assemble_trampoline_template () ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_block_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_trampoline_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_align (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trampolines_created ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_init_trampoline (tree arglist)
{
  tree t_tramp, t_func, t_chain;
  rtx r_tramp, r_func, r_chain;
#ifdef TRAMPOLINE_TEMPLATE
  rtx blktramp;
#endif

  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE,
			 POINTER_TYPE, VOID_TYPE))
    return NULL_RTX;

  t_tramp = TREE_VALUE (arglist);
  arglist = TREE_CHAIN (arglist);
  t_func = TREE_VALUE (arglist);
  arglist = TREE_CHAIN (arglist);
  t_chain = TREE_VALUE (arglist);

  r_tramp = expand_normal (t_tramp);
  r_func = expand_normal (t_func);
  r_chain = expand_normal (t_chain);

  /* Generate insns to initialize the trampoline.  */
  r_tramp = round_trampoline_addr (r_tramp);
#ifdef TRAMPOLINE_TEMPLATE
  blktramp = gen_rtx_MEM (BLKmode, r_tramp);
  set_mem_align (blktramp, TRAMPOLINE_ALIGNMENT);
  emit_block_move (blktramp, assemble_trampoline_template (),
		   GEN_INT (TRAMPOLINE_SIZE), BLOCK_OP_NORMAL);
#endif
  trampolines_created = 1;
  INITIALIZE_TRAMPOLINE (r_tramp, r_func, r_chain);

  return const0_rtx;
}