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
 int /*<<< orphan*/  WB_MUTEX_1 ; 
 int /*<<< orphan*/  WB_MUTEX_2 ; 
 int /*<<< orphan*/  WB_MUTEX_3 ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ubifs_inode (struct inode*) ; 

__attribute__((used)) static void lock_3_inodes(struct inode *inode1, struct inode *inode2,
			  struct inode *inode3)
{
	mutex_lock_nested(&ubifs_inode(inode1)->ui_mutex, WB_MUTEX_1);
	if (inode2 != inode1)
		mutex_lock_nested(&ubifs_inode(inode2)->ui_mutex, WB_MUTEX_2);
	if (inode3)
		mutex_lock_nested(&ubifs_inode(inode3)->ui_mutex, WB_MUTEX_3);
}