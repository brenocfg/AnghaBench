#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct sockaddr_in {int dummy; } ;
typedef  int /*<<< orphan*/  res3 ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  opaque_t ;
struct TYPE_17__ {int /*<<< orphan*/  drok_fhandle; } ;
struct TYPE_18__ {TYPE_5__ dr_drok_u; } ;
struct TYPE_13__ {int /*<<< orphan*/ * am_fh3_data; int /*<<< orphan*/  am_fh3_length; } ;
struct TYPE_14__ {TYPE_1__ object; } ;
struct TYPE_15__ {TYPE_2__ ok; } ;
struct TYPE_20__ {TYPE_6__ dr_u; int /*<<< orphan*/  dr_status; int /*<<< orphan*/  am_fh3_length; TYPE_3__ res_u; int /*<<< orphan*/ * am_fh3_data; int /*<<< orphan*/  status; } ;
typedef  TYPE_8__ nfsdiropres ;
struct TYPE_16__ {int /*<<< orphan*/  v2; TYPE_8__ v3; } ;
struct TYPE_21__ {scalar_t__ fh_nfs_version; scalar_t__ fh_wchan; void* fh_error; int /*<<< orphan*/  fh_path; TYPE_7__* fh_fs; TYPE_4__ fh_nfs_handle; void* fh_status; } ;
typedef  TYPE_9__ fh_cache ;
typedef  int /*<<< orphan*/  am_nfs_fh3 ;
typedef  TYPE_8__ am_LOOKUP3res ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
struct TYPE_19__ {int /*<<< orphan*/  fs_host; } ;

/* Variables and functions */
 void* EACCES ; 
 int /*<<< orphan*/  NFS_FHSIZE ; 
 scalar_t__ NFS_VERSION3 ; 
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  dlog (char*,unsigned long,...) ; 
 TYPE_9__* find_nfs_fhandle_cache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 void* pickup_rpc_reply (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* unx_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (scalar_t__) ; 
 scalar_t__ xdr_am_LOOKUP3res ; 
 scalar_t__ xdr_diropres ; 

__attribute__((used)) static void
got_nfs_fh_webnfs(voidp pkt, int len, struct sockaddr_in *sa, struct sockaddr_in *ia, opaque_t arg, int done)
{
  fh_cache *fp;
  nfsdiropres res;
#ifdef HAVE_FS_NFS3
  am_LOOKUP3res res3;
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
				    (XDRPROC_T_TYPE) xdr_am_LOOKUP3res);
    fp->fh_status = unx_error(res3.status);
    memset(&fp->fh_nfs_handle.v3, 0, sizeof(am_nfs_fh3));
    fp->fh_nfs_handle.v3.am_fh3_length = res3.res_u.ok.object.am_fh3_length;
    memmove(fp->fh_nfs_handle.v3.am_fh3_data,
	    res3.res_u.ok.object.am_fh3_data,
	    fp->fh_nfs_handle.v3.am_fh3_length);
  } else {
#endif /* HAVE_FS_NFS3 */
    memset(&res, 0, sizeof(res));
    fp->fh_error = pickup_rpc_reply(pkt, len, (voidp) &res,
				    (XDRPROC_T_TYPE) xdr_diropres);
    fp->fh_status = unx_error(res.dr_status);
    memmove(&fp->fh_nfs_handle.v2, &res.dr_u.dr_drok_u.drok_fhandle, NFS_FHSIZE);
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