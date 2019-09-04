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
typedef  int /*<<< orphan*/  user_addr_t ;
struct vfsstatfs {int /*<<< orphan*/ * f_mntfromname; int /*<<< orphan*/ * f_mntonname; int /*<<< orphan*/ * f_fstypename; int /*<<< orphan*/  f_fssubtype; int /*<<< orphan*/  f_owner; int /*<<< orphan*/  f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; scalar_t__ f_iosize; int /*<<< orphan*/  f_bsize; } ;
struct statfs64 {int f_flags; int /*<<< orphan*/ * f_mntfromname; int /*<<< orphan*/ * f_mntonname; int /*<<< orphan*/ * f_fstypename; int /*<<< orphan*/  f_fssubtype; int /*<<< orphan*/  f_type; int /*<<< orphan*/  f_owner; int /*<<< orphan*/  f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; scalar_t__ f_iosize; int /*<<< orphan*/  f_bsize; } ;
struct mount {int mnt_flag; int mnt_kern_flag; int /*<<< orphan*/ * fstypename_override; TYPE_1__* mnt_vtable; } ;
typedef  int /*<<< orphan*/  sfs ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  vfc_typenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  MFSTYPENAMELEN ; 
 int MNTK_TYPENAME_OVERRIDE ; 
 int MNT_VISFLAGMASK ; 
 int /*<<< orphan*/  bzero (struct statfs64*,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
statfs64_common(struct mount *mp, struct vfsstatfs *sfsp, user_addr_t bufp)
{
	int error;
	struct statfs64 sfs;

	bzero(&sfs, sizeof(sfs));

	sfs.f_bsize = sfsp->f_bsize;
	sfs.f_iosize = (int32_t)sfsp->f_iosize;
	sfs.f_blocks = sfsp->f_blocks;
	sfs.f_bfree = sfsp->f_bfree;
	sfs.f_bavail = sfsp->f_bavail;
	sfs.f_files = sfsp->f_files;
	sfs.f_ffree = sfsp->f_ffree;
	sfs.f_fsid = sfsp->f_fsid;
	sfs.f_owner = sfsp->f_owner;
	sfs.f_type = mp->mnt_vtable->vfc_typenum;
	sfs.f_flags = mp->mnt_flag & MNT_VISFLAGMASK;
	sfs.f_fssubtype = sfsp->f_fssubtype;
	if (mp->mnt_kern_flag & MNTK_TYPENAME_OVERRIDE) {
		strlcpy(&sfs.f_fstypename[0], &mp->fstypename_override[0], MFSTYPENAMELEN);
	} else {
		strlcpy(&sfs.f_fstypename[0], &sfsp->f_fstypename[0], MFSTYPENAMELEN);
	}
	strlcpy(&sfs.f_mntonname[0], &sfsp->f_mntonname[0], MAXPATHLEN);
	strlcpy(&sfs.f_mntfromname[0], &sfsp->f_mntfromname[0], MAXPATHLEN);

	error = copyout((caddr_t)&sfs, bufp, sizeof(sfs));

	return(error);
}