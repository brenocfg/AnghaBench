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
struct dentry {struct dentry* d_fsdata; } ;

/* Variables and functions */
 struct dentry* hypfs_last_dentry ; 

__attribute__((used)) static void hypfs_add_dentry(struct dentry *dentry)
{
	dentry->d_fsdata = hypfs_last_dentry;
	hypfs_last_dentry = dentry;
}