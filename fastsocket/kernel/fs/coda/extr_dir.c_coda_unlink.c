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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {char* name; int len; } ;
struct dentry {int /*<<< orphan*/  d_inode; TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  coda_dir_update_mtime (struct inode*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int venus_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int coda_unlink(struct inode *dir, struct dentry *de)
{
        int error;
	const char *name = de->d_name.name;
	int len = de->d_name.len;

	lock_kernel();

	error = venus_remove(dir->i_sb, coda_i2f(dir), name, len);
	if ( error ) {
		unlock_kernel();
		return error;
	}

	coda_dir_update_mtime(dir);
	drop_nlink(de->d_inode);
	unlock_kernel();
	return 0;
}