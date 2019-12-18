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
struct TYPE_2__ {int /*<<< orphan*/ * counter; int /*<<< orphan*/  wait_unfrozen; int /*<<< orphan*/  wait; int /*<<< orphan*/ * lock_map; } ;
struct super_block {TYPE_1__ s_writers; } ;
struct file_system_type {int fs_flags; int /*<<< orphan*/ * s_writers_key; } ;

/* Variables and functions */
 int FS_HAS_NEW_FREEZE ; 
 int SB_FREEZE_LEVELS ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 int percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sb_writers_name ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int init_sb_writers(struct super_block *s, struct file_system_type *type)
{
	int err;
	int i;

	/* Out of tree modules don't use this mechanism */
	if (unlikely(!(type->fs_flags & FS_HAS_NEW_FREEZE)))
		return 0;

	for (i = 0; i < SB_FREEZE_LEVELS; i++) {
		err = percpu_counter_init(&s->s_writers.counter[i], 0);
		if (err < 0)
			goto err_out;
		lockdep_init_map(&s->s_writers.lock_map[i], sb_writers_name[i],
				 &type->s_writers_key[i], 0);
	}
	init_waitqueue_head(&s->s_writers.wait);
	init_waitqueue_head(&s->s_writers.wait_unfrozen);
	return 0;
err_out:
	while (--i >= 0)
		percpu_counter_destroy(&s->s_writers.counter[i]);
	return err;
}