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
struct dentry {int /*<<< orphan*/ * d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 

__attribute__((used)) static void nfs_dentry_handle_enoent(struct dentry *dentry)
{
	if (dentry->d_inode != NULL && !d_unhashed(dentry))
		d_delete(dentry);
}