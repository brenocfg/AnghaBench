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
typedef  int /*<<< orphan*/  u64 ;
struct hppfs_dirent {int (* filldir ) (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  vfs_dirent; int /*<<< orphan*/  dentry; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ file_removed (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int hppfs_filldir(void *d, const char *name, int size,
			 loff_t offset, u64 inode, unsigned int type)
{
	struct hppfs_dirent *dirent = d;

	if (file_removed(dirent->dentry, name))
		return 0;

	return (*dirent->filldir)(dirent->vfs_dirent, name, size, offset,
				  inode, type);
}