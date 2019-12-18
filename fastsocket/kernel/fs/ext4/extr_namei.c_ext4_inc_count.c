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
struct inode {int i_nlink; int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_FEATURE_RO_COMPAT_DIR_NLINK ; 
 int EXT4_LINK_MAX ; 
 int /*<<< orphan*/  EXT4_SET_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 scalar_t__ is_dx (struct inode*) ; 

__attribute__((used)) static void ext4_inc_count(handle_t *handle, struct inode *inode)
{
	inc_nlink(inode);
	if (is_dx(inode) && inode->i_nlink > 1) {
		/* limit is 16-bit i_links_count */
		if (inode->i_nlink >= EXT4_LINK_MAX || inode->i_nlink == 2) {
			inode->i_nlink = 1;
			EXT4_SET_RO_COMPAT_FEATURE(inode->i_sb,
					      EXT4_FEATURE_RO_COMPAT_DIR_NLINK);
		}
	}
}