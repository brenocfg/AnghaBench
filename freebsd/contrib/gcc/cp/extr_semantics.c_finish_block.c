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
struct block_sema_info {struct block_sema_info* prev_block_info; } ;

/* Variables and functions */
 struct block_sema_info* cur_block ; 
 int /*<<< orphan*/  do_poplevel (scalar_t__) ; 

struct block_sema_info *
finish_block (tree block)
{
  struct block_sema_info *csi = cur_block;
  cur_block = cur_block->prev_block_info;
  /* pop_scope (); */
#if 0
  if (block)
    do_poplevel (block);
#else
  block = 0;
#endif
  return csi;
}