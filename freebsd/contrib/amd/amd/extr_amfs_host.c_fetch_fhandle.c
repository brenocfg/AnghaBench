#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char* voidp ;
typedef  scalar_t__ u_long ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct fhstatus {int fhs_status; int /*<<< orphan*/  fhs_fh; } ;
struct TYPE_7__ {int /*<<< orphan*/ * fhandle3_val; int /*<<< orphan*/  fhandle3_len; } ;
struct TYPE_8__ {TYPE_1__ fhandle; } ;
struct TYPE_9__ {TYPE_2__ mountinfo; } ;
struct am_mountres3 {int fhs_status; TYPE_3__ mountres3_u; } ;
typedef  int /*<<< orphan*/  res3 ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
struct TYPE_10__ {int /*<<< orphan*/  am_fh3_length; int /*<<< orphan*/ * am_fh3_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  v2; TYPE_4__ v3; } ;
typedef  TYPE_5__ am_nfs_handle_t ;
typedef  int /*<<< orphan*/  am_nfs_fh3 ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
typedef  int /*<<< orphan*/  SVC_IN_ARG_TYPE ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MOUNTPROC_MNT ; 
 int /*<<< orphan*/  NFS_FHSIZE ; 
 scalar_t__ NFS_VERSION3 ; 
 scalar_t__ NFS_VERSION4 ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval) ; 
 int clnt_sperrno (int) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ xdr_am_mountres3 ; 
 scalar_t__ xdr_dirpath ; 
 scalar_t__ xdr_fhstatus ; 

__attribute__((used)) static int
fetch_fhandle(CLIENT *client, char *dir, am_nfs_handle_t *fhp, u_long nfs_version)
{
  struct timeval tv;
  enum clnt_stat clnt_stat;
  struct fhstatus res;
#ifdef HAVE_FS_NFS3
  struct am_mountres3 res3;
#endif /* HAVE_FS_NFS3 */

  /*
   * Pick a number, any number...
   */
  tv.tv_sec = 20;
  tv.tv_usec = 0;

  dlog("Fetching fhandle for %s", dir);

  /*
   * Call the mount daemon on the remote host to
   * get the filehandle.  Use NFS version specific call.
   */

  plog(XLOG_INFO, "fetch_fhandle: NFS version %d", (int) nfs_version);
#ifdef HAVE_FS_NFS3
  if (nfs_version == NFS_VERSION3
#ifdef HAVE_FS_NFS4
#ifndef NO_FALLBACK
      || nfs_version == NFS_VERSION4
#endif /* NO_FALLBACK */
#endif /* HAVE_FS_NFS4 */
    ) {

    memset((char *) &res3, 0, sizeof(res3));
    clnt_stat = clnt_call(client,
			  MOUNTPROC_MNT,
			  (XDRPROC_T_TYPE) xdr_dirpath,
			  (SVC_IN_ARG_TYPE) &dir,
			  (XDRPROC_T_TYPE) xdr_am_mountres3,
			  (SVC_IN_ARG_TYPE) &res3,
			  tv);
    if (clnt_stat != RPC_SUCCESS) {
      plog(XLOG_ERROR, "mountd rpc failed: %s", clnt_sperrno(clnt_stat));
      return EIO;
    }
    /* Check the status of the filehandle */
    if ((errno = res3.fhs_status)) {
      dlog("fhandle fetch for mount version 3 failed: %m");
      return errno;
    }
    memset((voidp) &fhp->v3, 0, sizeof(am_nfs_fh3));
    fhp->v3.am_fh3_length = res3.mountres3_u.mountinfo.fhandle.fhandle3_len;
    memmove(fhp->v3.am_fh3_data,
	    res3.mountres3_u.mountinfo.fhandle.fhandle3_val,
	    fhp->v3.am_fh3_length);
  } else {			/* not NFS_VERSION3 mount */
#endif /* HAVE_FS_NFS3 */
    clnt_stat = clnt_call(client,
			  MOUNTPROC_MNT,
			  (XDRPROC_T_TYPE) xdr_dirpath,
			  (SVC_IN_ARG_TYPE) &dir,
			  (XDRPROC_T_TYPE) xdr_fhstatus,
			  (SVC_IN_ARG_TYPE) &res,
			  tv);
    if (clnt_stat != RPC_SUCCESS) {
      plog(XLOG_ERROR, "mountd rpc failed: %s", clnt_sperrno(clnt_stat));
      return EIO;
    }
    /* Check status of filehandle */
    if (res.fhs_status) {
      errno = res.fhs_status;
      dlog("fhandle fetch for mount version 1 failed: %m");
      return errno;
    }
    memmove(&fhp->v2, &res.fhs_fh, NFS_FHSIZE);
#ifdef HAVE_FS_NFS3
  } /* end of "if (nfs_version == NFS_VERSION3)" statement */
#endif /* HAVE_FS_NFS3 */

  /* all is well */
  return 0;
}