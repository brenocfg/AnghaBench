#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_8__ {char* mnt_dir; char* mnt_fsname; char* mnt_opts; int /*<<< orphan*/  mnt_type; } ;
typedef  TYPE_1__ mntent_t ;
typedef  int /*<<< orphan*/  mnt ;
struct TYPE_9__ {int flags; int iso_flags; char* fspec; scalar_t__ ssector; scalar_t__ norrip; int /*<<< orphan*/  iso_pgthresh; } ;
typedef  TYPE_2__ cdfs_args_t ;
typedef  int /*<<< orphan*/  cdfs_args ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  MTYPE_TYPE ;

/* Variables and functions */
 int MNT2_CDFS_OPT_DEFPERM ; 
 int MNT2_CDFS_OPT_EXTATT ; 
 int MNT2_CDFS_OPT_GENS ; 
 int MNT2_CDFS_OPT_NOCASETRANS ; 
 int MNT2_CDFS_OPT_NODEFPERM ; 
 int MNT2_CDFS_OPT_NOJOLIET ; 
 int MNT2_CDFS_OPT_NORRIP ; 
 int MNT2_CDFS_OPT_NOVERSION ; 
 int MNT2_CDFS_OPT_RRCASEINS ; 
 int MNT2_CDFS_OPT_RRIP ; 
 int /*<<< orphan*/  MNTTAB_OPT_DEFPERM ; 
 int /*<<< orphan*/  MNTTAB_OPT_EXTATT ; 
 int /*<<< orphan*/  MNTTAB_OPT_GENS ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOCASETRANS ; 
 int /*<<< orphan*/  MNTTAB_OPT_NODEFPERM ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOJOLIET ; 
 int /*<<< orphan*/  MNTTAB_OPT_NORRIP ; 
 int /*<<< orphan*/  MNTTAB_OPT_NOVERSION ; 
 int /*<<< orphan*/  MNTTAB_OPT_PGTHRESH ; 
 int /*<<< orphan*/  MNTTAB_OPT_RRCASEINS ; 
 int /*<<< orphan*/  MNTTAB_OPT_RRIP ; 
 int /*<<< orphan*/  MNTTAB_TYPE_CDFS ; 
 int /*<<< orphan*/  MOUNT_TYPE_CDFS ; 
 scalar_t__ amu_hasmntopt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int autofs_compute_mount_flags (TYPE_1__*) ; 
 int compute_mount_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  hasmntval (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 int mount_fs (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mount_cdfs(char *mntdir, char *fs_name, char *opts, int on_autofs)
{
  cdfs_args_t cdfs_args;
  mntent_t mnt;
  int genflags, cdfs_flags, retval;

  /*
   * Figure out the name of the file system type.
   */
  MTYPE_TYPE type = MOUNT_TYPE_CDFS;

  memset((voidp) &cdfs_args, 0, sizeof(cdfs_args)); /* Paranoid */
  cdfs_flags = 0;

  /*
   * Fill in the mount structure
   */
  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = mntdir;
  mnt.mnt_fsname = fs_name;
  mnt.mnt_type = MNTTAB_TYPE_CDFS;
  mnt.mnt_opts = opts;

#if defined(MNT2_CDFS_OPT_DEFPERM) && defined(MNTTAB_OPT_DEFPERM)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_DEFPERM))
# ifdef MNT2_CDFS_OPT_DEFPERM
    cdfs_flags |= MNT2_CDFS_OPT_DEFPERM;
# else /* not MNT2_CDFS_OPT_DEFPERM */
    cdfs_flags &= ~MNT2_CDFS_OPT_NODEFPERM;
# endif /* not MNT2_CDFS_OPT_DEFPERM */
#endif /* defined(MNT2_CDFS_OPT_DEFPERM) && defined(MNTTAB_OPT_DEFPERM) */

#if defined(MNT2_CDFS_OPT_NODEFPERM) && defined(MNTTAB_OPT_NODEFPERM)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_NODEFPERM))
    cdfs_flags |= MNT2_CDFS_OPT_NODEFPERM;
#endif /* MNTTAB_OPT_NODEFPERM */

#if defined(MNT2_CDFS_OPT_NOVERSION) && defined(MNTTAB_OPT_NOVERSION)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_NOVERSION))
    cdfs_flags |= MNT2_CDFS_OPT_NOVERSION;
#endif /* defined(MNT2_CDFS_OPT_NOVERSION) && defined(MNTTAB_OPT_NOVERSION) */

#if defined(MNT2_CDFS_OPT_RRIP) && defined(MNTTAB_OPT_RRIP)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_RRIP))
    cdfs_flags |= MNT2_CDFS_OPT_RRIP;
#endif /* defined(MNT2_CDFS_OPT_RRIP) && defined(MNTTAB_OPT_RRIP) */

#if defined(MNT2_CDFS_OPT_NORRIP) && defined(MNTTAB_OPT_NORRIP)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_NORRIP))
    cdfs_flags |= MNT2_CDFS_OPT_NORRIP;
#endif /* defined(MNT2_CDFS_OPT_NORRIP) && defined(MNTTAB_OPT_NORRIP) */

#if defined(MNT2_CDFS_OPT_GENS) && defined(MNTTAB_OPT_GENS)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_GENS))
    cdfs_flags |= MNT2_CDFS_OPT_GENS;
#endif /* defined(MNT2_CDFS_OPT_GENS) && defined(MNTTAB_OPT_GENS) */

#if defined(MNT2_CDFS_OPT_EXTATT) && defined(MNTTAB_OPT_EXTATT)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_EXTATT))
    cdfs_flags |= MNT2_CDFS_OPT_EXTATT;
#endif /* defined(MNT2_CDFS_OPT_EXTATT) && defined(MNTTAB_OPT_EXTATT) */

#if defined(MNT2_CDFS_OPT_NOCASETRANS) && defined(MNTTAB_OPT_NOCASETRANS)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_NOCASETRANS))
    cdfs_flags |= MNT2_CDFS_OPT_NOCASETRANS;
#endif /* defined(MNT2_CDFS_OPT_NOCASETRANS) && defined(MNTTAB_OPT_NOCASETRANS) */

#if defined(MNT2_CDFS_OPT_NOJOLIET) && defined(MNTTAB_OPT_NOJOLIET)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_NOJOLIET))
    cdfs_flags |= MNT2_CDFS_OPT_NOJOLIET;
#endif /* defined(MNT2_CDFS_OPT_NOJOLIET) && defined(MNTTAB_OPT_NOJOLIET) */

#if defined(MNT2_CDFS_OPT_RRCASEINS) && defined(MNTTAB_OPT_RRCASEINS)
  if (amu_hasmntopt(&mnt, MNTTAB_OPT_RRCASEINS))
    cdfs_flags |= MNT2_CDFS_OPT_RRCASEINS;
#endif /* defined(MNT2_CDFS_OPT_RRCASEINS) && defined(MNTTAB_OPT_RRCASEINS) */

  genflags = compute_mount_flags(&mnt);
#ifdef HAVE_FS_AUTOFS
  if (on_autofs)
    genflags |= autofs_compute_mount_flags(&mnt);
#endif /* HAVE_FS_AUTOFS */

#ifdef HAVE_CDFS_ARGS_T_FLAGS
  cdfs_args.flags = cdfs_flags;
#endif /* HAVE_CDFS_ARGS_T_FLAGS */

#ifdef HAVE_CDFS_ARGS_T_ISO_FLAGS
  cdfs_args.iso_flags = genflags | cdfs_flags;
#endif /* HAVE_CDFS_ARGS_T_ISO_FLAGS */

#ifdef HAVE_CDFS_ARGS_T_ISO_PGTHRESH
  cdfs_args.iso_pgthresh = hasmntval(&mnt, MNTTAB_OPT_PGTHRESH);
#endif /* HAVE_CDFS_ARGS_T_ISO_PGTHRESH */

#ifdef HAVE_CDFS_ARGS_T_NORRIP
  /* XXX: need to provide norrip mount opt */
  cdfs_args.norrip = 0;		/* use Rock-Ridge Protocol extensions */
#endif /* HAVE_CDFS_ARGS_T_NORRIP */

#ifdef HAVE_CDFS_ARGS_T_SSECTOR
  /* XXX: need to provide ssector mount option */
  cdfs_args.ssector = 0;	/* use 1st session on disk */
#endif /* HAVE_CDFS_ARGS_T_SSECTOR */

#ifdef HAVE_CDFS_ARGS_T_FSPEC
  cdfs_args.fspec = fs_name;
#endif /* HAVE_CDFS_ARGS_T_FSPEC */

  /*
   * Call generic mount routine
   */
  retval = mount_fs(&mnt, genflags, (caddr_t) &cdfs_args, 0, type, 0, NULL, mnttab_file_name, on_autofs);

  return retval;
}