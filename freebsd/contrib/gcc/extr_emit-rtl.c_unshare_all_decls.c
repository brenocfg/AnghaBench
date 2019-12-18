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

/* Variables and functions */
 scalar_t__ BLOCK_SUBBLOCKS (scalar_t__) ; 
 scalar_t__ BLOCK_VARS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL (scalar_t__) ; 
 scalar_t__ DECL_RTL_SET_P (scalar_t__) ; 
 int /*<<< orphan*/  SET_DECL_RTL (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  copy_rtx_if_shared (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unshare_all_decls (tree blk)
{
  tree t;

  /* Copy shared decls.  */
  for (t = BLOCK_VARS (blk); t; t = TREE_CHAIN (t))
    if (DECL_RTL_SET_P (t))
      SET_DECL_RTL (t, copy_rtx_if_shared (DECL_RTL (t)));

  /* Now process sub-blocks.  */
  for (t = BLOCK_SUBBLOCKS (blk); t; t = TREE_CHAIN (t))
    unshare_all_decls (t);
}