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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ui_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* ubifs_inode (struct inode*) ; 

__attribute__((used)) static void unlock_3_inodes(struct inode *inode1, struct inode *inode2,
			    struct inode *inode3)
{
	if (inode3)
		mutex_unlock(&ubifs_inode(inode3)->ui_mutex);
	if (inode1 != inode2)
		mutex_unlock(&ubifs_inode(inode2)->ui_mutex);
	mutex_unlock(&ubifs_inode(inode1)->ui_mutex);
}