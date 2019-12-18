#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchan_t ;
typedef  scalar_t__ u_short ;
struct TYPE_11__ {int mf_refc; int mf_flags; TYPE_3__* mf_server; int /*<<< orphan*/  mf_info; scalar_t__ mf_error; } ;
typedef  TYPE_2__ mntfs ;
typedef  int /*<<< orphan*/  fwd_fun ;
struct TYPE_12__ {TYPE_1__* fs_ip; } ;
typedef  TYPE_3__ fserver ;
struct TYPE_10__ {scalar_t__ sin_port; } ;
struct TYPE_13__ {char* fh_path; scalar_t__ fh_error; scalar_t__ fh_id; TYPE_3__* fh_fs; int /*<<< orphan*/  fh_nfs_version; TYPE_1__ fh_sin; } ;
typedef  TYPE_4__ fh_cache ;
typedef  int /*<<< orphan*/  am_nfs_handle_t ;

/* Variables and functions */
 int MFF_WEBNFS ; 
 int /*<<< orphan*/  MOUNTPROC_UMNT ; 
 int /*<<< orphan*/  SET_FH_VERSION (TYPE_3__*) ; 
 int /*<<< orphan*/  call_mountd (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prime_nfs_fhandle_cache (char*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
nfs_umounted(mntfs *mf)
{
  fserver *fs;
  char *colon, *path;

  if (mf->mf_error || mf->mf_refc > 1)
    return;

  /*
   * No need to inform mountd when WebNFS is in use.
   */
  if (mf->mf_flags & MFF_WEBNFS)
    return;

  /*
   * Call the mount daemon on the server to announce that we are not using
   * the fs any more.
   *
   * XXX: This is *wrong*.  The mountd should be called when the fhandle is
   * flushed from the cache, and a reference held to the cached entry while
   * the fs is mounted...
   */
  fs = mf->mf_server;
  colon = path = strchr(mf->mf_info, ':');
  if (fs && colon) {
    fh_cache f;

    dlog("calling mountd for %s", mf->mf_info);
    *path++ = '\0';
    f.fh_path = path;
    f.fh_sin = *fs->fs_ip;
    f.fh_sin.sin_port = (u_short) 0;
    f.fh_nfs_version = SET_FH_VERSION(fs);
    f.fh_fs = fs;
    f.fh_id = 0;
    f.fh_error = 0;
    prime_nfs_fhandle_cache(colon + 1, mf->mf_server, (am_nfs_handle_t *) NULL, mf);
    call_mountd(&f, MOUNTPROC_UMNT, (fwd_fun *) NULL, (wchan_t) NULL);
    *colon = ':';
  }
}