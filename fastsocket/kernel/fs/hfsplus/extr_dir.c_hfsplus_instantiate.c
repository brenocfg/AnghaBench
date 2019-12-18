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
typedef  scalar_t__ u32 ;
struct inode {int dummy; } ;
struct dentry {void* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 

__attribute__((used)) static inline void hfsplus_instantiate(struct dentry *dentry,
				       struct inode *inode, u32 cnid)
{
	dentry->d_fsdata = (void *)(unsigned long)cnid;
	d_instantiate(dentry, inode);
}