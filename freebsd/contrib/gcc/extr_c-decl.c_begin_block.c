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
struct block_sema_info {struct block_sema_info* prev_block_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 struct block_sema_info* cur_block ; 
 int /*<<< orphan*/  push_scope () ; 
 scalar_t__ xcalloc (int,int) ; 

tree
begin_block (void)
{
  struct block_sema_info *csi;
#if 0
  push_scope ();
#endif
  csi = (struct block_sema_info*)xcalloc (1, sizeof (struct block_sema_info));
  csi->prev_block_info = cur_block;
  cur_block = csi;
  return NULL_TREE;
}