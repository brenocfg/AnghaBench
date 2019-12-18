#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct svc_req {int dummy; } ;
typedef  int /*<<< orphan*/  nfsstat ;
struct TYPE_18__ {int /*<<< orphan*/  da_name; int /*<<< orphan*/  da_fhandle; } ;
typedef  TYPE_5__ nfsdiropargs ;
struct TYPE_14__ {scalar_t__ na_type; } ;
struct TYPE_19__ {TYPE_4__* am_al; int /*<<< orphan*/  am_path; TYPE_1__ am_fattr; } ;
typedef  TYPE_6__ am_node ;
struct TYPE_17__ {TYPE_3__* al_mnt; } ;
struct TYPE_16__ {TYPE_2__* mf_ops; } ;
struct TYPE_15__ {TYPE_6__* (* lookup_child ) (TYPE_6__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  d_drops; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TRACE ; 
 int ENOENT ; 
 int ENOTDIR ; 
 scalar_t__ NFDIR ; 
 int /*<<< orphan*/  NFS_OK ; 
 int /*<<< orphan*/  VLOOK_DELETE ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 TYPE_12__ amd_stats ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 TYPE_6__* fh_to_mp3 (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forcibly_timeout_mp (TYPE_6__*) ; 
 int /*<<< orphan*/  nfs_error (int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* stub1 (TYPE_6__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nfsstat *
unlink_or_rmdir(nfsdiropargs *argp, struct svc_req *rqstp, int unlinkp)
{
  static nfsstat res;
  int retry;

  am_node *mp = fh_to_mp3(&argp->da_fhandle, &retry, VLOOK_DELETE);
  if (mp == NULL) {
    if (retry < 0) {
      amd_stats.d_drops++;
      return 0;
    }
    res = nfs_error(retry);
    goto out;
  }

  if (mp->am_fattr.na_type != NFDIR) {
    res = nfs_error(ENOTDIR);
    goto out;
  }

  if (amuDebug(D_TRACE))
    plog(XLOG_DEBUG, "\tremove(%s, %s)", mp->am_path, argp->da_name);

  mp = mp->am_al->al_mnt->mf_ops->lookup_child(mp, argp->da_name, &retry, VLOOK_DELETE);
  if (mp == NULL) {
    /*
     * Ignore retries...
     */
    if (retry < 0)
      retry = 0;
    /*
     * Usual NFS workaround...
     */
    else if (retry == ENOENT)
      retry = 0;
    res = nfs_error(retry);
  } else {
    forcibly_timeout_mp(mp);
    res = NFS_OK;
  }

out:
  return &res;
}