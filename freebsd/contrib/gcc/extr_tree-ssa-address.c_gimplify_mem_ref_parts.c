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
struct mem_address {void* index; void* base; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 void* force_gimple_operand_bsi (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gimplify_mem_ref_parts (block_stmt_iterator *bsi, struct mem_address *parts)
{
  if (parts->base)
    parts->base = force_gimple_operand_bsi (bsi, parts->base,
					    true, NULL_TREE);
  if (parts->index)
    parts->index = force_gimple_operand_bsi (bsi, parts->index,
					     true, NULL_TREE);
}