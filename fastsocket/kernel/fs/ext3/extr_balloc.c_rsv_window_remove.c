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
struct super_block {int dummy; } ;
struct ext3_reserve_window_node {int /*<<< orphan*/  rsv_node; scalar_t__ rsv_alloc_hit; void* rsv_end; void* rsv_start; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_rsv_window_root; } ;

/* Variables and functions */
 void* EXT3_RESERVE_WINDOW_NOT_ALLOCATED ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rsv_window_remove(struct super_block *sb,
			      struct ext3_reserve_window_node *rsv)
{
	rsv->rsv_start = EXT3_RESERVE_WINDOW_NOT_ALLOCATED;
	rsv->rsv_end = EXT3_RESERVE_WINDOW_NOT_ALLOCATED;
	rsv->rsv_alloc_hit = 0;
	rb_erase(&rsv->rsv_node, &EXT3_SB(sb)->s_rsv_window_root);
}