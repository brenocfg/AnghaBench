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
struct tree_balance {TYPE_1__* transaction_handle; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  t_super; } ;

/* Variables and functions */
 int /*<<< orphan*/  journal_mark_dirty (TYPE_1__*,int /*<<< orphan*/ ,struct buffer_head*) ; 

inline void do_balance_mark_leaf_dirty(struct tree_balance *tb,
				       struct buffer_head *bh, int flag)
{
	journal_mark_dirty(tb->transaction_handle,
			   tb->transaction_handle->t_super, bh);
}