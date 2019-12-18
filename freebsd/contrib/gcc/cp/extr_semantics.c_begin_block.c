#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct block_sema_info {struct block_sema_info* prev_block_info; } ;
struct TYPE_2__ {int stmts_are_full_exprs_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 struct block_sema_info* cur_block ; 
 TYPE_1__* current_stmt_tree () ; 
 int /*<<< orphan*/  do_pushlevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_block ; 
 scalar_t__ xcalloc (int,int) ; 

tree
begin_block (void)
{
  struct block_sema_info *csi;
  tree block;
  /* push_scope (); */
  current_stmt_tree ()->stmts_are_full_exprs_p = 1;
#if 0
  block = do_pushlevel (sk_block);
#else
  block = NULL_TREE;
#endif
  csi = (struct block_sema_info*)xcalloc (1, sizeof (struct block_sema_info));
  csi->prev_block_info = cur_block;
  cur_block = csi;
  return block;
}