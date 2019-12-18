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
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {char* name; int len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct coda_vattr {int dummy; } ;
struct CodaFid {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  coda_dir_update_mtime (struct inode*) ; 
 int /*<<< orphan*/  coda_i2f (struct inode*) ; 
 struct inode* coda_iget (int /*<<< orphan*/ ,struct CodaFid*,struct coda_vattr*) ; 
 scalar_t__ coda_iscontrol (char const*,int) ; 
 scalar_t__ coda_isroot (struct inode*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int venus_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int,struct CodaFid*,struct coda_vattr*) ; 

__attribute__((used)) static int coda_create(struct inode *dir, struct dentry *de, int mode, struct nameidata *nd)
{
        int error=0;
	const char *name=de->d_name.name;
	int length=de->d_name.len;
	struct inode *inode;
	struct CodaFid newfid;
	struct coda_vattr attrs;

	lock_kernel();

	if (coda_isroot(dir) && coda_iscontrol(name, length)) {
		unlock_kernel();
		return -EPERM;
	}

	error = venus_create(dir->i_sb, coda_i2f(dir), name, length, 
				0, mode, &newfid, &attrs);

        if ( error ) {
		unlock_kernel();
		d_drop(de);
		return error;
	}

	inode = coda_iget(dir->i_sb, &newfid, &attrs);
	if ( IS_ERR(inode) ) {
		unlock_kernel();
		d_drop(de);
		return PTR_ERR(inode);
	}

	/* invalidate the directory cnode's attributes */
	coda_dir_update_mtime(dir);
	unlock_kernel();
	d_instantiate(de, inode);
	return 0;
}