#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_in {int dummy; } ;
typedef  int /*<<< orphan*/  mntpt ;
typedef  int /*<<< orphan*/  mntlist ;
struct TYPE_18__ {int mf_flags; char* mf_info; int /*<<< orphan*/  mf_mount; TYPE_1__* mf_server; } ;
typedef  TYPE_2__ mntfs ;
typedef  int /*<<< orphan*/  fs_name ;
typedef  TYPE_3__* exports ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  am_node ;
typedef  TYPE_3__* am_nfs_handle_t ;
typedef  int /*<<< orphan*/  XDRPROC_T_TYPE ;
struct TYPE_20__ {scalar_t__ cl_auth; } ;
struct TYPE_19__ {char* ex_dir; struct TYPE_19__* ex_next; } ;
struct TYPE_17__ {char* fs_host; scalar_t__ fs_version; struct sockaddr_in* fs_ip; } ;
typedef  int /*<<< orphan*/  SVC_IN_ARG_TYPE ;
typedef  TYPE_5__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AM_MOUNTVERS3 ; 
 int EINVAL ; 
 int EIO ; 
 int FALSE ; 
 int MAXPATHLEN ; 
 int MFF_WEBNFS ; 
 int /*<<< orphan*/  MOUNTPROC_EXPORT ; 
 int /*<<< orphan*/  MOUNTVERS ; 
 scalar_t__ NFS_VERSION3 ; 
 int RPC_ANYSOCK ; 
 int RPC_SUCCESS ; 
 scalar_t__ STREQ (char*,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  XFREE (TYPE_3__**) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 scalar_t__ already_mounted (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  amu_close (int) ; 
 int clnt_call (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval) ; 
 int /*<<< orphan*/  clnt_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 char* clnt_sperrno (int) ; 
 int /*<<< orphan*/  discard_mntlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,char*) ; 
 scalar_t__ do_mount (TYPE_3__**,char*,char*,TYPE_2__*) ; 
 int fetch_fhandle (TYPE_5__*,char*,TYPE_3__**,scalar_t__) ; 
 TYPE_5__* get_mount_client (char*,struct sockaddr_in*,struct timeval*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_mntpt (char*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int make_nfs_auth () ; 
 int /*<<< orphan*/  mnttab_file_name ; 
 scalar_t__ nfs_auth ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  qsort (TYPE_3__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_mtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sortfun ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  unlock_mntlist () ; 
 scalar_t__ xdr_exports ; 
 int /*<<< orphan*/  xdr_pri_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_void ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

__attribute__((used)) static int
amfs_host_mount(am_node *am, mntfs *mf)
{
  struct timeval tv2;
  CLIENT *client;
  enum clnt_stat clnt_stat;
  int n_export;
  int j, k;
  exports exlist = 0, ex;
  exports *ep = NULL;
  am_nfs_handle_t *fp = NULL;
  char *host;
  int error = 0;
  struct sockaddr_in sin;
  int sock = RPC_ANYSOCK;
  int ok = FALSE;
  mntlist *mlist;
  char fs_name[MAXPATHLEN], *rfs_dir;
  char mntpt[MAXPATHLEN];
  struct timeval tv;
  u_long mnt_version;

  /*
   * WebNFS servers don't necessarily run mountd.
   */
  if (mf->mf_flags & MFF_WEBNFS) {
    plog(XLOG_ERROR, "amfs_host_mount: cannot support WebNFS");
    return EIO;
  }

  /*
   * Read the mount list
   */
  mlist = read_mtab(mf->mf_mount, mnttab_file_name);

#ifdef MOUNT_TABLE_ON_FILE
  /*
   * Unlock the mount list
   */
  unlock_mntlist();
#endif /* MOUNT_TABLE_ON_FILE */

  /*
   * Take a copy of the server hostname, address, and nfs version
   * to mount version conversion.
   */
  host = mf->mf_server->fs_host;
  sin = *mf->mf_server->fs_ip;
  plog(XLOG_INFO, "amfs_host_mount: NFS version %d", (int) mf->mf_server->fs_version);
#ifdef HAVE_FS_NFS3
  if (mf->mf_server->fs_version == NFS_VERSION3)
    mnt_version = AM_MOUNTVERS3;
  else
#endif /* HAVE_FS_NFS3 */
    mnt_version = MOUNTVERS;

  /*
   * The original 10 second per try timeout is WAY too large, especially
   * if we're only waiting 10 or 20 seconds max for the response.
   * That would mean we'd try only once in 10 seconds, and we could
   * lose the transmit or receive packet, and never try again.
   * A 2-second per try timeout here is much more reasonable.
   * 09/28/92 Mike Mitchell, mcm@unx.sas.com
   */
  tv.tv_sec = 2;
  tv.tv_usec = 0;

  /*
   * Create a client attached to mountd
   */
  client = get_mount_client(host, &sin, &tv, &sock, mnt_version);
  if (client == NULL) {
#ifdef HAVE_CLNT_SPCREATEERROR
    plog(XLOG_ERROR, "get_mount_client failed for %s: %s",
	 host, clnt_spcreateerror(""));
#else /* not HAVE_CLNT_SPCREATEERROR */
    plog(XLOG_ERROR, "get_mount_client failed for %s", host);
#endif /* not HAVE_CLNT_SPCREATEERROR */
    error = EIO;
    goto out;
  }
  if (!nfs_auth) {
    error = make_nfs_auth();
    if (error)
      goto out;
  }
  client->cl_auth = nfs_auth;

  dlog("Fetching export list from %s", host);

  /*
   * Fetch the export list
   */
  tv2.tv_sec = 10;
  tv2.tv_usec = 0;
  clnt_stat = clnt_call(client,
			MOUNTPROC_EXPORT,
			(XDRPROC_T_TYPE) xdr_void,
			0,
			(XDRPROC_T_TYPE) xdr_exports,
			(SVC_IN_ARG_TYPE) & exlist,
			tv2);
  if (clnt_stat != RPC_SUCCESS) {
    const char *msg = clnt_sperrno(clnt_stat);
    plog(XLOG_ERROR, "host_mount rpc failed: %s", msg);
    /* clnt_perror(client, "rpc"); */
    error = EIO;
    goto out;
  }

  /*
   * Figure out how many exports were returned
   */
  for (n_export = 0, ex = exlist; ex; ex = ex->ex_next) {
    n_export++;
  }

  /*
   * Allocate an array of pointers into the list
   * so that they can be sorted.  If the filesystem
   * is already mounted then ignore it.
   */
  ep = (exports *) xmalloc(n_export * sizeof(exports));
  for (j = 0, ex = exlist; ex; ex = ex->ex_next) {
    make_mntpt(mntpt, sizeof(mntpt), ex, mf->mf_mount);
    if (already_mounted(mlist, mntpt))
      /* we have at least one mounted f/s, so don't fail the mount */
      ok = TRUE;
    else
      ep[j++] = ex;
  }
  n_export = j;

  /*
   * Sort into order.
   * This way the mounts are done in order down the tree,
   * instead of any random order returned by the mount
   * daemon (the protocol doesn't specify...).
   */
  qsort(ep, n_export, sizeof(exports), sortfun);

  /*
   * Allocate an array of filehandles
   */
  fp = (am_nfs_handle_t *) xmalloc(n_export * sizeof(am_nfs_handle_t));

  /*
   * Try to obtain filehandles for each directory.
   * If a fetch fails then just zero out the array
   * reference but discard the error.
   */
  for (j = k = 0; j < n_export; j++) {
    /* Check and avoid a duplicated export entry */
    if (j > k && ep[k] && STREQ(ep[j]->ex_dir, ep[k]->ex_dir)) {
      dlog("avoiding dup fhandle requested for %s", ep[j]->ex_dir);
      ep[j] = NULL;
    } else {
      k = j;
      error = fetch_fhandle(client, ep[j]->ex_dir, &fp[j],
			    mf->mf_server->fs_version);
      if (error)
	ep[j] = NULL;
    }
  }

  /*
   * Mount each filesystem for which we have a filehandle.
   * If any of the mounts succeed then mark "ok" and return
   * error code 0 at the end.  If they all fail then return
   * the last error code.
   */
  xstrlcpy(fs_name, mf->mf_info, sizeof(fs_name));
  if ((rfs_dir = strchr(fs_name, ':')) == (char *) NULL) {
    plog(XLOG_FATAL, "amfs_host_mount: mf_info has no colon");
    error = EINVAL;
    goto out;
  }
  ++rfs_dir;
  for (j = 0; j < n_export; j++) {
    ex = ep[j];
    if (ex) {
      /*
       * Note: the sizeof space left in rfs_dir is what's left in fs_name
       * after strchr() above returned a pointer _inside_ fs_name.  The
       * calculation below also takes into account that rfs_dir was
       * incremented by the ++ above.
       */
      xstrlcpy(rfs_dir, ex->ex_dir, sizeof(fs_name) - (rfs_dir - fs_name));
      make_mntpt(mntpt, sizeof(mntpt), ex, mf->mf_mount);
      if (do_mount(&fp[j], mntpt, fs_name, mf) == 0)
	ok = TRUE;
    }
  }

  /*
   * Clean up and exit
   */
out:
  discard_mntlist(mlist);
  XFREE(ep);
  XFREE(fp);
  if (sock != RPC_ANYSOCK)
    (void) amu_close(sock);
  if (client)
    clnt_destroy(client);
  if (exlist)
    xdr_pri_free((XDRPROC_T_TYPE) xdr_exports, (caddr_t) &exlist);
  if (ok)
    return 0;
  return error;
}