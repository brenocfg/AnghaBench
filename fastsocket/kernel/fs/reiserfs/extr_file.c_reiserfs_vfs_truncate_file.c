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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reiserfs_truncate_file (struct inode*,int) ; 

__attribute__((used)) static void reiserfs_vfs_truncate_file(struct inode *inode)
{
	reiserfs_truncate_file(inode, 1);
}