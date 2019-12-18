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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int smb_proc_write (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb_proc_trunc32(struct inode *inode, loff_t length)
{
	/*
	 * Writing 0bytes is old-SMB magic for truncating files.
	 * MAX_NON_LFS should prevent this from being called with a too
	 * large offset.
	 */
	return smb_proc_write(inode, length, 0, NULL);
}