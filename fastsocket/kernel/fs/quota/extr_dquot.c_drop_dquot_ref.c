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
struct super_block {scalar_t__ dq_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqptr_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dquot_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dquot_ref (struct super_block*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  tofree_head ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_dquot_ref(struct super_block *sb, int type)
{
	LIST_HEAD(tofree_head);

	if (sb->dq_op) {
		down_write(&sb_dqopt(sb)->dqptr_sem);
		remove_dquot_ref(sb, type, &tofree_head);
		up_write(&sb_dqopt(sb)->dqptr_sem);
		put_dquot_list(&tofree_head);
	}
}