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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct extent_state {int state; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  outstanding_extents; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int EXTENT_DELALLOC ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_split_extent_hook(struct inode *inode,
				    struct extent_state *orig, u64 split)
{
	/* not delalloc, ignore it */
	if (!(orig->state & EXTENT_DELALLOC))
		return;

	spin_lock(&BTRFS_I(inode)->lock);
	BTRFS_I(inode)->outstanding_extents++;
	spin_unlock(&BTRFS_I(inode)->lock);
}