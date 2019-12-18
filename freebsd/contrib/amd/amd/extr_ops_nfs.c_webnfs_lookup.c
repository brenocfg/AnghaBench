#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchan_t ;
typedef  TYPE_4__* voidp ;
typedef  int /*<<< orphan*/  u_long ;
struct rpc_msg {int dummy; } ;
typedef  int /*<<< orphan*/  opaque_t ;
struct TYPE_14__ {scalar_t__ am_fh3_length; } ;
struct TYPE_15__ {char* name; TYPE_2__ dir; } ;
struct TYPE_16__ {char* da_name; int /*<<< orphan*/  da_fhandle; TYPE_3__ what; } ;
typedef  TYPE_4__ nfsdiropargs ;
typedef  int /*<<< orphan*/  iobuf ;
typedef  int /*<<< orphan*/  fwd_fun ;
struct TYPE_12__ {scalar_t__ sin_port; } ;
struct TYPE_17__ {scalar_t__ fh_nfs_version; scalar_t__ fh_id; TYPE_10__ fh_sin; int /*<<< orphan*/  fh_path; TYPE_1__* fh_fs; } ;
typedef  TYPE_6__ fh_cache ;
typedef  TYPE_4__ am_LOOKUP3args ;
typedef  scalar_t__ XDRPROC_T_TYPE ;
struct TYPE_13__ {int fs_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_NFSPROC3_LOOKUP ; 
 int /*<<< orphan*/  MK_RPC_XID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NFSPROC_LOOKUP ; 
 int /*<<< orphan*/  NFS_FHSIZE ; 
 int /*<<< orphan*/  NFS_PORT ; 
 int /*<<< orphan*/  NFS_PROGRAM ; 
 scalar_t__ NFS_VERSION3 ; 
 int /*<<< orphan*/  RPC_XID_WEBNFS ; 
 int UDPMSGSIZE ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int fwd_packet (int /*<<< orphan*/ ,char*,int,TYPE_10__*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int make_nfs_auth () ; 
 int make_rpc_packet (char*,int,int /*<<< orphan*/ ,struct rpc_msg*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_auth ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rpc_msg_init (struct rpc_msg*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_am_LOOKUP3args ; 
 scalar_t__ xdr_diropargs ; 
 scalar_t__ xmalloc (size_t) ; 
 int /*<<< orphan*/  xstrlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
webnfs_lookup(fh_cache *fp, fwd_fun fun, wchan_t wchan)
{
  struct rpc_msg wnfs_msg;
  int len;
  char iobuf[UDPMSGSIZE];
  int error;
  u_long proc;
  XDRPROC_T_TYPE xdr_fn;
  voidp argp;
  nfsdiropargs args;
#ifdef HAVE_FS_NFS3
  am_LOOKUP3args args3;
#endif /* HAVE_FS_NFS3 */
  char *wnfs_path;
  size_t l;

  if (!nfs_auth) {
    error = make_nfs_auth();
    if (error)
      return error;
  }

  if (fp->fh_sin.sin_port == 0) {
    /* FIXME: wrong, don't discard sin_port in the first place for WebNFS. */
    plog(XLOG_WARNING, "webnfs_lookup: port == 0 for nfs on %s, fixed",
	 fp->fh_fs->fs_host);
    fp->fh_sin.sin_port = htons(NFS_PORT);
  }

  /*
   * Use native path like the rest of amd (cf. RFC 2054, 6.1).
   */
  l = strlen(fp->fh_path) + 2;
  wnfs_path = (char *) xmalloc(l);
  wnfs_path[0] = 0x80;
  xstrlcpy(wnfs_path + 1, fp->fh_path, l - 1);

  /* find the right program and lookup procedure */
#ifdef HAVE_FS_NFS3
  if (fp->fh_nfs_version == NFS_VERSION3) {
    proc = AM_NFSPROC3_LOOKUP;
    xdr_fn = (XDRPROC_T_TYPE) xdr_am_LOOKUP3args;
    argp = &args3;
    /* WebNFS public file handle */
    args3.what.dir.am_fh3_length = 0;
    args3.what.name = wnfs_path;
  } else {
#endif /* HAVE_FS_NFS3 */
    proc = NFSPROC_LOOKUP;
    xdr_fn = (XDRPROC_T_TYPE) xdr_diropargs;
    argp = &args;
    /* WebNFS public file handle */
    memset(&args.da_fhandle, 0, NFS_FHSIZE);
    args.da_name = wnfs_path;
#ifdef HAVE_FS_NFS3
  }
#endif /* HAVE_FS_NFS3 */

  plog(XLOG_INFO, "webnfs_lookup: NFS version %d", (int) fp->fh_nfs_version);

  rpc_msg_init(&wnfs_msg, NFS_PROGRAM, fp->fh_nfs_version, proc);
  len = make_rpc_packet(iobuf,
			sizeof(iobuf),
			proc,
			&wnfs_msg,
			argp,
			(XDRPROC_T_TYPE) xdr_fn,
			nfs_auth);

  if (len > 0) {
    error = fwd_packet(MK_RPC_XID(RPC_XID_WEBNFS, fp->fh_id),
		       iobuf,
		       len,
		       &fp->fh_sin,
		       &fp->fh_sin,
		       (opaque_t) ((long) fp->fh_id), /* cast to long needed for 64-bit archs */
		       fun);
  } else {
    error = -len;
  }

  XFREE(wnfs_path);
  return error;
}