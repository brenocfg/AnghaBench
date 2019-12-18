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
struct kstatfs {int /*<<< orphan*/  f_type; scalar_t__ f_ffree; scalar_t__ f_files; scalar_t__ f_bavail; scalar_t__ f_bfree; scalar_t__ f_blocks; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPPFS_SUPER_MAGIC ; 

__attribute__((used)) static int hppfs_statfs(struct dentry *dentry, struct kstatfs *sf)
{
	sf->f_blocks = 0;
	sf->f_bfree = 0;
	sf->f_bavail = 0;
	sf->f_files = 0;
	sf->f_ffree = 0;
	sf->f_type = HPPFS_SUPER_MAGIC;
	return 0;
}