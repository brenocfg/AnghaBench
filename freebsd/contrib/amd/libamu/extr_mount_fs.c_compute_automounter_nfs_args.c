#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nfs_common_args {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; scalar_t__ symttl; } ;
typedef  TYPE_1__ nfs_args_t ;
struct TYPE_8__ {int /*<<< orphan*/  mnt_dir; } ;
typedef  TYPE_2__ mntent_t ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  MNT2_GEN_OPT_AUTOMNTFS ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_AUTO ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_DUMBTIMR ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_IGNORE ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_RESVPORT ; 
 int /*<<< orphan*/  MNT2_NFS_OPT_SYMTTL ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  compute_nfs_attrcache_flags (struct nfs_common_args*,TYPE_2__*) ; 
 int /*<<< orphan*/  get_nfs_common_args (TYPE_1__*,struct nfs_common_args) ; 
 int /*<<< orphan*/  memset (struct nfs_common_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 

void
compute_automounter_nfs_args(nfs_args_t *nap, mntent_t *mntp)
{
  struct nfs_common_args a;

#ifdef MNT2_NFS_OPT_SYMTTL
  /*
   * Don't let the kernel cache symbolic links we generate, or else lookups
   * will bypass amd and fail to remount stuff as needed.
   */
  plog(XLOG_INFO, "turning on NFS option symttl and setting value to 0");
  nap->flags |= MNT2_NFS_OPT_SYMTTL;
  nap->symttl = 0;
#endif /* MNT2_NFS_OPT_SYMTTL */

  /*
   * This completes the flags for the HIDE_MOUNT_TYPE  code in the
   * mount_amfs_toplvl() function in amd/amfs_toplvl.c.
   * Some systems don't have a mount type, but a mount flag.
   */
#ifdef MNT2_NFS_OPT_AUTO
  nap->flags |= MNT2_NFS_OPT_AUTO;
#endif /* MNT2_NFS_OPT_AUTO */
#ifdef MNT2_NFS_OPT_IGNORE
  nap->flags |= MNT2_NFS_OPT_IGNORE;
#endif /* MNT2_NFS_OPT_IGNORE */
#ifdef MNT2_GEN_OPT_AUTOMNTFS
  nap->flags |= MNT2_GEN_OPT_AUTOMNTFS;
#endif /* not MNT2_GEN_OPT_AUTOMNTFS */

#ifdef MNT2_NFS_OPT_DUMBTIMR
  /*
   * Don't let the kernel start computing throughput of Amd.  The numbers
   * will be meaningless because of the way Amd does mount retries.
   */
  plog(XLOG_INFO, "%s: disabling nfs congestion window", mntp->mnt_dir);
  nap->flags |= MNT2_NFS_OPT_DUMBTIMR;
#endif /* MNT2_NFS_OPT_DUMBTIMR */

  /* compute all of the NFS attribute-cache flags */
  memset(&a, 0, sizeof(a));
  a.flags = nap->flags;
  compute_nfs_attrcache_flags(&a, mntp);
  get_nfs_common_args(nap, a);

  /*
   * Provide a slight bit more security by requiring the kernel to use
   * reserved ports.
   */
#ifdef MNT2_NFS_OPT_RESVPORT
  nap->flags |= MNT2_NFS_OPT_RESVPORT;
#endif /* MNT2_NFS_OPT_RESVPORT */
}