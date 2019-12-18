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
struct inode {int i_flags; int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  REISERFS_IMMUTABLE_FL ; 
 int /*<<< orphan*/  REISERFS_NOATIME_FL ; 
 int /*<<< orphan*/  REISERFS_NOTAIL_FL ; 
 int /*<<< orphan*/  REISERFS_SYNC_FL ; 
 int S_IMMUTABLE ; 
 int S_NOATIME ; 
 int S_SYNC ; 
 int i_nopack_mask ; 
 scalar_t__ reiserfs_attrs (int /*<<< orphan*/ ) ; 

void i_attrs_to_sd_attrs(struct inode *inode, __u16 * sd_attrs)
{
	if (reiserfs_attrs(inode->i_sb)) {
		if (inode->i_flags & S_IMMUTABLE)
			*sd_attrs |= REISERFS_IMMUTABLE_FL;
		else
			*sd_attrs &= ~REISERFS_IMMUTABLE_FL;
		if (inode->i_flags & S_SYNC)
			*sd_attrs |= REISERFS_SYNC_FL;
		else
			*sd_attrs &= ~REISERFS_SYNC_FL;
		if (inode->i_flags & S_NOATIME)
			*sd_attrs |= REISERFS_NOATIME_FL;
		else
			*sd_attrs &= ~REISERFS_NOATIME_FL;
		if (REISERFS_I(inode)->i_flags & i_nopack_mask)
			*sd_attrs |= REISERFS_NOTAIL_FL;
		else
			*sd_attrs &= ~REISERFS_NOTAIL_FL;
	}
}