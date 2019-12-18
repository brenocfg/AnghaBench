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
struct TYPE_2__ {scalar_t__ frozen; int /*<<< orphan*/  wait_unfrozen; } ;
struct super_block {scalar_t__ s_frozen; int /*<<< orphan*/  s_umount; TYPE_1__ s_writers; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_FREEZE_WRITE ; 
 scalar_t__ SB_UNFROZEN ; 
 struct super_block* get_super (struct block_device*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_super (struct super_block*) ; 
 int /*<<< orphan*/  sb_has_new_freeze (struct super_block*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_check_frozen (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

struct super_block *get_super_thawed(struct block_device *bdev)
{
	while (1) {
		struct super_block *s = get_super(bdev);

		if (!s)
			return s;

		if (likely(sb_has_new_freeze(s))) {
			if (s->s_writers.frozen == SB_UNFROZEN)
				return s;
			up_read(&s->s_umount);
			wait_event(s->s_writers.wait_unfrozen,
				   s->s_writers.frozen == SB_UNFROZEN);
		} else {
			/* Version for out of tree filesystems w/o s_writers */
			if (s->s_frozen == SB_UNFROZEN)
				return s;
			up_read(&s->s_umount);
			vfs_check_frozen(s, SB_FREEZE_WRITE);
		}
		put_super(s);
	}
}