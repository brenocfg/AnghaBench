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
struct tree_balance {int dummy; } ;
struct buffer_info {scalar_t__ bi_position; int /*<<< orphan*/ * bi_parent; struct buffer_head* bi_bh; struct tree_balance* tb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void buffer_info_init_bh(struct tree_balance *tb,
                                       struct buffer_info *bi,
                                       struct buffer_head *bh)
{
	bi->tb          = tb;
	bi->bi_bh       = bh;
	bi->bi_parent   = NULL;
	bi->bi_position = 0;
}