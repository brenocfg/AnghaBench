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
struct TYPE_2__ {scalar_t__ rb_parent_color; } ;
struct netfs_trans_dst {TYPE_1__ state_entry; } ;
struct netfs_state {int /*<<< orphan*/  trans_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (TYPE_1__*,int /*<<< orphan*/ *) ; 

int netfs_trans_remove_nolock(struct netfs_trans_dst *dst, struct netfs_state *st)
{
	if (dst && dst->state_entry.rb_parent_color) {
		rb_erase(&dst->state_entry, &st->trans_root);
		dst->state_entry.rb_parent_color = 0;
		return 1;
	}
	return 0;
}