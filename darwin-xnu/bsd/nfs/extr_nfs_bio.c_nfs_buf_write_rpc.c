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
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct nfsreq_cbinfo {int* rcb_args; struct nfsbuf* rcb_bp; int /*<<< orphan*/  (* rcb_func ) (struct nfsreq*) ;} ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; int nm_wsize; int nm_stategenid; TYPE_1__* nm_funcs; } ;
struct nfsbuf {int nb_error; int nb_flags; int nb_offio; int nb_endio; int nb_rpcs; scalar_t__ nb_data; int /*<<< orphan*/  nb_commitlevel; int /*<<< orphan*/  nb_np; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_2__ {int (* nf_write_rpc_async ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nfsreq_cbinfo*,struct nfsreq**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (scalar_t__) ; 
 int /*<<< orphan*/  CLR (int,int /*<<< orphan*/ ) ; 
 int EFBIG ; 
 int ENXIO ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int NBOFF (struct nfsbuf*) ; 
 int NB_ASYNC ; 
 int /*<<< orphan*/  NB_ERROR ; 
 int /*<<< orphan*/  NB_MULTASYNCRPC ; 
 scalar_t__ NFSIOD_MAX ; 
 struct nfsmount* NFSTONMP (int /*<<< orphan*/ ) ; 
 int NFS_VER2 ; 
 int NFS_VER4 ; 
 int /*<<< orphan*/  NFS_WRITE_FILESYNC ; 
 int /*<<< orphan*/  SET (int,int /*<<< orphan*/ ) ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_async_write_done (struct nfsmount*) ; 
 int nfs_async_write_start (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_buf_iodone (struct nfsbuf*) ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfs_buf_write_finish (struct nfsbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_write_rpc_finish (struct nfsreq*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nfsreq_cbinfo*,struct nfsreq**) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int) ; 

int
nfs_buf_write_rpc(struct nfsbuf *bp, int iomode, thread_t thd, kauth_cred_t cred)
{
	struct nfsmount *nmp;
	nfsnode_t np = bp->nb_np;
	int error = 0, nfsvers, async;
	int offset, nrpcs;
	uint32_t nmwsize, length, len;
	struct nfsreq *req;
	struct nfsreq_cbinfo cb;
	uio_t auio;
	char uio_buf [ UIO_SIZEOF(1) ];

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp)) {
		bp->nb_error = error = ENXIO;
		SET(bp->nb_flags, NB_ERROR);
		nfs_buf_iodone(bp);
		return (error);
	}
	nfsvers = nmp->nm_vers;
	nmwsize = nmp->nm_wsize;

	offset = bp->nb_offio;
	length = bp->nb_endio - bp->nb_offio;

	/* Note: Can only do async I/O if nfsiods are configured. */
	async = (bp->nb_flags & NB_ASYNC) && (NFSIOD_MAX > 0);
	bp->nb_commitlevel = NFS_WRITE_FILESYNC;
	cb.rcb_func = async ? nfs_buf_write_rpc_finish : NULL;
	cb.rcb_bp = bp;

	if ((nfsvers == NFS_VER2) && ((NBOFF(bp) + bp->nb_endio) > 0xffffffffLL)) {
		bp->nb_error = error = EFBIG;
		SET(bp->nb_flags, NB_ERROR);
		nfs_buf_iodone(bp);
		return (error);
	}

	auio = uio_createwithbuffer(1, NBOFF(bp) + offset, UIO_SYSSPACE,
		UIO_WRITE, &uio_buf, sizeof(uio_buf));
	uio_addiov(auio, CAST_USER_ADDR_T(bp->nb_data + offset), length);

	bp->nb_rpcs = nrpcs = (length + nmwsize - 1) / nmwsize;
	if (async && (nrpcs > 1)) {
		SET(bp->nb_flags, NB_MULTASYNCRPC);
	} else {
		CLR(bp->nb_flags, NB_MULTASYNCRPC);
	}

	while (length > 0) {
		if (ISSET(bp->nb_flags, NB_ERROR)) {
			error = bp->nb_error;
			break;
		}
		len = (length > nmwsize) ? nmwsize : length;
		cb.rcb_args[0] = offset;
		cb.rcb_args[1] = len;
		if (nmp->nm_vers >= NFS_VER4)
			cb.rcb_args[2] = nmp->nm_stategenid;
		if (async && ((error = nfs_async_write_start(nmp))))
			break;
		req = NULL;
		error = nmp->nm_funcs->nf_write_rpc_async(np, auio, len, thd, cred,
				iomode, &cb, &req);
		if (error) {
			if (async)
				nfs_async_write_done(nmp);
			break;
		}
		offset += len;
		length -= len;
		if (async)
			continue;
		nfs_buf_write_rpc_finish(req);
	}

	if (length > 0) {
		/*
		 * Something bad happened while trying to send the RPCs.
		 * Wait for any outstanding requests to complete.
		 */
		bp->nb_error = error;
		SET(bp->nb_flags, NB_ERROR);
		if (ISSET(bp->nb_flags, NB_MULTASYNCRPC)) {
			nrpcs = (length + nmwsize - 1) / nmwsize;
			lck_mtx_lock(nfs_buf_mutex);
			bp->nb_rpcs -= nrpcs;
			if (bp->nb_rpcs == 0) {
				/* No RPCs left, so the buffer's done */
				lck_mtx_unlock(nfs_buf_mutex);
				nfs_buf_write_finish(bp, thd, cred);
			} else {
				/* wait for the last RPC to mark it done */
				while (bp->nb_rpcs > 0)
					msleep(&bp->nb_rpcs, nfs_buf_mutex, 0,
						"nfs_buf_write_rpc_cancel", NULL);
				lck_mtx_unlock(nfs_buf_mutex);
			}
		} else {
			nfs_buf_write_finish(bp, thd, cred);
		}
		/* It may have just been an interrupt... that's OK */
		if (!ISSET(bp->nb_flags, NB_ERROR))
			error = 0;
	}

	return (error);
}