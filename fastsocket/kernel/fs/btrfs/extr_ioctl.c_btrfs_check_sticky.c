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
typedef  scalar_t__ uid_t ;
struct inode {int i_mode; scalar_t__ i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FOWNER ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 

__attribute__((used)) static inline int btrfs_check_sticky(struct inode *dir, struct inode *inode)
{
	uid_t fsuid = current_fsuid();

	if (!(dir->i_mode & S_ISVTX))
		return 0;
	if (inode->i_uid == fsuid)
		return 0;
	if (dir->i_uid == fsuid)
		return 0;
	return !capable(CAP_FOWNER);
}