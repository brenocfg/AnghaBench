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
struct sysfs_dirent {scalar_t__ s_ino; } ;
struct inode {scalar_t__ i_ino; } ;

/* Variables and functions */

__attribute__((used)) static int sysfs_ilookup_test(struct inode *inode, void *arg)
{
	struct sysfs_dirent *sd = arg;
	return inode->i_ino == sd->s_ino;
}