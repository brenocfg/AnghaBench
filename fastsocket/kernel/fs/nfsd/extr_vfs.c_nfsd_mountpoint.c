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
struct svc_export {int ex_flags; } ;
struct dentry {int /*<<< orphan*/ * d_inode; } ;

/* Variables and functions */
 int NFSEXP_V4ROOT ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 

int nfsd_mountpoint(struct dentry *dentry, struct svc_export *exp)
{
	if (d_mountpoint(dentry))
		return 1;
	if (!(exp->ex_flags & NFSEXP_V4ROOT))
		return 0;
	return dentry->d_inode != NULL;
}