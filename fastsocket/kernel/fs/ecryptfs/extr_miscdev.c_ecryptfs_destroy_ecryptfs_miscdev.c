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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecryptfs_miscdev ; 
 int /*<<< orphan*/  ecryptfs_num_miscdev_opens ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

void ecryptfs_destroy_ecryptfs_miscdev(void)
{
	BUG_ON(atomic_read(&ecryptfs_num_miscdev_opens) != 0);
	misc_deregister(&ecryptfs_miscdev);
}