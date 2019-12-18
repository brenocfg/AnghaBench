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
 struct block_sema_info* cur_block ; 
 int /*<<< orphan*/  pop_scope () ; 

struct block_sema_info *
finish_block (tree block __attribute__ ((__unused__)))
{
  struct block_sema_info *csi = cur_block;
  cur_block = cur_block->prev_block_info;
#if 0
  pop_scope ();
#endif
  return csi;
}