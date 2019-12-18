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
struct nameidata {int flags; } ;
struct dentry {scalar_t__ d_inode; } ;

/* Variables and functions */
 int LOOKUP_CONTINUE ; 
 int LOOKUP_CREATE ; 
 int LOOKUP_PARENT ; 
 int LOOKUP_RENAME_TARGET ; 
 int vfat_revalidate_shortname (struct dentry*) ; 

__attribute__((used)) static int vfat_revalidate_ci(struct dentry *dentry, struct nameidata *nd)
{
	/*
	 * This is not negative dentry. Always valid.
	 *
	 * Note, rename() to existing directory entry will have ->d_inode,
	 * and will use existing name which isn't specified name by user.
	 *
	 * We may be able to drop this positive dentry here. But dropping
	 * positive dentry isn't good idea. So it's unsupported like
	 * rename("filename", "FILENAME") for now.
	 */
	if (dentry->d_inode)
		return 1;

	/*
	 * This may be nfsd (or something), anyway, we can't see the
	 * intent of this. So, since this can be for creation, drop it.
	 */
	if (!nd)
		return 0;

	/*
	 * Drop the negative dentry, in order to make sure to use the
	 * case sensitive name which is specified by user if this is
	 * for creation.
	 */
	if (!(nd->flags & (LOOKUP_CONTINUE | LOOKUP_PARENT))) {
		if (nd->flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
			return 0;
	}

	return vfat_revalidate_shortname(dentry);
}