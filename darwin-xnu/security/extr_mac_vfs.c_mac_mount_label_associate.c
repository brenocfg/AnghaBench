#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_4__ {char* f_fstypename; char* f_mntfromname; char* f_mntonname; } ;
struct mount {int mnt_flag; TYPE_2__ mnt_vfsstat; int /*<<< orphan*/  mnt_mntlabel; TYPE_1__* mnt_vtable; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_3__ {int vfc_vfsflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mount*,int /*<<< orphan*/ ) ; 
 int MNT_MULTILABEL ; 
 int MNT_ROOTFS ; 
 int VFC_VFSNATIVEXATTR ; 
 int VFC_VFSNOMACLABEL ; 
 int /*<<< orphan*/  mount_label_associate ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

void
mac_mount_label_associate(vfs_context_t ctx, struct mount *mp)
{
	kauth_cred_t cred = vfs_context_ucred(ctx);

	/* XXX: eventually this logic may be handled by the policy? */

	/* We desire MULTILABEL for the root filesystem. */
	if ((mp->mnt_flag & MNT_ROOTFS) && 
	    (strcmp(mp->mnt_vfsstat.f_fstypename, "hfs") == 0))
		mp->mnt_flag |= MNT_MULTILABEL;

	/* MULTILABEL on DEVFS. */
	if (strcmp(mp->mnt_vfsstat.f_fstypename, "devfs") == 0)
		mp->mnt_flag |= MNT_MULTILABEL;

	/* MULTILABEL on FDESC pseudo-filesystem. */
	if (strcmp(mp->mnt_vfsstat.f_fstypename, "fdesc") == 0)
		mp->mnt_flag |= MNT_MULTILABEL;

	/* MULTILABEL on all NFS filesystems. */
	if (strcmp(mp->mnt_vfsstat.f_fstypename, "nfs") == 0)
		mp->mnt_flag |= MNT_MULTILABEL;

	/* MULTILABEL on all AFP filesystems. */
	if (strcmp(mp->mnt_vfsstat.f_fstypename, "afpfs") == 0)
		mp->mnt_flag |= MNT_MULTILABEL;

	if (mp->mnt_vtable != NULL) {
		/* Any filesystem that supports native XATTRs. */
		if ((mp->mnt_vtable->vfc_vfsflags & VFC_VFSNATIVEXATTR))
			mp->mnt_flag |= MNT_MULTILABEL;

		/* Filesystem does not support multilabel. */
		if ((mp->mnt_vtable->vfc_vfsflags & VFC_VFSNOMACLABEL) &&
		    (mp->mnt_flag & MNT_MULTILABEL))
			mp->mnt_flag &= ~MNT_MULTILABEL;
	}

	MAC_PERFORM(mount_label_associate, cred, mp, mp->mnt_mntlabel);
#if DEBUG
	printf("MAC Framework enabling %s support: %s -> %s (%s)\n",
		mp->mnt_flag & MNT_MULTILABEL ? "multilabel" : "singlelabel", 
		mp->mnt_vfsstat.f_mntfromname,
		mp->mnt_vfsstat.f_mntonname,
		mp->mnt_vfsstat.f_fstypename);
#endif
}