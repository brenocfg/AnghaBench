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
struct TYPE_2__ {int /*<<< orphan*/  block_byref_global_decl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 TYPE_1__* cur_block ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void add_block_global_byref_list (tree decl)
{
  cur_block->block_byref_global_decl_list = 
    tree_cons (NULL_TREE, decl, cur_block->block_byref_global_decl_list);
}