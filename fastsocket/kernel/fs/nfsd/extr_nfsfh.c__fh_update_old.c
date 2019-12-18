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
struct svc_export {int ex_flags; } ;
struct knfsd_fh {scalar_t__ ofh_dirino; int /*<<< orphan*/  ofh_generation; int /*<<< orphan*/  ofh_ino; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int NFSEXP_NOSUBTREECHECK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_t_to_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void _fh_update_old(struct dentry *dentry,
				  struct svc_export *exp,
				  struct knfsd_fh *fh)
{
	fh->ofh_ino = ino_t_to_u32(dentry->d_inode->i_ino);
	fh->ofh_generation = dentry->d_inode->i_generation;
	if (S_ISDIR(dentry->d_inode->i_mode) ||
	    (exp->ex_flags & NFSEXP_NOSUBTREECHECK))
		fh->ofh_dirino = 0;
}