#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct sockaddr_in {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * auth_flavors_val; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fhandle3_val; int /*<<< orphan*/  fhandle3_len; } ;
struct TYPE_11__ {TYPE_2__ auth_flavors; TYPE_1__ fhandle; } ;
struct TYPE_12__ {TYPE_3__ mountinfo; } ;
struct fhstatus {int /*<<< orphan*/  fhs_fh; int /*<<< orphan*/  fhs_status; TYPE_4__ mountres3_u; int /*<<< orphan*/  am_fh3_length; int /*<<< orphan*/ * am_fh3_data; } ;
struct am_mountres3 {int /*<<< orphan*/  fhs_fh; int /*<<< orphan*/  fhs_status; TYPE_4__ mountres3_u; int /*<<< orphan*/  am_fh3_length; int /*<<< orphan*/ * am_fh3_data; } ;
typedef  int /*<<< orphan*/  res3 ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  opaque_t ;
struct TYPE_13__ {int /*<<< orphan*/  v2; struct fhstatus v3; } ;
struct TYPE_15__ {scalar_t__ fh_nfs_version; scalar_t__ fh_wchan; void* fh_error; int /*<<< orphan*/  fh_path; TYPE_6__* fh_fs; TYPE_5__ fh_nfs_handle; void* fh_status; } ;
typedef  TYPE_7__ fh_cache ;
typedef  int /*<<< orphan*/  am_nfs_fh3 ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
struct TYPE_14__ {int /*<<< orphan*/  fs_host; } ;

/* Variables and functions */
 void* EACCES ; 
 int /*<<< orphan*/  NFS_FHSIZE ; 
 scalar_t__ NFS_VERSION3 ; 
 int /*<<< orphan*/  XFREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  dlog (char*,unsigned long,...) ; 
 TYPE_7__* find_nfs_fhandle_cache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fhstatus*,int /*<<< orphan*/ ,int) ; 
 void* pickup_rpc_reply (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* unx_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__) ; 
 scalar_t__ xdr_am_mountres3 ; 
 scalar_t__ xdr_fhstatus ; 

__attribute__((used)) static void
got_nfs_fh_mount(voidp pkt, int len, struct sockaddr_in *sa, struct sockaddr_in *ia, opaque_t arg, int done)
{
  fh_cache *fp;
  struct fhstatus res;
#ifdef HAVE_FS_NFS3
  struct am_mountres3 res3;
#endif /* HAVE_FS_NFS3 */

  fp = find_nfs_fhandle_cache(arg, done);
  if (!fp)
    return;

  /*
   * retrieve the correct RPC reply for the file handle, based on the
   * NFS protocol version.
   */
#ifdef HAVE_FS_NFS3
  if (fp->fh_nfs_version == NFS_VERSION3) {
    memset(&res3, 0, sizeof(res3));
    fp->fh_error = pickup_rpc_reply(pkt, len, (voidp) &res3,
				    (XDRPROC_T_TYPE) xdr_am_mountres3);
    fp->fh_status = unx_error(res3.fhs_status);
    memset(&fp->fh_nfs_handle.v3, 0, sizeof(am_nfs_fh3));
    fp->fh_nfs_handle.v3.am_fh3_length = res3.mountres3_u.mountinfo.fhandle.fhandle3_len;
    memmove(fp->fh_nfs_handle.v3.am_fh3_data,
	    res3.mountres3_u.mountinfo.fhandle.fhandle3_val,
	    fp->fh_nfs_handle.v3.am_fh3_length);

    XFREE(res3.mountres3_u.mountinfo.fhandle.fhandle3_val);
    if (res3.mountres3_u.mountinfo.auth_flavors.auth_flavors_val)
      XFREE(res3.mountres3_u.mountinfo.auth_flavors.auth_flavors_val);
  } else {
#endif /* HAVE_FS_NFS3 */
    memset(&res, 0, sizeof(res));
    fp->fh_error = pickup_rpc_reply(pkt, len, (voidp) &res,
				    (XDRPROC_T_TYPE) xdr_fhstatus);
    fp->fh_status = unx_error(res.fhs_status);
    memmove(&fp->fh_nfs_handle.v2, &res.fhs_fh, NFS_FHSIZE);
#ifdef HAVE_FS_NFS3
  }
#endif /* HAVE_FS_NFS3 */

  if (!fp->fh_error) {
    dlog("got filehandle for %s:%s", fp->fh_fs->fs_host, fp->fh_path);
  } else {
    plog(XLOG_USER, "filehandle denied for %s:%s", fp->fh_fs->fs_host, fp->fh_path);
    /*
     * Force the error to be EACCES. It's debatable whether it should be
     * ENOENT instead, but the server really doesn't give us any clues, and
     * EACCES is more in line with the "filehandle denied" message.
     */
    fp->fh_error = EACCES;
  }

  /*
   * Wakeup anything sleeping on this filehandle
   */
  if (fp->fh_wchan) {
    dlog("Calling wakeup on %#lx", (unsigned long) fp->fh_wchan);
    wakeup(fp->fh_wchan);
  }
}