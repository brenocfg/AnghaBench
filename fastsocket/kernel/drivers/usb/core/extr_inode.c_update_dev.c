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
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  devgid ; 
 int devmode ; 
 int /*<<< orphan*/  devuid ; 

__attribute__((used)) static void update_dev(struct dentry *dev)
{
	dev->d_inode->i_uid = devuid;
	dev->d_inode->i_gid = devgid;
	dev->d_inode->i_mode = S_IFREG | devmode;
}